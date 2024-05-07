#pragma once
#include <vector>
#include <memory>
#include "../../render/materials/MaterialColor.h"
#include "ModelBase.h"

class DXCamera;

class CModelColor : public CModelBase<BasicPosVertex>
{
public:
	~CModelColor(void);

	void Initialize(DXCamera *camera);

	virtual void drawModel();
	virtual phyVector3D getColor() { return mColor; }
	virtual void setColor(phyVector3D color) { mbColorNeedsUpdate = true; mColor = color; }

protected:
	CModelColor(ID3D11Device *device, ID3D11DeviceContext *context);
	void setRenderProperties();

protected:
	MaterialColor *mMaterialColor;

	DXCamera *mCamera;
	phyVector3D mColor;
	bool mbColorNeedsUpdate;
};
