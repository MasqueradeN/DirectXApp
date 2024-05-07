cbuffer modelBuffer : register(b0)
{
	matrix model;
};

cbuffer viewBuffer : register(b1)
{
	matrix view;
};

cbuffer projectionBuffer : register(b2)
{
	matrix projection;
};

struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
};

VS_OUTPUT main(float4 Pos : POSITION)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.Pos = mul(Pos, model);
	output.Pos = mul(output.Pos, view);
	output.Pos = mul(output.Pos, projection);
	return output;
}


