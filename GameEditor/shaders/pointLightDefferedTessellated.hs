
struct HS_CONSTANT_DATA_OUTPUT
{
	float Edges[4] : SV_TessFactor;
	float Inside[2] : SV_InsideTessFactor; 
};

HS_CONSTANT_DATA_OUTPUT PointLightConstantHS()
{
	HS_CONSTANT_DATA_OUTPUT Output;

	float tessFactor = 18.0f;
	Output.Edges[0] = Output.Edges[1] = Output.Edges[2] = Output.Edges[3] = tessFactor;
	Output.Inside[0] = Output.Inside[1] = tessFactor;
	
	return Output;
}

static const float3 HemiDir[2] = {
	float3(1.0f, 1.0f, 1.0f),
	float3(-1.0f, 1.0f, -1.0f)
};

struct HS_OUTPUT
{
	float3 HemiDir : POSITION;
};

[domain("quad")]
[partitioning("integer")]
[outputtopology("triangle_ccw")]
[outputcontrolpoints(4)]
[patchconstantfunc("PointLightConstantHS")]
HS_OUTPUT PointLightHS(uint PatchID : SV_PrimitiveID) : POSITION
{
	HS_OUTPUT Output;
	
	Output.HemiDir = HemiDir[PatchID];
	
	return Output;
}