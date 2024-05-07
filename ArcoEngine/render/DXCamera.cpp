#include <new>
#include "DXCamera.h"
//#include "..\render\shaders\ShaderBase.h"

//std::mutex DXCamera::_mutex;

//static DXCamera *instance = nullptr;

//DXCamera *DXCamera::getInstance()
//{
//	if (!instance)
//	{
//		std::lock_guard<std::mutex> lock(_mutex);
//		if (!instance)
//			instance = new DXCamera();
//	}
//	return instance;
//}

DXCamera::DXCamera(void)
	: mfRa(60.f), mfPH(0.f), mfTE(0.78539816339f)
	, mX(0.f), mY(0.f), mZ(-20.f)
	, mbHasChangedView(true)
	, mbHasChangedProj(true)
{
}

DXCamera::~DXCamera(void)
{
}


void DXCamera::setCameraView(float x, float y, float z)
{
	//float nz = mfRa * sinf(mfTE) * cosf(mfPH);
	//float nx = mfRa * sinf(mfTE) * sinf(mfPH);
	//float ny = mfRa * cosf(mfTE);

	MathUtil::sVector4f Eye = { { x, y, z, 0.0f } };
	MathUtil::sVector4f At = { { 0.f, 0.0f, 0.f, 0.f } };
	MathUtil::sVector4f Up = { { 0.f, 1.f, 0.f, 0.f } };
	mView = MathUtil::MatrixLookAtLH(Eye, At, Up);
	mbHasChangedView = true;
}

void DXCamera::setCameraProjection(float angleFov, float aspect, float nearPlane, float farPlane)
{
	mProjection = MathUtil::MatrixPerspectiveFovLH(MathUtil::Pi / 4.f, 1.f, 0.02f, 200.0f);
	mbHasChangedProj = true;
}



MathUtil::CMatrix &DXCamera::GetView()
{
	//if (!mbHasChangedView)
	//	return mView;

	//float nz = mfRa * sinf(mfTE) * cosf(mfPH);
	//float nx = mfRa * sinf(mfTE) * sinf(mfPH);
	//float ny = mfRa * cosf(mfTE);

	////XMVECTOR Eye = XMVectorSet(nx, ny, -nz, 0.0f);
	////XMVECTOR Eye = XMVectorSet(0.0f, 0.0f, -40.0f, 0.0f);
	//MathUtil::sVector4f Eye = { { mX, mY, mZ, 0.0f } };
	//MathUtil::sVector4f At = { { 0.f, 0.0f, 0.f, 0.f } };
	//MathUtil::sVector4f Up = { { 0.f, 1.f, 0.f, 0.f } };
	//mView = MathUtil::MatrixLookAtLH(Eye, At, Up);
	mbHasChangedView = false;
	return mView;
}

MathUtil::CMatrix &DXCamera::GetProjection()
{
	//if (!mbHasChangedProj)
	//	return mProjection;

	//mProjection = MathUtil::MatrixPerspectiveFovLH(MathUtil::Pi/4.f, 1.f, 0.01f, 500.0f);
	mbHasChangedProj = false;
	return mProjection;
}

void DXCamera::DeltaRadioStep(bool isPos)
{
	float realR = mfRa + (isPos ? RADIOSTEP : -RADIOSTEP);
	mfRa = realR>10.f ? 10.f : realR<2.f ? 2.f : realR;
	mbHasChangedView = true;
}

void DXCamera::DeltaPhiStep(bool isPos)
{
	const float DosPi = 6.28318530718f;
	float realv = mfPH + (isPos ? DEGSTEP : -DEGSTEP);
	mfPH = realv>DosPi ? realv - DosPi : realv<0.f ? DosPi + realv : realv;
	mbHasChangedView = true;
}

void DXCamera::DeltaThetaStep(bool isPos)
{
	float realv = mfTE + (isPos ? -DEGSTEP : DEGSTEP);
	mfTE = realv>DEG150 ? DEG150 : realv<DEG30 ? DEG30 : realv;
	mbHasChangedView = true;
}

//void DXCamera::SetCamera(float x, float y, float z)
//{
//	mX = x; mY = y; mZ = z;
//	mbHasChangedView = true;
//}

//void DXCamera::Release()
//{
//	delete instance;
//}