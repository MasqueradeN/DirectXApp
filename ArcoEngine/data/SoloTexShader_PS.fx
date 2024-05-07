Texture2D txDiffuse : register(t0);
SamplerState samLinear : register(s0);

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
	float2 t : TEXCOORD;
};

float4 main( VS_OUTPUT input ) : SV_Target
{
	return txDiffuse.Sample(samLinear, input.t);
}
