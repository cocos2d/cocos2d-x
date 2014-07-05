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
//const char* ccPositionColorLengthTexture_frag = STRINGIFY(
//
//\n#ifdef GL_ES\n
//// #extension GL_OES_standard_derivatives : enable\n
//
//varying mediump vec4 v_color;
//varying mediump vec2 v_texcoord;
//\n#else\n
//varying vec4 v_color;
//varying vec2 v_texcoord;
//\n#endif\n
//
//void main()
//{
//// #if defined GL_OES_standard_derivatives\n
//// gl_FragColor = v_color*smoothstep(0.0, length(fwidth(v_texcoord)), 1.0 - length(v_texcoord));\n
//// #else\n
//    gl_FragColor = v_color*step(0.0, 1.0 - length(v_texcoord));
//// #endif\n
//}
//);
