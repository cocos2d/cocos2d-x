#ifdef GL_FRAGMENT_PRECISION_HIGH
	precision highp float;
#else
	precision mediump float;
#endif


uniform sampler2D u_texture;

varying vec2 v_texCoord;

void main() 
{
	gl_FragColor = texture2D(u_texture, v_texCoord);
}
