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
//const char* ccPosition_uColor_frag = STRINGIFY(
//
//\n#ifdef GL_ES\n
//precision lowp float;
//\n#endif\n
//
//varying vec4 v_fragmentColor;
//
//void main()
//{
//    gl_FragColor = v_fragmentColor;
//}
//);
