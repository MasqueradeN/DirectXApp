#pragma once
#include <vector>
#include "../logic/AnimLogic.h"

struct ID3D11Device;
struct ID3D11DeviceContext;
class DXCamera;
class CCuboT;

enum class eHipoKind
{
	MIKE = 0,
	DANIEL,
	MATEO,
	FRAN
};

enum class eUpdateSt
{
	none = 0,
	ok,
	done,
};

struct sDevNCam 
{
	ID3D11Device* device;
	ID3D11DeviceContext* context;
	DXCamera* camera;
};

class HipoModel
{
public:
	HipoModel();
	~HipoModel(void);

	void Initialize(sDevNCam deviceCam, eHipoKind hipoType);
	void InitializeModels(sDevNCam& deviceCam, eHipoKind hipoType);
	void drawModel(float, float, float, float angY = 0.f, float angZ = 0.f);

	eUpdateSt update(float deltaTime);

	void hitHipo(float cutNowTime);

private:
	CCuboT* mHipoCabeza;
	CCuboT* mHipoCuerpo;
	CCuboT* mHipoCuello;


	float mAnimPos, mAnimAng;	
	AnimLogic mAnims[2];

	float mAccTime = 0.f;
};
