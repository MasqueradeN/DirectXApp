#pragma once
#include "winapplication.h"
#include "timer/Timer.h"
#include "../scene/SceneMgr.h"
#include <vector>

class DXCore;
class DXRenderToTexture;

class ArcosApp : public WinApplication
{
private:
	CTimer mTimer;
	DXCore *mpDXCore;
	//DXRenderToTexture *mDXRenderToTexture;

	CSceneMgr mSceneMgr;

private:
	virtual bool AppBegin();
	virtual bool AppUpdate();
	virtual bool AppEnd();

	void InitializeScene();

	void BuildObjects();
	void ReleaseObjects();
	void ProcessInput();

public:
	ArcosApp(void);
	virtual ~ArcosApp(void);

private:
	std::vector<int> numeros;

};
