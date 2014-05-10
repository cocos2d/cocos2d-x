const char* ccLabelDistanceFieldNormal_frag = STRINGIFY(

#ifdef GL_ES\n
precision lowp float; 
#endif\n
 
varying vec4 v_fragmentColor; 
varying vec2 v_texCoord; 
uniform sampler2D CC_Texture0; 
uniform vec4 v_textColor; 
 
void main() 
{
    vec4 color = texture2D(CC_Texture0, v_texCoord);
    //the texture use dual channel 16-bit output for distance_map 
    //float dist = color.b+color.g/256.0; 
    // the texture use single channel 8-bit output for distance_map 
    float dist = color.a; 
    //todo:Implementation 'fwidth' for glsl 1.0 
    //float width = fwidth(dist); 
    //assign width for constant will lead to a little bit fuzzy,it's temporary measure.
    float width = 0.04; 
    float alpha = smoothstep(0.5-width, 0.5+width, dist) * v_textColor.a; 
    gl_FragColor = v_fragmentColor * vec4(v_textColor.rgb,alpha); 
}
);
