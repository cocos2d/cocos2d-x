attribute vec4 a_position;
attribute vec2 a_texCoord;
varying vec2 v_texture_coord;
varying vec4 v_position;
uniform mat4 u_model_matrix;

uniform mat4 u_MVPMatrix;

void main(void)
{
    gl_Position =  u_MVPMatrix * a_position;
    v_texture_coord = a_texCoord;
    v_texture_coord.y = (1.0 - v_texture_coord.y);
	v_position = u_model_matrix * a_position;
}
