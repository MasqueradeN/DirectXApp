#ifndef CAMERA_H
#define CAMERA_H

//#include <d3d11.h>
//#include <memory>
//#include <mutex>
#include "../scene/logic/UMath.h"

static const float DEGSTEP = 0.01745329f;
static const float RADIOSTEP = 0.5f;
static const float DEG30 = 0.52359877f;
static const float DEG150 = 2.61799387f;

struct sConstantBuffer;

class DXCamera
{
public:
	~DXCamera(void);
	DXCamera(void);

	//static DXCamera *getInstance();

	void Update(float elapsedTime);

	MathUtil::CMatrix &GetView();
	MathUtil::CMatrix &GetProjection();

	void DeltaRadioStep(bool isPos);
	void DeltaPhiStep(bool isPos);
	void DeltaThetaStep(bool isPos);

	void setCameraView(float x, float y, float z);
	void setCameraProjection(float angleFov, float aspect, float nearPlane, float farPlane);

	bool viewNeedsUpdate() { return mbHasChangedView; }
	bool projectionNeedsUpdate() { return mbHasChangedProj; }

	//void Release();

private:

private:
	float mfRa;
	float mfPH;
	float mfTE;

	float mX;
	float mY;
	float mZ;

	bool mbHasChangedView;
	bool mbHasChangedProj;

	MathUtil::CMatrix mView;
	MathUtil::CMatrix mProjection;

	sConstantBuffer *mpsConsData;

	//static std::mutex _mutex;
};

#endif
