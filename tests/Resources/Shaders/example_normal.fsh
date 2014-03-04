#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform sampler2D CC_Texture0;

void main(void)
{
	gl_FragColor = texture2D(CC_Texture0, v_texCoord);
}