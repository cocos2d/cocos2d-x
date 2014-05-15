
const char* cc3D_Color_frag = STRINGIFY(

#ifdef GL_ES
varying lowp vec4 DestinationColor;
#else
varying vec4 DestinationColor;
#endif
uniform vec4 u_color;

void main(void)
{
    gl_FragColor = u_color;
}
);
