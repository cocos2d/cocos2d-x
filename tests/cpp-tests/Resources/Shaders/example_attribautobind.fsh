#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec4 v_diffColor;

uniform sampler2D CC_Texture0;

void main(void)
{
	gl_FragColor = v_fragmentColor;// * v_diffColor;
}