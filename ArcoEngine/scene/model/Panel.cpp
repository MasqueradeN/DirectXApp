#include <d3d11.h>
#include <cmath>
#include "Panel.h"
#include "../../render/materials/MaterialTexture.h"

void CPanel::InsertModel()
{
	if (mpDevice == nullptr)
		return;
	vertexVectorType vertices{
		{ {	 0.2f,  0.2f,  0.f }, { 0.f, 0.f, -1.f },	{ 1.f, 0.f } },
		{ { -0.2f,  0.2f,  0.f }, { 0.f, 0.f, -1.f },	{ 0.f, 0.f } },
		{ { -0.2f, -0.2f,  0.f }, { 0.f, 0.f, -1.f },	{ 0.f, 1.f } },
		{ {  0.2f, -0.2f,  0.f }, { 0.f, 0.f, -1.f },	{ 1.f, 1.f } },
	};
	mAllModelsVertices.insert(mAllModelsVertices.end(), vertices.begin(), vertices.end());

	std::vector<unsigned short> indices{
		0, 3, 1,  3, 2, 1
	};
	mAllModelsIndices.insert(mAllModelsIndices.end(), indices.begin(), indices.end());

	setBuffers();
}

void CPanel::drawModel(float lx, float ly, float lz)
{
	setShaders();
	setRenderProperties();
	activateBuffers();
	ID3D11Buffer *conbuf = mMaterialTexture->GetVConstantBuffer0();

	MathUtil::CMatrix translation =
		MathUtil::MatrixTranslation(lx, ly, lz);
	translation = MathUtil::MatrixTranspose(translation);
	
	mpContext->UpdateSubresource(conbuf, 0, nullptr, &translation, 0, 0);
	mpContext->VSSetConstantBuffers(0, 1, &conbuf);

	mpContext->DrawIndexed(mIndexBufferSize, 0, 0);
}
