attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec3 a_normal;
varying vec2 v_texture_coord;
varying vec3 v_normal;

uniform mat4 u_MVPMatrix;
uniform mat3 u_NormalMatrix;

void main(void)
{
    gl_Position = u_MVPMatrix * a_position;
    v_texture_coord = a_texCoord;
    v_texture_coord.y = (1.0 - v_texture_coord.y);
	v_normal = u_NormalMatrix *a_normal;
}
