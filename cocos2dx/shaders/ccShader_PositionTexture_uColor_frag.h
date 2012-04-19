"                                        \n\
#ifdef GL_ES                            \n\
precision lowp float;                    \n\
#endif                                    \n\
                                        \n\
uniform        vec4 u_color;                \n\
                                        \n\
varying vec2 v_texCoord;                \n\
                                        \n\
uniform sampler2D u_texture;            \n\
                                        \n\
void main()                                \n\
{                                        \n\
    gl_FragColor =  texture2D(u_texture, v_texCoord) * u_color;    \n\
}                                        \n\
";
