#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform sampler2D u_texture;

void main(void)
{
	gl_FragColor = texture2D(u_texture, v_texCoord);
}