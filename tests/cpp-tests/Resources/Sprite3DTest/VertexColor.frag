#ifdef GL_ES
precision lowp float;
#endif

varying vec4 v_fragmentColor;

void main()
{
    gl_FragColor = v_fragmentColor;
}