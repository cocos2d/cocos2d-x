Texture2D g_Texture0;

SamplerState TextureSampler
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

// A constant buffer that stores the three basic column-major matrices for composing geometry.
cbuffer ConstantBuffer : register(b0)
{	
	float4 u_textColor;
};

// Per-pixel color data passed through the pixel shader.
struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float4 color : COLOR0;
	float2 texUV : TEXCOORD0;
};

// A pass-through function for the (interpolated) color data.
float4 main(PixelShaderInput input) : SV_TARGET
{		
	return input.color *  float4(u_textColor.rgb,	// RGB from uniform
								 u_textColor.a * g_Texture0.Sample(TextureSampler, input.texUV).a); // A from texture & uniform
}
