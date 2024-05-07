#include <d3d11.h>
#include <cmath>
#include <new>
#include "Cubo.h"

void CCubo::InsertModel()
{
	if (mpDevice == nullptr)
		return;

	vertexVectorType vertices{
		{ {  0.5f,  0.5f, -0.5f } },
		{ { -0.5f,  0.5f, -0.5f } },	
		{ { -0.5f, -0.5f, -0.5f } },
		{ {  0.5f, -0.5f, -0.5f } },
			  
		{ {  0.5f,  0.5f,  0.5f } },
		{ { -0.5f,  0.5f,  0.5f } },
		{ { -0.5f, -0.5f,  0.5f } },
		{ {  0.5f, -0.5f,  0.5f } },

	};
	mAllModelsVertices.insert(mAllModelsVertices.end(), vertices.begin(), vertices.end());

	std::vector<unsigned short> indices{
		0, 3, 1,  3, 2, 1,  0, 4, 7,  0, 7, 3,
		4, 5, 6,  4, 6, 7,  5, 1, 2,  5, 2, 6,
		5, 4, 0,  5, 0, 1,  2, 3, 7,  2, 7, 6
	};
	mAllModelsIndices.insert(mAllModelsIndices.end(), indices.begin(), indices.end());

	setBuffers();
}

void CCubo::drawModel(float lx, float ly, float lz)
{
	setShaders();
	setRenderProperties();
	activateBuffers();
	ID3D11Buffer *conbuf = mMaterialColor->GetVConstantBuffer0();

	MathUtil::CMatrix translation =
		MathUtil::MatrixTranslation(lx, ly, lz);
	translation = MathUtil::MatrixTranspose(translation);
	
	mpContext->UpdateSubresource(conbuf, 0, nullptr, &translation, 0, 0);
	mpContext->VSSetConstantBuffers(0, 1, &conbuf);

	mpContext->DrawIndexed(mIndexBufferSize, 0, 0);
}

//void CCubo::drawModel(cubeInfo *info)
//{
//	setRenderProperties();
//	activateBuffers();
//	ID3D11Buffer *conbuf = mMaterialColor->GetVConstantBuffer0();
//
//	MathUtil::CMatrix translation =
//		MathUtil::MatrixTranslation(info->x, info->y, info->z);
//	translation = MathUtil::MatrixTranspose(translation);
//
//	mpContext->UpdateSubresource(conbuf, 0, nullptr, &translation, 0, 0);
//	mpContext->VSSetConstantBuffers(0, 1, &conbuf);
//
//	mpContext->DrawIndexed(mIndexBufferSize, 0, 0);
//}
//
//void CCubo::drawModel()
//{
//	setRenderProperties();
//	activateBuffers();
//	ID3D11Buffer *conbuf = mMaterialColor->GetVConstantBuffer0();
//
//	MathUtil::CMatrix translation =
//		MathUtil::MatrixTranslation(mcubeInfo.x, mcubeInfo.y, mcubeInfo.z);
//	translation = MathUtil::MatrixTranspose(translation);
//
//	mpContext->UpdateSubresource(conbuf, 0, nullptr, &translation, 0, 0);
//	mpContext->VSSetConstantBuffers(0, 1, &conbuf);
//
//	mpContext->DrawIndexed(mIndexBufferSize, 0, 0);
//}