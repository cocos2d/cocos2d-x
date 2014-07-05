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
//const char* ccPositionTexture_frag = STRINGIFY(
//
//\n#ifdef GL_ES\n
//precision lowp float;
//\n#endif\n
//
//varying vec2 v_texCoord;
//
//void main()
//{
//    gl_FragColor =  texture2D(CC_Texture0, v_texCoord);
//}
//);
