const char* ccLabelDistanceFieldNormal_frag = STRINGIFY(

\n#ifdef GL_ES\n
precision lowp float; 
\n#endif\n
 
varying vec4 v_fragmentColor; 
varying vec2 v_texCoord;

uniform vec4 u_textColor;
 
void main() 
{
    vec4 color = texture2D(CC_Texture0, v_texCoord);
    //the texture use dual channel 16-bit output for distance_map \n
    //float dist = color.b+color.g/256.0; \n
    // the texture use single channel 8-bit output for distance_map \n
    float dist = color.a; 
    //TODO: Implementation 'fwidth' for glsl 1.0 \n
    //float width = fwidth(dist); \n
    //assign width for constant will lead to a little bit fuzzy,it's temporary measure.\n
    float width = 0.04; 
    float alpha = smoothstep(0.5-width, 0.5+width, dist) * u_textColor.a; 
    gl_FragColor = v_fragmentColor * vec4(u_textColor.rgb,alpha);
}
);
