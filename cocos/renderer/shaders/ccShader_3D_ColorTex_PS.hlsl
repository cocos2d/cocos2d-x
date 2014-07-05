// Per-pixel color data passed through the pixel shader.
struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float3 color : COLOR0;
};

// A pass-through function for the (interpolated) color data.
float4 main(PixelShaderInput input) : SV_TARGET
{
	return float4(input.color, 1.0f);
}
//
//const char* cc3D_ColorTex_frag = STRINGIFY(
//
//\n#ifdef GL_ES\n
//varying mediump vec2 TextureCoordOut;
//\n#else\n
//varying vec2 TextureCoordOut;
//\n#endif\n
//uniform vec4 u_color;
//
//void main(void)
//{
//    gl_FragColor = texture2D(CC_Texture0, TextureCoordOut) * u_color;
//}
//);
