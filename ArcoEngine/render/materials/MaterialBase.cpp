#include <fstream>
#include <string>
#include <vector>
#include <d3d11.h>

#include "MaterialBase.h"

MaterialBase::MaterialBase(void)
: mpVertexShader(nullptr)
, mpPixelShader(nullptr)
, mpInputLayout(nullptr)
{
}

bool MaterialBase::Initialize(
	const std::string &shaderName,
	const D3D11_INPUT_ELEMENT_DESC *vertexld, 
	unsigned int vldsize, 
	ID3D11Device *device)
{
	int size = 0;
	std::string sname("data/");
	sname.append(shaderName);

	std::string vsName = sname + "_VS.cso";
	std::string psName = sname + "_PS.cso";
	std::vector<char> comShader;
	
	FillVectorWithFile(vsName, comShader, size);
	HRESULT hr = device->CreateVertexShader(
		&comShader[0], size, 0, &mpVertexShader);
	if (hr != S_OK) { return false; }

	hr = device->CreateInputLayout(
		vertexld, vldsize, 
		&comShader[0], size, &mpInputLayout);
	if (hr != S_OK) { return false; }

	FillVectorWithFile(psName, comShader, size);
	hr = device->CreatePixelShader(
		&comShader[0], size, 0, &mpPixelShader);
	if (hr != S_OK) { return false; }

	mCameraBufferData.model = MathUtil::MatrixIdentity();
	mCameraBufferData.view = MathUtil::MatrixIdentity();
	mCameraBufferData.projection = MathUtil::MatrixIdentity();

	return true;
}




