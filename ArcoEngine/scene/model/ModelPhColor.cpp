#include <d3d11.h>
#include <cmath>
#include "ModelPhColor.h"
#include "../../render/DXCamera.h"
#include "../../render/materials/MaterialPhongColor.h"

CModelPhColor::CModelPhColor(ID3D11Device *device, ID3D11DeviceContext *context)
	: CModelBase(device, context)
	, mbColorNeedsUpdate(true), mCamera(nullptr)
	, mMaterialColor(nullptr)
{
}

CModelPhColor::~CModelPhColor(void)
{
	if (mMaterialColor) 
		delete mMaterialColor;
}

void CModelPhColor::Initialize(DXCamera *camera)
{
	mCamera = camera;
	mMaterialColor = new MaterialPhongColor();
	mMaterialColor->Initialize("PhongShader", posNorVertexLayoutDesc, posNorVertexLayoutSize, mpDevice);
	CModelBase::Initialize(mMaterialColor);
}

void CModelPhColor::drawModel()
{
	setRenderProperties();
	activateBuffers();
	mpContext->DrawIndexed(mIndexBufferSize, 0, 0);
}

void CModelPhColor::setRenderProperties()
{
	ID3D11Buffer *conbuf;
	if (mCamera->viewNeedsUpdate() || mCamera->projectionNeedsUpdate())
	{
		if (mCamera->viewNeedsUpdate())
		{
			MathUtil::CMatrix nview = mCamera->GetView();
			nview = MathUtil::MatrixTranspose(nview);
			conbuf = mMaterialColor->GetVConstantBuffer1();
			mpContext->UpdateSubresource(
				conbuf, 0, nullptr, &nview, 0, 0);
			mpContext->VSSetConstantBuffers(1, 1, &conbuf);
		}
		if (mCamera->projectionNeedsUpdate())
		{
			MathUtil::CMatrix nproj = mCamera->GetProjection();
			nproj = MathUtil::MatrixTranspose(nproj);
			conbuf = mMaterialColor->GetVConstantBuffer2();
			mpContext->UpdateSubresource(
				conbuf, 0, nullptr, &nproj, 0, 0);
			mpContext->VSSetConstantBuffers(2, 1, &conbuf);
		}
	}
	conbuf = mMaterialColor->GetPConstantBuffer();
	phyVector3D color = getColor();
	float bufferColor[4];
	bufferColor[0] = color.x;
	bufferColor[1] = color.y;
	bufferColor[2] = color.z;
	bufferColor[3] = 1.f;

	mpContext->UpdateSubresource(conbuf, 0, nullptr, bufferColor, 0, 0);
	mpContext->PSSetConstantBuffers(0, 1, &conbuf);
}
