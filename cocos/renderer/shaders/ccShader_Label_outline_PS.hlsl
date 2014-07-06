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
	float4 u_effectColor;
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
	float4 sampledColor = g_Texture0.Sample(TextureSampler, input.texUV);
	float fontAlpha = sampledColor.g;
	float outlineAlpha = sampledColor.r;
	
	if (outlineAlpha <= 0.0)
		discard;

	float4 color = u_textColor * fontAlpha + u_effectColor * (1.0 - fontAlpha);
	return input.color * float4(color.rgb, max(fontAlpha, outlineAlpha) * color.a);	
}

