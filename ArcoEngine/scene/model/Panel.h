#pragma once
#include <vector>
#include "ModelRTT.h"

class CPanel : public CModelRTT
{
public:
	CPanel(ID3D11Device *device, ID3D11DeviceContext *context)
		: CModelRTT(device, context) { }
	~CPanel(void)		{ }

	void InsertModel();
	void drawModel(float, float, float);
};
