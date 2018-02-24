
cbuffer ShadowMapCubeViewProj : register( b0 )
{
    float4x4 cubeViewProj[6];
	int4 shadowDirectionsSize;
	int4 shadowDirections[6];
};

struct GS_OUTPUT
{
	float4 Pos: SV_POSITION;
	uint RTIndex : SV_RenderTargetArrayIndex;
};

[maxvertexcount(18)]
void PointShadowGenGS(triangle float4 InPos[3] : SV_Position, inout TriangleStream<GS_OUTPUT> OutStream)
{
	for (int i = 0; i < shadowDirectionsSize.x; ++i)
	{
		GS_OUTPUT output;
		int iFace = shadowDirections[i].x;
		
		output.RTIndex = iFace;
		
		for (int v = 0; v < 3; ++v)
		{
			output.Pos = mul(InPos[v], cubeViewProj[iFace]);
			OutStream.Append(output);
		}
		OutStream.RestartStrip();
	}
}