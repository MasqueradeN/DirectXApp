#pragma once
#include <vector>
#include "ModelPhColor.h"

class CCuboP : public CModelPhColor
{
public:
	CCuboP(ID3D11Device *device, ID3D11DeviceContext *context) : CModelPhColor(device, context) { }
	~CCuboP(void)		{ }

	void InsertModel();
	void drawModel(float, float, float, float, float, float);
};
