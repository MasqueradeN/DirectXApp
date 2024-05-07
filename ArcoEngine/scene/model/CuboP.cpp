#include <d3d11.h>
#include <cmath>
#include <new>
#include "CuboP.h"
#include "../../render/materials/MaterialPhongColor.h"

void CCuboP::InsertModel()
{
	if (mpDevice == nullptr)
		return;
	const float i3r = 0.57735027f;
	vertexVectorType vertices{
		{ {  0.5f,  0.5f, -0.5f }, { i3r, i3r, -i3r } },
		{ { -0.5f,  0.5f, -0.5f }, { -i3r, i3r, -i3r } },
		{ { -0.5f, -0.5f, -0.5f }, { -i3r, -i3r, -i3r } },
		{ {  0.5f, -0.5f, -0.5f }, { i3r, -i3r, -i3r } },
			  
		{ {  0.5f,  0.5f,  0.5f }, { i3r, i3r, i3r } },
		{ { -0.5f,  0.5f,  0.5f }, { -i3r, i3r, i3r } },
		{ { -0.5f, -0.5f,  0.5f }, { -i3r, -i3r, i3r } },
		{ {  0.5f, -0.5f,  0.5f }, { i3r, -i3r, i3r } },

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

void CCuboP::drawModel(float lx, float ly, float lz , float rx, float ry, float rz)
{
	setShaders();
	setRenderProperties();
	activateBuffers();
	ID3D11Buffer *conbuf = mMaterialColor->GetVConstantBuffer0();

	MathUtil::CMatrix translation =
		MathUtil::MatrixTranslation(lx, ly, lz);
	translation = MathUtil::MatrixTranspose(translation);
	MathUtil::CMatrix rotationx = MathUtil::MatrixRotationX(rx);
	MathUtil::CMatrix rotationy = MathUtil::MatrixRotationY(ry);	
	MathUtil::CMatrix rotationz = MathUtil::MatrixRotationZ(rz);
	MathUtil::CMatrix rotation = MathUtil::Multiply(rotationx, rotationy);
	rotation = MathUtil::Multiply(rotation, rotationz);
	MathUtil::CMatrix transform = MathUtil::Multiply(rotation, translation);
	
	mpContext->UpdateSubresource(conbuf, 0, nullptr, &transform , 0, 0);

	mpContext->VSSetConstantBuffers(0, 1, &conbuf);

	mpContext->DrawIndexed(mIndexBufferSize, 0, 0);
}
