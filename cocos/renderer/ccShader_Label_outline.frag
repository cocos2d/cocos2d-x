/*
 * LICENSE ???
 */
const char* ccLabelOutline_frag = STRINGIFY(
\n#ifdef GL_ES\n
precision lowp float; 
\n#endif\n
 
varying vec4 v_fragmentColor; 
varying vec2 v_texCoord;

uniform vec4 u_effectColor;
uniform vec4 u_textColor;
 
void main()
{
    vec4 sample = texture2D(CC_Texture0, v_texCoord);
    float fontAlpha = sample.a; 
    float outlineAlpha = sample.r; 
    if ((fontAlpha + outlineAlpha) > 0.0){
        vec4 color = u_textColor * fontAlpha + u_effectColor * (1.0 - fontAlpha);
        gl_FragColor = v_fragmentColor * vec4( color.rgb,max(fontAlpha,outlineAlpha)*color.a);
    }
    else {
        discard;
    }
}
);
