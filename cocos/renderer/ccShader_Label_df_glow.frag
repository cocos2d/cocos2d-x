const char* ccLabelDistanceFieldGlow_frag = STRINGIFY(

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
    float dist = texture2D(CC_Texture0, v_texCoord).a;
    //todo:Implementation 'fwidth' for glsl 1.0 
    //float width = fwidth(dist); 
    //assign width for constant will lead to a little bit fuzzy,it's temporary measure.
    float width = 0.04; 
    float alpha = smoothstep(0.5-width, 0.5+width, dist); 
    //glow 
    float mu = smoothstep(0.5, 1.0, sqrt(dist)); 
    vec4 color = v_effectColor*(1.0-alpha) + v_textColor*alpha; 
    gl_FragColor = v_fragmentColor * vec4(color.rgb, max(alpha,mu)*color.a); 
}
);
