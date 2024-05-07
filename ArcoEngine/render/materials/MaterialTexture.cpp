#include <fstream>
#include <string>
#include <d3d11.h>

#include "MaterialTexture.h"
#include "WICTextureLoader.h"

MaterialTexture::MaterialTexture(void)
: MaterialBase(), mpTextureRV(nullptr)
, mpSamplerLinear(nullptr)
{
}

MaterialTexture::~MaterialTexture(void) 
{
	if (mpTextureRV)			{ mpTextureRV->Release();			}
	if (mpSamplerLinear)	{ mpSamplerLinear->Release(); }
}

bool MaterialTexture::Initialize(
	const std::string &shadername, const std::wstring &texturename,
	const D3D11_INPUT_ELEMENT_DESC *vertexld, unsigned int vldsize,
	ID3D11Device *device, ID3D11DeviceContext *context)
{
	MaterialBase::Initialize(shadername, vertexld, vldsize, device);

	D3D11_BUFFER_DESC constantBufferDesc = { 0 };
	constantBufferDesc.ByteWidth = sizeof(MathUtil::CMatrix);
	constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.CPUAccessFlags = 0;
	constantBufferDesc.MiscFlags = 0;
	constantBufferDesc.StructureByteStride = 0;

	HRESULT hr = device->CreateBuffer(
		&constantBufferDesc, 0, &mpVConstantBuffer0);
	hr = device->CreateBuffer(
		&constantBufferDesc, 0, &mpVConstantBuffer1);
	hr = device->CreateBuffer(
		&constantBufferDesc, 0, &mpVConstantBuffer2);

	std::wstring dataPath(TEXT("data/"));
	dataPath += texturename;
	hr = DirectX::CreateWICTextureFromFile(
		device, context, dataPath.c_str(), nullptr, &mpTextureRV);
	if (FAILED(hr))
		return false;

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;//D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;//D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;//D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = device->CreateSamplerState(&sampDesc, &mpSamplerLinear);
	if (FAILED(hr))
		return false;

	//D3D11_BLEND_DESC BlendStateDescription;
	//ID3D11BlendState* pBlendState = NULL;
	//ZeroMemory(&BlendStateDescription, sizeof(D3D11_BLEND_DESC));

	//BlendStateDescription.RenderTarget[0].BlendEnable = TRUE;
	//BlendStateDescription.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	//BlendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	//BlendStateDescription.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	//BlendStateDescription.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	//BlendStateDescription.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_INV_DEST_ALPHA;
	//BlendStateDescription.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	//BlendStateDescription.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	//device->CreateBlendState(&BlendStateDescription, &pBlendState);
	//float blendFactor[] = { 0, 0, 0, 0 };
	//UINT sampleMask = 0xffffffff;

	//context->OMSetBlendState(pBlendState, blendFactor, sampleMask);

	return true;
}



