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
//const char* ccLabelNormal_frag = STRINGIFY(
//\n#ifdef GL_ES\n
//precision lowp float;
//\n#endif\n
//
//varying vec4 v_fragmentColor;
//varying vec2 v_texCoord;
//
//uniform vec4 u_textColor;
//
//void main()
//{
//    gl_FragColor =  v_fragmentColor * vec4(u_textColor.rgb,// RGB from uniform\n
//        u_textColor.a * texture2D(CC_Texture0, v_texCoord).a// A from texture & uniform\n
//    );
//}
//);
