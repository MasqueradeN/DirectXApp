#include <d3d11.h>
#include <cmath>
#include <numeric>
#include "CuboT.h"
#include "../../render/materials/MaterialTexture.h"
#include "HipoModel.h"

HipoModel::HipoModel()
	: mHipoCabeza(nullptr), mHipoCuerpo(nullptr), mHipoCuello(nullptr)
	, mAnimPos{ 0 }, mAnimAng{ 0 }
{
}

HipoModel::~HipoModel(void)
{
	if (mHipoCabeza) { delete mHipoCabeza; }
	if (mHipoCuerpo) { delete mHipoCuerpo; }
	if (mHipoCuello) { delete mHipoCuello; }
}

void HipoModel::Initialize(sDevNCam deviceCam, eHipoKind hipoType)
{
	InitializeModels(deviceCam, hipoType);

	sAnimSeq forwHd{ 0.f, 8.f, 0.07f };
	mAnims[0].addFrame(forwHd);

	sAnimSeq backHd{ 8.f, 0.f, 0.07f };
	mAnims[0].addFrame(backHd);

	sAnimSeq openHd{ 0.f, 30.f, 0.07f };
	mAnims[1].addFrame(openHd);

	sAnimSeq closeHd{ 30.f, 0.f, 0.07f };
	mAnims[1].addFrame(closeHd);

}

void HipoModel::InitializeModels(sDevNCam& deviceCam, eHipoKind hipoType)
{
	mHipoCabeza = new CCuboT(deviceCam.device, deviceCam.context);
	mHipoCuerpo = new CCuboT(deviceCam.device, deviceCam.context);
	mHipoCuello = new CCuboT(deviceCam.device, deviceCam.context);
	std::wstring cabeImg = L"hiposaeNaran.png";
	std::wstring cuerImg = L"panzahipo1.png";
	std::wstring cuelImg = L"cuellohipo1.png";

	switch (hipoType)
	{
	case eHipoKind::MIKE:
		cabeImg = L"hiposaeNaran.png";
		cuerImg = L"panzahipoN.png";
		cuelImg = L"cuellohipoN.png";
		break;
	case eHipoKind::DANIEL:
		cabeImg = L"hiposaeAmar.png";
		cuerImg = L"panzahipoA.png";
		cuelImg = L"cuellohipoA.png";
		break;
	case eHipoKind::MATEO:
		cabeImg = L"hiposaeAzul.png";
		cuerImg = L"panzahipoZ.png";
		cuelImg = L"cuellohipoZ.png";
		break;
	case eHipoKind::FRAN:
		cabeImg = L"hiposaeVerde.png";
		cuerImg = L"panzahipoV.png";
		cuelImg = L"cuellohipoV.png";
		break;
	default:
		break;
	}
	mHipoCabeza->Initialize(deviceCam.camera, cabeImg);
	mHipoCabeza->InsertModel("data/hiporeload.obj");

	mHipoCuerpo->Initialize(deviceCam.camera, cuerImg);
	mHipoCuerpo->InsertModel("data/panzahipo1.obj");

	mHipoCuello->Initialize(deviceCam.camera, cuelImg);
	mHipoCuello->InsertModel("data/cuellohipo1.obj");
}

eUpdateSt HipoModel::update(float deltaTime)
{
	mAccTime += deltaTime;
	std::pair<int, float> valPos = mAnims[0].propAnimStep(mAccTime);
	mAnimPos = valPos.second;

	std::pair<int, float> valAng = mAnims[1].propAnimStep(mAccTime);
	mAnimAng = valAng.second;

	return valPos.first == 0 ?
		eUpdateSt::done : valPos.first == 1 ? eUpdateSt::ok : eUpdateSt::done;
}

void HipoModel::hitHipo(float cutNowTime)
{
	mAccTime = 0.f;
	mAnims[0].startAnim(cutNowTime);
	mAnims[1].startAnim(cutNowTime);
}

void HipoModel::drawModel(float x, float y, float z, float angY, float angZ)
{
	mHipoCabeza->drawModel(x + mAnimPos, y, z, angY, angZ + mAnimAng);
	mHipoCuerpo->drawModel(x, y, z, angY);
	mHipoCuello->drawModel(x + mAnimPos, y, z, angY);
}