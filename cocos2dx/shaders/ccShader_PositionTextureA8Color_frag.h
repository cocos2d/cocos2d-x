"                                                    \n\
#ifdef GL_ES                                        \n\
precision lowp float;                                \n\
#endif                                                \n\
                                                    \n\
varying vec4 v_fragmentColor;                        \n\
varying vec2 v_texCoord;                            \n\
uniform sampler2D u_texture;                        \n\
                                                    \n\
void main()                                            \n\
{                                                    \n\
    gl_FragColor = vec4( v_fragmentColor.rgb,                                        // RGB from uniform                \n\
                        v_fragmentColor.a * texture2D(u_texture, v_texCoord).a        // A from texture & uniform        \n\
                        );                            \n\
}                                                    \n\
";
