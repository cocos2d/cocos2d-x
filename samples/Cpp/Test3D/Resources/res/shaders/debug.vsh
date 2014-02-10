uniform mat4 u_viewProjectionMatrix;
attribute vec4 a_position;
attribute vec4 a_color;
varying vec4 v_color;
void main(void)
{
     v_color = a_color;
     gl_Position = u_viewProjectionMatrix * a_position;
}