#ifdef OPENGL_ES
 precision highp float;
#endif
 varying vec4 v_color;

void main(void) 
{
   gl_FragColor = v_color;
}