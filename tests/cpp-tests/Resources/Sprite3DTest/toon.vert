attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec3 a_normal;
varying vec2 TextureCoordOut;
varying vec3 v_normal;
void main(void)
{
    gl_Position = CC_MVPMatrix * a_position;
    TextureCoordOut = a_texCoord;
    TextureCoordOut.y = (1.0 - TextureCoordOut.y);
	v_normal = CC_NormalMatrix *a_normal;
}
