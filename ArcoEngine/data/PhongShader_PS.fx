cbuffer cbPerObject : register(b0)
{
	float4 g_vObjectColor;
};

static float4 ambientLight = { 1.0f, 1.0f, 1.0f, 1.0f };
static float4 lightColor = { 1.0f, 1.0f, 1.0f, 1.0f };
static float3 lightDir = { 1.0f, -1.0f, 0.0f };

static float MKa = 0.1f;
static float MKd = 0.5f;
static float MKs = 0.5f;
static float MA = 30.0f;

struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float3 n : TEXCOORD;
	float3 h : TEXCOORD1;
};

float4 calcBlinnPhongLighting(float4 LColor, float3 N, float3 L, float3 H)
{
	float4 Ia = MKa * ambientLight;
	float4 Id = MKd * saturate(dot(N, L));
	float4 Is = MKs * pow(saturate(dot(N, H)), MA);

	return Ia + (Id + Is) * LColor;
}

float4 main( VS_OUTPUT input ) : SV_Target
{
	input.n = normalize(input.n);
	input.h = normalize(input.h);
	float4 I = calcBlinnPhongLighting(lightColor, input.n, -lightDir, input.h);

	return I * g_vObjectColor;
}
