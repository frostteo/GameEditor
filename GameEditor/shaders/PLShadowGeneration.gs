
cbuffer ShadowMapCubeViewProj : register( b0 )
{
    float4x4 cubeViewProj[6] : packoffset(c0);
};

struct GS_OUTPUT
{
	float4 Pos: SV_POSITION;
	uint RTIndex : SV_RenderTargetArrayIndex;
};

[maxvertexcount(18)]
void PointShadowGenGS(triangle float4 InPos[3] : SV_Position, inout TriangleStream<GS_OUTPUT> OutStream)
{
	for (int iFace = 0; iFace < 6; ++iFace)
	{
		GS_OUTPUT output;
		
		output.RTIndex = iFace;
		
		for (int v = 0; v < 3; ++v)
		{
			output.Pos = mul(InPos[v], cubeViewProj[iFace]);
			OutStream.Append(output);
		}
		OutStream.RestartStrip();
	}
}