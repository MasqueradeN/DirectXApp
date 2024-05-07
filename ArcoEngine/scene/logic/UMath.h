#pragma once
#include <vector>
#include <memory>
#include <mutex>

struct phyVector2D
{
	float x;
	float y;
};

struct phyVector3D
{
	float x;
	float y;
	float z;
};

namespace MathUtil
{
	static float Pi = 3.14159265359f;
	struct sVector4f
	{
		float f[4];
	};

	struct sVector4u
	{
		uint32_t u[4];
	};

	struct CMatrix
	{
		sVector4f r[4];
	};

	static CMatrix MatrixIdentity()
	{
		CMatrix M;
		M.r[0] = { { 1.0f, 0.0f, 0.0f, 0.0f } };
		M.r[1] = { { 0.0f, 1.0f, 0.0f, 0.0f } };
		M.r[2] = { { 0.0f, 0.0f, 1.0f, 0.0f } };
		M.r[3] = { { 0.0f, 0.0f, 0.0f, 1.0f } };
		return M;
	}

	static CMatrix MatrixTranslation(float OffsetX, float OffsetY, float OffsetZ)
	{
		CMatrix M;
		M.r[0] = { { 1.0f, 0.0f, 0.0f, 0.0f } };
		M.r[1] = { { 0.0f, 1.0f, 0.0f, 0.0f } };
		M.r[2] = { { 0.0f, 0.0f, 1.0f, 0.0f } };
		M.r[3] = { { OffsetX, OffsetY, OffsetZ, 1.f } };
		return M;
	}

	static CMatrix MatrixScale(float kx, float ky, float kz) 
	{
		CMatrix M;
		M.r[0] = { { kx, 0.0f, 0.0f, 0.0f } };
		M.r[1] = { { 0.0f, ky, 0.0f, 0.0f } };
		M.r[2] = { { 0.0f, 0.0f, kz, 0.0f } };
		M.r[3] = { { 0.0f, 0.0f, 0.0f, 1.0f } };
		return M;
	}

	static CMatrix MatrixRotationX(float angle)
	{
		CMatrix M;
		M.r[0] = { { 1.0f, 0.0f, 0.0f, 0.0f } };
		M.r[1] = { { 0.0f, cosf(angle), sinf(angle), 0.0f } };
		M.r[2] = { { 0.0f, -sinf(angle), cosf(angle), 0.0f } };
		M.r[3] = { { 0.0f, 0.0f, 0.0f, 1.0f } };
		return M;
	}

	static CMatrix MatrixRotationY(float angle)
	{
		CMatrix M;
		M.r[0] = { { cosf(angle), 0.0f, sinf(angle), 0.0f } };
		M.r[1] = { { 0.0f, 1.0f, 0.0f, 0.0f } };
		M.r[2] = { { -sinf(angle), 0.0f, cosf(angle), 0.0f } };
		M.r[3] = { { 0.0f, 0.0f, 0.0f, 1.0f } };
		return M;
	}

	static CMatrix MatrixRotationZ(float angle)
	{
		CMatrix M;
		M.r[0] = { { cosf(angle), sinf(angle), 0.0f, 0.0f } };
		M.r[1] = { { -sinf(angle), cosf(angle), 0.0f, 0.0f } };
		M.r[2] = { { 0.0f, 0.0f, 1.0f, 0.0f } };
		M.r[3] = { { 0.0f, 0.0f, 0.0f, 1.0f } };
		return M;
	}

	static CMatrix Multiply(const CMatrix& M1, const CMatrix& M2)
	{
		CMatrix mResult;
		// Cache the invariants in registers
		float x = M1.r[0].f[0];
		float y = M1.r[0].f[1];
		float z = M1.r[0].f[2];
		float w = M1.r[0].f[3];
		// Perform the operation on the first row
		mResult.r[0].f[0] = (M2.r[0].f[0] * x) + (M2.r[1].f[0] * y) + (M2.r[2].f[0] * z) + (M2.r[3].f[0] * w);
		mResult.r[0].f[1] = (M2.r[0].f[1] * x) + (M2.r[1].f[1] * y) + (M2.r[2].f[1] * z) + (M2.r[3].f[1] * w);
		mResult.r[0].f[2] = (M2.r[0].f[2] * x) + (M2.r[1].f[2] * y) + (M2.r[2].f[2] * z) + (M2.r[3].f[2] * w);
		mResult.r[0].f[3] = (M2.r[0].f[3] * x) + (M2.r[1].f[3] * y) + (M2.r[2].f[3] * z) + (M2.r[3].f[3] * w);
		// Repeat for all the other rows
		x = M1.r[1].f[0];
		y = M1.r[1].f[1];
		z = M1.r[1].f[2];
		w = M1.r[1].f[3];
		mResult.r[1].f[0] = (M2.r[0].f[0] * x) + (M2.r[1].f[0] * y) + (M2.r[2].f[0] * z) + (M2.r[3].f[0] * w);
		mResult.r[1].f[1] = (M2.r[0].f[1] * x) + (M2.r[1].f[1] * y) + (M2.r[2].f[1] * z) + (M2.r[3].f[1] * w);
		mResult.r[1].f[2] = (M2.r[0].f[2] * x) + (M2.r[1].f[2] * y) + (M2.r[2].f[2] * z) + (M2.r[3].f[2] * w);
		mResult.r[1].f[3] = (M2.r[0].f[3] * x) + (M2.r[1].f[3] * y) + (M2.r[2].f[3] * z) + (M2.r[3].f[3] * w);
		x = M1.r[2].f[0];
		y = M1.r[2].f[1];
		z = M1.r[2].f[2];
		w = M1.r[2].f[3];
		mResult.r[2].f[0] = (M2.r[0].f[0] * x) + (M2.r[1].f[0] * y) + (M2.r[2].f[0] * z) + (M2.r[3].f[0] * w);
		mResult.r[2].f[1] = (M2.r[0].f[1] * x) + (M2.r[1].f[1] * y) + (M2.r[2].f[1] * z) + (M2.r[3].f[1] * w);
		mResult.r[2].f[2] = (M2.r[0].f[2] * x) + (M2.r[1].f[2] * y) + (M2.r[2].f[2] * z) + (M2.r[3].f[2] * w);
		mResult.r[2].f[3] = (M2.r[0].f[3] * x) + (M2.r[1].f[3] * y) + (M2.r[2].f[3] * z) + (M2.r[3].f[3] * w);
		x = M1.r[3].f[0];
		y = M1.r[3].f[1];
		z = M1.r[3].f[2];
		w = M1.r[3].f[3];
		mResult.r[3].f[0] = (M2.r[0].f[0] * x) + (M2.r[1].f[0] * y) + (M2.r[2].f[0] * z) + (M2.r[3].f[0] * w);
		mResult.r[3].f[1] = (M2.r[0].f[1] * x) + (M2.r[1].f[1] * y) + (M2.r[2].f[1] * z) + (M2.r[3].f[1] * w);
		mResult.r[3].f[2] = (M2.r[0].f[2] * x) + (M2.r[1].f[2] * y) + (M2.r[2].f[2] * z) + (M2.r[3].f[2] * w);
		mResult.r[3].f[3] = (M2.r[0].f[3] * x) + (M2.r[1].f[3] * y) + (M2.r[2].f[3] * z) + (M2.r[3].f[3] * w);
		return mResult;
	}

	static CMatrix MatrixTranspose(CMatrix matrix)
	{
		sVector4f temp0 = { { matrix.r[0].f[0], matrix.r[1].f[0], matrix.r[2].f[0], matrix.r[3].f[0] } };
		sVector4f temp1 = { { matrix.r[0].f[1], matrix.r[1].f[1], matrix.r[2].f[1], matrix.r[3].f[1] } };
		sVector4f temp2 = { { matrix.r[0].f[2], matrix.r[1].f[2], matrix.r[2].f[2], matrix.r[3].f[2] } };
		sVector4f temp3 = { { matrix.r[0].f[3], matrix.r[1].f[3], matrix.r[2].f[3], matrix.r[3].f[3] } };

		CMatrix M;
		M.r[0] = temp0;
		M.r[1] = temp1;
		M.r[2] = temp2;
		M.r[3] = temp3;
		return M;
	}

	static sVector4f VectorSubtract(sVector4f v1, sVector4f v2)
	{
		sVector4f temp = { { v1.f[0] - v2.f[0], v1.f[1] - v2.f[1], v1.f[2] - v2.f[2], v1.f[3] - v2.f[3] } };
		return temp;
	}

	static sVector4f Vector3Normalize(sVector4f v)
	{
		float magnitude = v.f[0] * v.f[0] + v.f[1] * v.f[1] + v.f[2] * v.f[2];
		magnitude = sqrtf(magnitude);
		sVector4f temp = { { v.f[0] / magnitude, v.f[1] / magnitude, v.f[2] / magnitude, v.f[3] / magnitude } };
		return temp;
	}

	static sVector4f Vector3Cross(sVector4f v1, sVector4f v2)
	{
		sVector4f vResult = {
			(v1.f[1] * v2.f[2]) - (v1.f[2] * v2.f[1]),
			(v1.f[2] * v2.f[0]) - (v1.f[0] * v2.f[2]),
			(v1.f[0] * v2.f[1]) - (v1.f[1] * v2.f[0]),
			0.0f
		};
		return vResult;
	}

	static sVector4f VectorNegate(sVector4f v)
	{
		sVector4f Result;
		Result.f[0] = -v.f[0];
		Result.f[1] = -v.f[1];
		Result.f[2] = -v.f[2];
		Result.f[3] = -v.f[3];
		return Result;
	}

	static sVector4f Vector3Dot(sVector4f v1, sVector4f v2)
	{
		float fValue = 
			v1.f[0] * v2.f[0] + 
			v1.f[1] * v2.f[1] + 
			v1.f[2] * v2.f[2];
		sVector4f vResult = {
			fValue,	fValue,	fValue,	fValue
		};
		return vResult;
	}
	
	static CMatrix MatrixLookToLH(sVector4f EyePosition,
		sVector4f EyeDirection, sVector4f UpDirection)
	{

		sVector4f R2 = Vector3Normalize(EyeDirection);

		sVector4f R0 = Vector3Cross(UpDirection, R2);
		R0 = Vector3Normalize(R0);

		sVector4f R1 = Vector3Cross(R2, R0);

		sVector4f NegEyePosition = VectorNegate(EyePosition);

		sVector4f D0 = Vector3Dot(R0, NegEyePosition);
		sVector4f D1 = Vector3Dot(R1, NegEyePosition);
		sVector4f D2 = Vector3Dot(R2, NegEyePosition);

		CMatrix M;
		M.r[0] = { { R0.f[0], R0.f[1], R0.f[2], D0.f[3] } };
		M.r[1] = { { R1.f[0], R1.f[1], R1.f[2], D1.f[3] } };
		M.r[2] = { { R2.f[0], R2.f[1], R2.f[2], D2.f[3] } };
		M.r[3] = { { 0.0f, 0.0f, 0.0f, 1.0f } };

		M = MatrixTranspose(M);
		return M;
	}

	static CMatrix MatrixLookAtLH(sVector4f EyePosition, 
		sVector4f FocusPosition, sVector4f UpDirection)
	{
		sVector4f EyeDirection = VectorSubtract(FocusPosition, EyePosition);
		return MatrixLookToLH(EyePosition, EyeDirection, UpDirection);
	}

	static CMatrix MatrixPerspectiveFovLH(
		float FovAngleY, float AspectHByW, float NearZ, float FarZ)
	{
		float sinFov = sinf(0.5f * FovAngleY);
		float cosFov = cosf(0.5f * FovAngleY);
		float Height = cosFov / sinFov;
		float Width = Height / AspectHByW;
		float fRange = FarZ / (FarZ - NearZ);

		CMatrix M;
		M.r[0] = { { Width, 0.0f, 0.0f, 0.0f } };
		M.r[1] = { { 0.0f, Height, 0.0f, 0.0f } };
		M.r[2] = { { 0.0f, 0.0f, fRange, 1.0f } };
		M.r[3] = { { 0.0f, 0.0f, -fRange * NearZ, 0.0f } };
		return M;
	}

};