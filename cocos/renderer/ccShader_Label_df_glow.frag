const char* ccLabelDistanceFieldGlow_frag = STRINGIFY(

\n#ifdef GL_ES\n
precision lowp float; 
\n#endif\n
 
varying vec4 v_fragmentColor; 
varying vec2 v_texCoord;

uniform vec4 u_effectColor;
uniform vec4 u_textColor;
 
void main() 
{
    float dist = texture2D(CC_Texture0, v_texCoord).a;
    //TODO: Implementation 'fwidth' for glsl 1.0 \n
    //float width = fwidth(dist); \n
    //assign width for constant will lead to a little bit fuzzy,it's temporary measure.\n
    float width = 0.04; 
    float alpha = smoothstep(0.5-width, 0.5+width, dist); 
    //glow \n
    float mu = smoothstep(0.5, 1.0, sqrt(dist)); 
    vec4 color = u_effectColor*(1.0-alpha) + u_textColor*alpha;
    gl_FragColor = v_fragmentColor * vec4(color.rgb, max(alpha,mu)*color.a); 
}
);
