// A constant buffer that stores the three basic column-major matrices for composing geometry.
cbuffer ModelViewProjectionConstantBuffer : register(b0)
{
	matrix model;
	matrix view;
	matrix projection;
};

// Per-vertex data used as input to the vertex shader.
struct VertexShaderInput
{
	float3 pos : POSITION;
	float3 color : COLOR0;
};

// Per-pixel color data passed through the pixel shader.
struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float3 color : COLOR0;
};

// Simple shader to do vertex processing on the GPU.
PixelShaderInput main(VertexShaderInput input)
{
	PixelShaderInput output;
	float4 pos = float4(input.pos, 1.0f);

		// Transform the vertex position into projected space.
		pos = mul(pos, model);
	pos = mul(pos, view);
	pos = mul(pos, projection);
	output.pos = pos;

	// Pass the color through without modification.
	output.color = input.color;

	return output;
}
//
//const char* ccPositionColorLengthTexture_vert = STRINGIFY(
//
//\n#ifdef GL_ES\n
//attribute mediump vec4 a_position;
//attribute mediump vec2 a_texcoord;
//attribute mediump vec4 a_color;
//
//varying mediump vec4 v_color;
//varying mediump vec2 v_texcoord;
//
//\n#else\n
//
//attribute vec4 a_position;
//attribute vec2 a_texcoord;
//attribute vec4 a_color;
//
//varying vec4 v_color;
//varying vec2 v_texcoord;
//
//\n#endif\n
//
//void main()
//{
//    v_color = vec4(a_color.rgb * a_color.a, a_color.a);
//    v_texcoord = a_texcoord;
//
//    gl_Position = CC_MVPMatrix * a_position;
//}
//);
