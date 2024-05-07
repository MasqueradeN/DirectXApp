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
	float3 normal : NORMAL;
};

struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	//float2 t : TEXCOORD;
	float3 n : TEXCOORD;
	float3 h : TEXCOORD1;
};

//struct VS_OUTPUT
//{
//	float4 pos : SV_POSITION;
//	float4 color : COLOR;
//};

//float4 ambientLight = { 1.0f, 1.0f, 1.0f, 1.0f };
static float4 lightColor = { 1.0f, 1.0f, 1.0f, 1.0f };
static float3 eye = { 10.0f, 10.0f, -10.0f };
static float3 lightDir = { 1.0f, -1.0f, 0.0f };
//
//float MKa = 0.1f;
//float MKd = 0.5f;
//float MKs = 0.5f;
//float MA = 30;



VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	input.pos = mul(input.pos, model);
	output.pos = mul(input.pos, view);
	output.pos = mul(output.pos, projection);

	float3 V = normalize(eye - (float3) input.pos);
	output.n = normalize(mul(input.normal, (float3x3)model));
	output.h = normalize(-lightDir + V);

	//float3 N = normalize(mul(input.n, (float3x3) World));
	//float3 V = normalize(eye - (float3) input.p);
	//float3 H = normalize(-light.dir + V);

	//output.i = calcBlinnPhongLighting(lightColor, N, -lightDir, H);

	return output;
}


