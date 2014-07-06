// A constant buffer that stores the three basic column-major matrices for composing geometry.
cbuffer ConstantBuffer : register(b0)
{
	matrix MVP;	
};

// Per-vertex data used as input to the vertex shader.
struct VertexShaderInput
{
	float3 pos : POSITION;
	float4 color : COLOR0;
	float2 texUV : TEXCOORD0;
};

// Per-pixel color data passed through the pixel shader.
struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float4 color : COLOR0;
	float2 texUV : TEXCOORD0;
};

// Simple shader to do vertex processing on the GPU.
PixelShaderInput main(VertexShaderInput input)
{
	PixelShaderInput output;
	float4 pos = float4(input.pos, 1.0f);

	// Transform the vertex position into projected space.
	output.pos = mul(pos, MVP);

	// Pass the color through without modification.
	output.color = input.color;
	output.texUV = input.texUV;

	return output;
}
