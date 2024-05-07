#pragma once
#include <d3d11.h>
#include <vector>
#include <fstream>
#include "../../scene/logic/UMath.h"

//const D3D11_INPUT_ELEMENT_DESC basicVertexLayoutDesc[] =
//{
//	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
//	//{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
//};

const D3D11_INPUT_ELEMENT_DESC posVertexLayoutDesc [] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

const unsigned int posVertexLayoutSize = ARRAYSIZE(posVertexLayoutDesc);

const D3D11_INPUT_ELEMENT_DESC posNorVertexLayoutDesc[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

const unsigned int posNorVertexLayoutSize = ARRAYSIZE(posNorVertexLayoutDesc);

const D3D11_INPUT_ELEMENT_DESC posTexVertexLayoutDesc[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

const unsigned int posTexVertexLayoutSize = ARRAYSIZE(posTexVertexLayoutDesc);

struct BasicPosVertex
{
	float pos[3];
};

struct BasicPosNorVertex
{
	float pos[3];
	float normal[3];
};

struct BasicTexVertex
{
	float pos[3];
	float normal[3];
	float tex[2];
};

struct sTransformBuffer
{
		MathUtil::CMatrix  model;
		MathUtil::CMatrix  view;
		MathUtil::CMatrix  projection;
};

struct sColorBuffer
{
	float color[4];
};

static void FillVectorWithFile(const std::string &name,
	std::vector<char> &mvec, int &size)
{
	std::ifstream fin(name, std::ios::binary);
	fin.seekg(0, std::ios_base::end);
	int szvec = static_cast<int>(fin.tellg());
	fin.seekg(0, std::ios_base::beg);

	mvec.clear();
	mvec.resize(szvec);
	fin.read(&mvec[0], szvec);
	fin.close();

	size = szvec;
}

