
const char* cc3D_Color_frag = STRINGIFY(

\n#ifdef GL_ES\n
varying lowp vec4 DestinationColor;
\n#else\n
varying vec4 DestinationColor;
\n#endif\n
uniform vec4 u_color;

void main(void)
{
    gl_FragColor = u_color;
}
);
