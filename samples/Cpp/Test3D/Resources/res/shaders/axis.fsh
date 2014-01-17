#ifdef OPENGL_ES
 precision highp float;
#endif
 varying vec4 v_color;
uniform vec4 u_diffuseColor;

void main(void) 
{
   gl_FragColor = v_color * u_diffuseColor;
}