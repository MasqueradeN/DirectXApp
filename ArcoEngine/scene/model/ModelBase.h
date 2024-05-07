#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "../model/tiny_obj_loader.h"

class MaterialBase;
struct D3D11_INPUT_ELEMENT_DESC;
struct ID3D11Buffer;
struct ID3D11Device;
struct ID3D11DeviceContext;

struct PosNorTexVertex
{
	float pos[3];
	float normal[3];
	float texcoords[2];
};

struct sObjMesh
{
	std::vector<PosNorTexVertex> mVertices;
	std::vector<unsigned short> mIndices;
};

template <typename VSRT>
class CModelBase
{
public:
	virtual ~CModelBase(void) 
	{
		if (mpVertexBuffer != nullptr) {
			mpVertexBuffer->Release();
			mpVertexBuffer = nullptr;
		}
		if (mpIndexBuffer != nullptr)	{
			mpIndexBuffer->Release();
			mpIndexBuffer = nullptr;
		}
	}

	void Initialize(MaterialBase *materialBase)
	{
		mMaterialBase = materialBase;
	}

	ID3D11Buffer *GetVertices()				{ return mpVertexBuffer;		}
	ID3D11Buffer *GetIndices()				{ return mpIndexBuffer;			}
	unsigned int GetIndexBufferSize() { return mIndexBufferSize;	}

protected:
	CModelBase(ID3D11Device *device, ID3D11DeviceContext *context)
		: mpVertexBuffer(nullptr), mpIndexBuffer(nullptr)
		, mIndexBufferSize(0), mpDevice(device), mpContext(context)
	{	}
	
	void setBuffers()
	{
		if (mpDevice == nullptr)
			return;

		mIndexBufferSize = static_cast<unsigned int>(mAllModelsIndices.size());

		D3D11_BUFFER_DESC vertexBufferDesc = { 0 };
		vertexBufferDesc.ByteWidth =
			sizeof(VSRT) * static_cast<unsigned int>(mAllModelsVertices.size());
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = 0;
		vertexBufferDesc.MiscFlags = 0;
		vertexBufferDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA vertexBufferData;
		vertexBufferData.pSysMem = &mAllModelsVertices[0];
		vertexBufferData.SysMemPitch = 0;
		vertexBufferData.SysMemSlicePitch = 0;

		mpDevice->CreateBuffer(
			&vertexBufferDesc, &vertexBufferData, &mpVertexBuffer);

		if (mAllModelsIndices.size() > 0)
		{
			D3D11_BUFFER_DESC indexBufferDesc;
			indexBufferDesc.ByteWidth =
				sizeof(unsigned short) * static_cast<unsigned int>(mAllModelsIndices.size());
			indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
			indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			indexBufferDesc.CPUAccessFlags = 0;
			indexBufferDesc.MiscFlags = 0;
			indexBufferDesc.StructureByteStride = 0;

			D3D11_SUBRESOURCE_DATA indexBufferData;
			indexBufferData.pSysMem = &mAllModelsIndices[0];
			indexBufferData.SysMemPitch = 0;
			indexBufferData.SysMemSlicePitch = 0;

			mpDevice->CreateBuffer(
				&indexBufferDesc, &indexBufferData, &mpIndexBuffer);
		}

	}
	void setShaders()
	{
		ID3D11VertexShader *vshader = mMaterialBase->GetVertexShader();
		ID3D11PixelShader *pshader = mMaterialBase->GetPixelShader();
		mpContext->VSSetShader(vshader, nullptr, 0);
		mpContext->PSSetShader(pshader, nullptr, 0);

		ID3D11InputLayout *inlay = mMaterialBase->GetInputLayout();
		mpContext->IASetInputLayout(inlay);
	}

	void activateBuffers()
	{
		unsigned int stride = sizeof(VSRT);
		unsigned int offset = 0;
		mpContext->IASetVertexBuffers(0, 1, &mpVertexBuffer, &stride, &offset);
		mpContext->IASetIndexBuffer(mpIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
		mpContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	void activateLineBuffers()
	{
		unsigned int stride = sizeof(VSRT);
		unsigned int offset = 0;
		mpContext->IASetVertexBuffers(0, 1, &mpVertexBuffer, &stride, &offset);
		mpContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	}

	sObjMesh loadModelToVertices(const std::string& modelname, int meshIdx)
	{
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		
		std::string err;
		std::string warn;
		bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, modelname.c_str());
		
		if (!err.empty()) { std::cout << err << std::endl; }
		if (!ret) { exit(1); }

		std::vector<PosNorTexVertex> vertices;
		std::vector<unsigned short> indices;
		size_t index_offset = 0;
		
		for (size_t f = 0; f < shapes[meshIdx].mesh.num_face_vertices.size(); f++)
		{
			int fv = shapes[meshIdx].mesh.num_face_vertices[f];
			for (size_t v = 0; v < fv; v++)
			{
				tinyobj::index_t idx = shapes[meshIdx].mesh.indices[index_offset + v];
				PosNorTexVertex allv;
				allv.pos[0] = attrib.vertices[3 * idx.vertex_index + 0];
				allv.pos[1] = attrib.vertices[3 * idx.vertex_index + 1];
				allv.pos[2] = attrib.vertices[3 * idx.vertex_index + 2];
		
				allv.normal[0] = attrib.normals[3 * idx.normal_index + 0];
				allv.normal[1] = attrib.normals[3 * idx.normal_index + 1];
				allv.normal[2] = attrib.normals[3 * idx.normal_index + 2];
		
				allv.texcoords[0] = attrib.texcoords[2 * idx.texcoord_index + 0];
				allv.texcoords[1] = 1 - attrib.texcoords[2 * idx.texcoord_index + 1];
		
				indices.push_back(idx.vertex_index);
				vertices.push_back(allv);
			}
			index_offset += fv;
		}

		return sObjMesh{ {vertices}, {indices} };
	}

protected:
	MaterialBase *mMaterialBase;

	typedef std::vector<VSRT> vertexVectorType;
	std::vector<VSRT> mAllModelsVertices;
	std::vector<unsigned short> mAllModelsIndices;

	ID3D11Buffer *mpVertexBuffer;
	ID3D11Buffer *mpIndexBuffer;
	ID3D11Device *mpDevice;
	ID3D11DeviceContext *mpContext;
	unsigned int mIndexBufferSize;
};
