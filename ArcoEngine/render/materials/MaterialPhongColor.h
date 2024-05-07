#pragma once
#include "MaterialBase.h"

class MaterialPhongColor : public MaterialBase
{
public:
	MaterialPhongColor(void);
	virtual ~MaterialPhongColor(void) { }

	bool Initialize(
		char *shadername,
		const D3D11_INPUT_ELEMENT_DESC *vertexld,
		unsigned int vldsize, ID3D11Device *device);

	ID3D11Buffer *GetVConstantBuffer0() { return mpVConstantBuffer0; }
	ID3D11Buffer *GetVConstantBuffer1() { return mpVConstantBuffer1; }
	ID3D11Buffer *GetVConstantBuffer2() { return mpVConstantBuffer2; }

	ID3D11Buffer *GetPConstantBuffer()	{ return mpPConstantBuffer; }

protected:
	ID3D11Buffer		*mpVConstantBuffer0;
	ID3D11Buffer		*mpVConstantBuffer1;
	ID3D11Buffer		*mpVConstantBuffer2;

	ID3D11Buffer		*mpPConstantBuffer;
};



