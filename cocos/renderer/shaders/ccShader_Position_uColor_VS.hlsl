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
//const char* ccPosition_uColor_vert = STRINGIFY(
//
//attribute vec4 a_position;
//uniform vec4 u_color;
//uniform float u_pointSize;
//
//\n#ifdef GL_ES\n
//varying lowp vec4 v_fragmentColor;
//\n#else\n
//varying vec4 v_fragmentColor;
//\n#endif\n
//
//void main()
//{
//    gl_Position = CC_MVPMatrix * a_position;
//    gl_PointSize = u_pointSize;
//    v_fragmentColor = u_color;
//}
//);
