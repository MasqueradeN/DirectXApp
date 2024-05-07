#pragma once
#include <d3d11.h>
#include "VertexFormat.h"
#include <vector>

class MaterialBase 
{
protected:
	ID3D11InputLayout	*mpInputLayout;

	ID3D11VertexShader		*mpVertexShader;
	ID3D11PixelShader		*mpPixelShader;
	sTransformBuffer		mCameraBufferData;

	unsigned long m_dwShaderFlags;

public:
	MaterialBase(void);

	virtual ~MaterialBase(void) { }

	bool Initialize(
		const std::string &shaderName,
		const D3D11_INPUT_ELEMENT_DESC *vertexld,
		unsigned int vldsize, ID3D11Device *device);

	sTransformBuffer &GetCameraBufferData()	{ return mCameraBufferData; }

	ID3D11VertexShader *GetVertexShader()		{ return mpVertexShader; }
	ID3D11PixelShader *GetPixelShader()			{ return mpPixelShader; }

	ID3D11InputLayout *GetInputLayout()			{ return mpInputLayout; }

};


