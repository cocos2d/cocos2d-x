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
///*
// * LICENSE ???
// */
//const char* ccLabelOutline_frag = STRINGIFY(
//\n#ifdef GL_ES\n
//precision lowp float; 
//\n#endif\n
// 
//varying vec4 v_fragmentColor; 
//varying vec2 v_texCoord;
//
//uniform vec4 u_effectColor;
//uniform vec4 u_textColor;
// 
//void main()
//{
//    vec4 sample = texture2D(CC_Texture0, v_texCoord);
//    float fontAlpha = sample.a; 
//    float outlineAlpha = sample.r; 
//    if (outlineAlpha > 0.0){ 
//        vec4 color = u_textColor * fontAlpha + u_effectColor * (1.0 - fontAlpha);
//        gl_FragColor = v_fragmentColor * vec4( color.rgb,max(fontAlpha,outlineAlpha)*color.a);
//    }
//    else {
//        discard;
//    }
//}
//);
