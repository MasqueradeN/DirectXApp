#pragma once
#include <conio.h>
#include <iostream>
#include "../HungryHippos.h"

struct ID3D11Device;
struct ID3D11DeviceContext;
class CCubo;
class CCuboP;
class CCuboT;
class CPanel;
class DXCamera;

class CSceneMgr
{
public:
	CSceneMgr(void);
	~CSceneMgr(void);

	void Initialize(ID3D11Device *device, ID3D11DeviceContext *dcontext);
	void update(float deltaTime);

	void draw(float deltaTime);
	void changeCamera(float x, float y, float z);
	void keyPress();

private:
	float mClearColor[4];

	ID3D11Device *mpDevice;
	ID3D11DeviceContext *mpDcontext;

	CCubo *mCube;
	CCuboP *mCubePhong;
	CCuboT *mCubeTexture;
	CPanel *mPanel;

	HungryHippos hippont;

	DXCamera *mCamera;
	float angle;
};





