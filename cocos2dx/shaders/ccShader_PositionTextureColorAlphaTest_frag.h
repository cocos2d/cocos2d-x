"                                                            \n\
#ifdef GL_ES                                                \n\
precision lowp float;                                        \n\
#endif                                                        \n\
                                                            \n\
varying vec4 v_fragmentColor;                                \n\
varying vec2 v_texCoord;                                    \n\
uniform sampler2D u_texture;                                \n\
uniform        float u_alpha_value;                            \n\
                                                            \n\
void main()                                                    \n\
{                                                            \n\
    vec4 texColor = texture2D(u_texture, v_texCoord);        \n\
                                                            \n\
    // mimic: glAlphaFunc(GL_GREATER)                        \n\
    // pass if ( incoming_pixel >= u_alpha_value ) => fail if incoming_pixel < u_alpha_value        \n\
                                                            \n\
    if ( texColor.a <= u_alpha_value )                        \n\
        discard;                                            \n\
                                                            \n\
    gl_FragColor = texColor * v_fragmentColor;                \n\
}                                                            \n\
";
