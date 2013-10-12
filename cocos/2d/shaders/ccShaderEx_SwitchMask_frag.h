"                                                \n\
#ifdef GL_ES                                     \n\
precision lowp float;                            \n\
#endif                                           \n\
                                                 \n\
varying vec4        v_fragmentColor;             \n\
varying vec2        v_texCoord;                  \n\
uniform sampler2D   u_texture;                   \n\
uniform sampler2D   u_mask;                      \n\
                                                 \n\
void main()                                      \n\
{                                                \n\
    vec4 texColor   = texture2D(u_texture, v_texCoord);                                      \n\
    vec4 maskColor  = texture2D(u_mask, v_texCoord);                                         \n\
    vec4 finalColor = vec4(texColor.r, texColor.g, texColor.b, maskColor.a * texColor.a);    \n\
    gl_FragColor    = v_fragmentColor * finalColor;                                          \n\
}                                                                                            \n\
";
