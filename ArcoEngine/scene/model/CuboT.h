#pragma once
#include <vector>
#include "ModelTexture.h"

class CCuboT : public CModelTexture
{
public:
	CCuboT(ID3D11Device *device, ID3D11DeviceContext *context) : CModelTexture(device, context) { }
	~CCuboT(void)		{ }

	void InsertModel(const std::string &modelname);
	void drawModel(float, float, float, float, float, float);
};
