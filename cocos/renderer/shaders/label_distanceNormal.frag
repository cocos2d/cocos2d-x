const char* label_distanceNormal_frag = R"(

#ifdef GL_ES
precision lowp float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform vec4 u_textColor;
uniform sampler2D u_texture;

void main()
{
    vec4 color = texture2D(u_texture, v_texCoord);
    //the texture use dual channel 16-bit output for distance_map
    //float dist = color.b+color.g/256.0;
    // the texture use single channel 8-bit output for distance_map
    float dist = color.a;
    //TODO: Implementation 'fwidth' for glsl 1.0
    //float width = fwidth(dist);
    //assign width for constant will lead to a little bit fuzzy,it's temporary measure.
    float width = 0.04;
    float alpha = smoothstep(0.5-width, 0.5+width, dist) * u_textColor.a;
    gl_FragColor = v_fragmentColor * vec4(u_textColor.rgb,alpha);
}
)";
