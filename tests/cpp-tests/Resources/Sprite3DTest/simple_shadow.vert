attribute vec4 a_position;
attribute vec2 a_texCoord;
varying vec2 TextureCoordOut;
varying vec4 v_position;
uniform mat4 u_model_matrix;
void main(void)
{
    gl_Position =  CC_PMatrix  * CC_MVMatrix * a_position;
    TextureCoordOut = a_texCoord;
    TextureCoordOut.y = (1.0 - TextureCoordOut.y);
	v_position = u_model_matrix * a_position;
}
