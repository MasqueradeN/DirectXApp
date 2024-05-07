cbuffer cbPerObject : register(b0)
{
	float4 g_vObjectColor;
};

struct VS_OUTPUT
{
		float4 Pos : SV_POSITION;
};

float4 main( VS_OUTPUT input ) : SV_Target
{
	return g_vObjectColor;
}
