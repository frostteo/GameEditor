
cbuffer MatrixBuffer
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

struct VertexInputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
	float2 cpPos: TEXCOORD0;
};

PixelInputType PointLightVertexShader(VertexInputType input)
{
    PixelInputType output;
    input.position.w = 1.0f;
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
	output.cpPos = output.position.xy / output.position.w;
    return output;
}
