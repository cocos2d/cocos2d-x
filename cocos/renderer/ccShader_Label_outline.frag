const char* ccLabelOutline_frag = STRINGIFY(
#ifdef GL_ES 
precision lowp float; 
#endif 
 
varying vec4 v_fragmentColor; 
varying vec2 v_texCoord; 
uniform sampler2D CC_Texture0; 
uniform vec4 v_effectColor; 
uniform vec4 v_textColor; 
 
void main()
{
    vec4 sample = texture2D(CC_Texture0, v_texCoord);
    float fontAlpha = sample.a; 
    float outlineAlpha = sample.r; 
    if (outlineAlpha > 0.0){ 
        vec4 color = v_textColor * fontAlpha + v_effectColor * (1.0 - fontAlpha);
        gl_FragColor = v_fragmentColor * vec4( color.rgb,max(fontAlpha,outlineAlpha)*color.a);
    }
    else {
        discard;
    }
}
);
