#include "ArcosApp.h"
#include <string>
#include "../render/DXCore.h"
#include "../render/DXRenderToTexture.h"
#include "../scene/logic/SceneLoader.h"

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

ArcosApp pApp;

ArcosApp::ArcosApp(void)
	: WinApplication(), mpDXCore(nullptr)	
{
	mTimer.setTockTime(0.050f);
}

ArcosApp::~ArcosApp(void)
{
	if (mpDXCore) { delete mpDXCore; mpDXCore = 0; }
	//if (mDXRenderToTexture) { delete mDXRenderToTexture; mDXRenderToTexture = 0; }	
}

void ArcosApp::InitializeScene()
{
	CSceneLoader sceneLoader;
	sceneLoader.LoadXML("gameobjs.xml");
	mSceneMgr.Initialize(mpDXCore->Get3DDevice(), mpDXCore->GetDeviceContext());
}


void ArcosApp::BuildObjects()
{

}

void ArcosApp::ReleaseObjects()
{
	
}

void ArcosApp::ProcessInput()
{

	if(KEY_DOWN(VK_RIGHT)) {
		//mSceneMgr.ChangeCamera(0, 1, 0);
		numeros.push_back(8);
	}
	if(KEY_DOWN(VK_LEFT)) {
		numeros.push_back(9);
		//mSceneMgr.ChangeCamera(0, -1, 0);
	}
	if(KEY_DOWN(VK_UP)) {
		//mSceneMgr.ChangeCamera(1, 0, 0);
	}
	if(KEY_DOWN(VK_DOWN)) {
		//mSceneMgr.ChangeCamera(-1, 0, 0);
	}
	if (KEY_DOWN(VK_SPACE)) {
	}

	if (KEY_DOWN(0x57)) {
	}

	if (KEY_DOWN(0x41)) {
	}

	if (KEY_DOWN(0x53)) {
	}

	if (KEY_DOWN(0x44)) {
	}
}

bool ArcosApp::AppBegin()
{	
	long w = 0, h = 0;
	GetWindowDims(w, h);

	mpDXCore = new DXCore();
	mpDXCore->Initialize(GetAppHwnd(), w, h);

	//mDXRenderToTexture = new DXRenderToTexture();
	//mDXRenderToTexture->Initialize(mpDXCore->Get3DDevice(), w, h);

	InitializeScene();

	BuildObjects();

	return true;
}

bool ArcosApp::AppUpdate()
{
	mTimer.Tick();
	float elapsedTime = mTimer.GetTimeElapsed();
	if (mTimer.IsTock()) {
		ProcessInput();
	}

	const float colorClear[4] = { 0.1961f, 0.0f, 0.9f, 1.0f };
	mpDXCore->ClearColor(colorClear);

	//mDXRenderToTexture->SetRenderTarget(
	//	mpDXCore->GetDeviceContext(), mpDXCore->GetDepthStencilView());
	//mDXRenderToTexture->ClearRenderTarget(
	//	mpDXCore->GetDeviceContext(), mpDXCore->GetDepthStencilView(),
	//	0.f, 0.f, 1.f);

	mSceneMgr.update(elapsedTime);
	mSceneMgr.draw(elapsedTime);

	mpDXCore->Present();	
	return true;
}

bool ArcosApp::AppEnd()
{
	mpDXCore->Close();
	return true;
}
