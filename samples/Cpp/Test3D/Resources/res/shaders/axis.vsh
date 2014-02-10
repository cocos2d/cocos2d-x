uniform mat4 u_worldViewProjectionMatrix;
attribute vec4 a_position;
attribute vec4 a_color;
varying vec4 v_color;
void main(void)
{
     v_color = a_color;
     gl_Position = u_worldViewProjectionMatrix * a_position;
}