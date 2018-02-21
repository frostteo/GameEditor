
cbuffer WorldMatrixBuffer : register( b0 )
{
    matrix worldMatrix;
};

float4 PointShadowGenVS(float4 Pos : POSITION) : SV_Position
{
	Pos.w = 1.0f;
	return mul(Pos, worldMatrix);
}