"                                        \n\
#ifdef GL_ES                            \n\
precision lowp float;                    \n\
#endif                                    \n\
                                        \n\
varying vec4 v_fragmentColor;            \n\
                                        \n\
void main()                                \n\
{                                        \n\
    gl_FragColor = v_fragmentColor;        \n\
}                                        \n\
";
