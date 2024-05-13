#include "HungryHippos.h"

HungryHippos::HungryHippos()
	: mHippoHead{ nullptr }, mHippoNeck{ nullptr }, mHippoBody{ nullptr }
{

}

HungryHippos::~HungryHippos()
{
	if (mHippoHead) delete mHippoHead;
	if (mHippoNeck) delete mHippoNeck;
	if (mHippoBody) delete mHippoBody;
}

void HungryHippos::Initialize(ID3D11Device* device, ID3D11DeviceContext* context, DXCamera* camera, const std::wstring &textname, const std::string &modelname)
{
	mHippoHead = new CCuboT(device, context);
	mHippoNeck = new CCuboT(device, context);
	mHippoBody = new CCuboT(device, context);

	mHippoHead->Initialize(camera, textname);
	mHippoNeck->Initialize(camera, textname);
	mHippoBody->Initialize(camera, textname);

	mHippoHead->InsertModel(modelname);
	mHippoNeck->InsertModel(modelname);
	mHippoBody->InsertModel(modelname);
}

void HungryHippos::update(float elapsedTime)
{

}

void HungryHippos::drawModel(float tx, float ty, float tz, float rx, float ry, float rz)
{
	mHippoHead->drawModel(tx, ty, tz, rx, ry, rz);
	mHippoNeck->drawModel(tx, ty, tz, rx, ry, rz);
	mHippoBody->drawModel(tx, ty, tz, rx, ry, rz);
}
