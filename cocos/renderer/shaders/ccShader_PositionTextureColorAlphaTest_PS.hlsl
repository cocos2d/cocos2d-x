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
//const char* ccPositionTextureColorAlphaTest_frag = STRINGIFY(
//
//\n#ifdef GL_ES\n
//precision lowp float;
//\n#endif\n
//
//varying vec4 v_fragmentColor;
//varying vec2 v_texCoord;
//uniform float CC_alpha_value;
//
//void main()
//{
//    vec4 texColor = texture2D(CC_Texture0, v_texCoord);
//
//\n// mimic: glAlphaFunc(GL_GREATER)
//\n// pass if ( incoming_pixel >= CC_alpha_value ) => fail if incoming_pixel < CC_alpha_value\n
//
//    if ( texColor.a <= CC_alpha_value )
//        discard;
//
//    gl_FragColor = texColor * v_fragmentColor;
//}
//);
