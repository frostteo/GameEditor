
struct VS_OUTPUT
{
	float4 position : SV_Position;
	float2 tex : TEXCOORD0;
};

static const float2 positions[4] = 
{
	float2(-1.0f, 1.0f),
	float2(1.0f, 1.0f),
	float2(-1.0f, -1.0f),
	float2(1.0f, -1.0f)
};

static const float2 texturePos[4] = 
{
	float2(0.0f, 0.0f),
	float2(1.0f, 0.0f),
	float2(0.0f, 1.0f),
	float2(1.0f, 1.0f)
};

VS_OUTPUT AmbientVertexShader(uint VertexID : SV_VertexID)
{
	VS_OUTPUT output;
	output.position = float4(positions[VertexID].xy, 0.0f, 1.0f);
	output.tex = texturePos[VertexID];
	return output;
}