#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "/ArcoEngineSAE23_cubos/ArcoEngineSAE23/ArcoEngine/scene/model/CuboT.h"

class HungryHippos
{
public:
	HungryHippos();
	~HungryHippos();

	void Initialize(ID3D11Device* device, ID3D11DeviceContext* context, DXCamera* camera, const std::wstring& textname, const std::string &modelname);
	void update(float elapsedTime);
	void draw();

	void drawModel(float x, float y, float z, float angDeg);

private:

	CCuboT* mHippoHead;
	CCuboT* mHippoNeck;
	CCuboT* mHippoBody;

	float neckLength;

	//std::vector<CCuboT*> mHippoHead;
	//std::vector<glm::vec3> posiciones;
};

