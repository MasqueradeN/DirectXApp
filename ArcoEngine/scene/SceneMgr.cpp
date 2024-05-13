#include <d3d11.h>

#include "SceneMgr.h"
#include "model/Cubo.h"
#include "model/CuboP.h"
#include "model/CuboT.h"
#include "model/Panel.h"
#include "../render/DXCamera.h"

static float cblack[3] = { 0.0f, 0.0f, 0.0f };
static float cblue[3] = { 0.01176f, 0.01568f, 0.43529f };

CSceneMgr::CSceneMgr(void)
: mpDevice(nullptr)
, mpDcontext(nullptr)
, mCamera(nullptr)
, mCube(nullptr)
, mCubePhong(nullptr)
, mCubeTexture(nullptr)
, mPanel(nullptr)
, angle(0.f)
{	
}

CSceneMgr::~CSceneMgr(void)
{
	//mCube->Release();
	if (mCube) delete mCube;
	if (mCubePhong) delete mCubePhong;
	if (mCubeTexture) delete mCubeTexture;
	if (mPanel) delete mPanel;
}

void CSceneMgr::changeCamera(float x, float y, float z)
{
	mCamera->setCameraView(x, y, z);
}

void CSceneMgr::Initialize(
	ID3D11Device* device, ID3D11DeviceContext* dcontext)
{
	mpDevice = device;
	mpDcontext = dcontext;

	mCamera = new DXCamera();
	mCamera->setCameraView(0.f, 0.f, 6.f);
	mCamera->setCameraProjection(MathUtil::Pi / 4.f, 1, 0.02f, 200.f);

	mCube = new CCubo(device, dcontext);
	mCube->Initialize(mCamera);
	mCube->InsertModel();
	mCube->setColor({ 0.0f, 0.5f, 0.039f });

	mCubePhong = new CCuboP(device, dcontext);
	mCubePhong->Initialize(mCamera);
	mCubePhong->InsertModel();
	mCubePhong->setColor({ 0.8569f, 0.5f, 0.6039f });

	//mCubeTexture = new CCuboT(device, dcontext);
	//mCubeTexture->Initialize(mCamera);
	//mCubeTexture->InsertModel();

	mPanel = new CPanel(device, dcontext);
	mPanel->Initialize(mCamera);
	mPanel->InsertModel();

	hippont.Initialize(device, dcontext, mCamera, L"hiposaeAzul.png", "data/HippoBody.obj");
}

void CSceneMgr::update(float deltaTime)
{
	// Rotación de la camara
	//changeCamera(-cosf(angle) * 4, 4.f, sinf(angle) * 4);
}

void CSceneMgr::draw(float deltaTime)
{
	//mCube->drawModel(4, 0, 1);

	//Rotación y movimiento del cubo phong
	angle += deltaTime;

	//mCubePhong->drawModel(0/*cosf(angle)*/, 0, 0/*sinf(angle)*/, 0/*angle*/, 0, 0);
	//mCubeTexture->drawModel(0, 0, 0);
	//mPanel->drawModel(0.75f, 0.75f, 0);
	//changeCamera();
	hippont.drawModel(0,0,-5,0,cosf(angle), 0);
}