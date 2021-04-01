attribute vec4 a_position;
attribute vec4 a_color;

#ifdef GL_ES
varying lowp vec4 v_fragmentColor;
#else
varying vec4 v_fragmentColor;
#endif

uniform mat4 u_MVPMatrix;

void main()
{
    gl_Position = u_MVPMatrix * a_position;
    v_fragmentColor = a_color;
}