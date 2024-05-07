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

struct VS_INPUT
{
	float4 pos : POSITION;
	float2 tex : TEXCOORD;
	float3 normal : NORMAL;
};

struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float2 t : TEXCOORD;
};

static float3 eye = { 10.0f, 10.0f, -10.0f };
static float3 lightDir = { 1.0f, -1.0f, 0.0f };

VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	input.pos = mul(input.pos, model);
	output.pos = input.pos;
	//output.pos = mul(input.pos, view);
	//output.pos = mul(output.pos, projection);

	output.t = input.tex;
	return output;
}


