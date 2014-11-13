attribute vec4 a_position;
attribute vec2 a_texCoord;
uniform float offset;
varying vec2 TextureCoordOut;
void main(void)
{
    gl_Position = CC_MVPMatrix * a_position;
    TextureCoordOut = a_texCoord;
    TextureCoordOut.y = (1.0 - TextureCoordOut.y);
}
