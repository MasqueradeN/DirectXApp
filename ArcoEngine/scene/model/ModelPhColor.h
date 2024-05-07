#pragma once
#include <vector>
#include <memory>
#include "ModelBase.h"
#include "../../render/materials/VertexFormat.h"

class DXCamera;
class MaterialPhongColor;

class CModelPhColor : public CModelBase<BasicPosNorVertex>
{
public:
	~CModelPhColor(void);

	void Initialize(DXCamera *camera);

	virtual void drawModel();
	virtual phyVector3D getColor() { return mColor; }
	virtual void setColor(phyVector3D color) { mbColorNeedsUpdate = true; mColor = color; }

protected:
	CModelPhColor(ID3D11Device *device, ID3D11DeviceContext *context);
	void setRenderProperties();

protected:
	MaterialPhongColor *mMaterialColor;

	DXCamera *mCamera;
	phyVector3D mColor;
	bool mbColorNeedsUpdate;
};
