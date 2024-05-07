#include <d3d11.h>
#include <cmath>
#include "ModelRTT.h"
#include "../../render/DXCamera.h"
#include "../../render/materials/MaterialTexture.h"

CModelRTT::CModelRTT(ID3D11Device *device, ID3D11DeviceContext *context)
	: CModelBase(device, context)
	, mCamera(nullptr), mMaterialTexture(nullptr)
{
}

CModelRTT::~CModelRTT(void)
{
	if (mMaterialTexture)
		delete mMaterialTexture;
}

void CModelRTT::Initialize(DXCamera *camera)
{
	mCamera = camera;
	mMaterialTexture = new MaterialTexture();
	mMaterialTexture->Initialize(
		"SoloTexShader", TEXT("tela01.png"), posTexVertexLayoutDesc, posTexVertexLayoutSize,
		mpDevice, mpContext);
	CModelBase::Initialize(mMaterialTexture);
}

void CModelRTT::drawModel()
{
	setRenderProperties();
	activateBuffers();
	mpContext->DrawIndexed(mIndexBufferSize, 0, 0);
}

void CModelRTT::setRenderProperties()
{
	ID3D11Buffer *conbuf;
	if (mCamera->viewNeedsUpdate() || mCamera->projectionNeedsUpdate())
	{
		if (mCamera->viewNeedsUpdate())
		{
			MathUtil::CMatrix nview = mCamera->GetView();
			nview = MathUtil::MatrixTranspose(nview);
			conbuf = mMaterialTexture->GetVConstantBuffer1();
			mpContext->UpdateSubresource(
				conbuf, 0, nullptr, &nview, 0, 0);
			mpContext->VSSetConstantBuffers(1, 1, &conbuf);
		}
		if (mCamera->projectionNeedsUpdate())
		{
			MathUtil::CMatrix nproj = mCamera->GetProjection();
			nproj = MathUtil::MatrixTranspose(nproj);
			conbuf = mMaterialTexture->GetVConstantBuffer2();
			mpContext->UpdateSubresource(
				conbuf, 0, nullptr, &nproj, 0, 0);
			mpContext->VSSetConstantBuffers(2, 1, &conbuf);
		}
	}
	ID3D11ShaderResourceView *sres = mMaterialTexture->GetShaderResource();
	ID3D11SamplerState *sste = mMaterialTexture->GetSampler();
	mpContext->PSSetShaderResources(0, 1, &sres);
	mpContext->PSSetSamplers(0, 1, &sste);


	//conbuf = mMaterialColor->GetPConstantBuffer();
	//phyVector3D color = getColor();
	//float bufferColor[4];
	//bufferColor[0] = color.x;
	//bufferColor[1] = color.y;
	//bufferColor[2] = color.z;
	//bufferColor[3] = 1.f;

	//mpContext->UpdateSubresource(conbuf, 0, nullptr, bufferColor, 0, 0);
	//mpContext->PSSetConstantBuffers(0, 1, &conbuf);
}
