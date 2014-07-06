Texture2D g_Texture0;

SamplerState TextureSampler
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

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
	float4 color = g_Texture0.Sample(TextureSampler, input.texUV);
	//the texture use dual channel 16-bit output for distance_map \n
	//float dist = color.b+color.g/256.0; \n
	// the texture use single channel 8-bit output for distance_map \n
	float dist = color.a; 
	//todo:Implementation 'fwidth' for glsl 1.0 \n
	//float width = fwidth(dist); \n
	//assign width for constant will lead to a little bit fuzzy,it's temporary measure.\n
	float width = 0.04; 
	float alpha = smoothstep(0.5-width, 0.5+width, dist) * u_textColor.a; 
	return input.color * float4(u_textColor.rgb, alpha);
}

