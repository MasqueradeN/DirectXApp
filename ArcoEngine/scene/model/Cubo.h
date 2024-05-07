#pragma once
#include <vector>
#include "ModelColor.h"

struct cubeInfo
{
	cubeInfo(){}
	cubeInfo(float px, float py, float pz)
	{
		x = px; y = py; z = pz;
	}
	float x, y, z;
	float r, g, b;
};

class CCubo : public CModelColor
{
private:
	cubeInfo mcubeInfo;

public:
	CCubo(ID3D11Device *device, ID3D11DeviceContext *context) : CModelColor(device, context) { }
	//CCubo(float ix, float iy, float iz) : CModelColor() { mcubeInfo.x = ix; mcubeInfo.y = iy; mcubeInfo.z = iz; }
	//CCubo(cubeInfo *info) : CModelColor() { mcubeInfo.x = info->x; mcubeInfo.y = info->y; mcubeInfo.z = info->z; }
	~CCubo(void)		{ }

	void InsertModel();
	void drawModel(float, float, float);
	//void drawModel(cubeInfo*);
	//void drawModel();
	void setRGB(float r, float g, float b){ mcubeInfo.r = r; mcubeInfo.g = g; mcubeInfo.b = b; }
	//void Release() override { CModelColor::Release(); }
};