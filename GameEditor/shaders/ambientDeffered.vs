
struct VS_OUTPUT
{
	float4 position : SV_Position;
	float2 cpPos: TEXCOORD0;
};

static const float2 positions[4] = 
{
	float2(-1.0f, 1.0f),
	float2(1.0f, 1.0f),
	float2(-1.0f, -1.0f),
	float2(1.0f, -1.0f)
};

VS_OUTPUT AmbientVertexShader(uint VertexID : SV_VertexID)
{
	VS_OUTPUT output;
	output.position = float4(positions[VertexID].xy, 0.0f, 1.0f);
	output.cpPos = output.position.xy;
	return output;
}