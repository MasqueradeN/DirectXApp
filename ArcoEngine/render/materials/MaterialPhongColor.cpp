#include <fstream>
#include <string>
#include <d3d11.h>

#include "MaterialPhongColor.h"

MaterialPhongColor::MaterialPhongColor(void)
: MaterialBase()
{
}

bool MaterialPhongColor::Initialize(
	char *shadername,
	const D3D11_INPUT_ELEMENT_DESC *vertexld,
	unsigned int vldsize,
	ID3D11Device *device)
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

	constantBufferDesc = { 0 };
	constantBufferDesc.ByteWidth = sizeof(sColorBuffer);
	constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.CPUAccessFlags = 0;
	constantBufferDesc.MiscFlags = 0;
	constantBufferDesc.StructureByteStride = 0;

	hr = device->CreateBuffer(
		&constantBufferDesc, 0, &mpPConstantBuffer);

	return true;
}



