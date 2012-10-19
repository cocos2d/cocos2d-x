// Shader taken from: http://webglsamples.googlecode.com/hg/electricflower/electricflower.html

#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform sampler2D u_texture;

uniform vec2 blurSize;
uniform vec4 substract;

void main() {
	vec4 sum = vec4(0.0);
	sum += texture2D(u_texture, v_texCoord - 4.0 * blurSize) * 0.05;
	sum += texture2D(u_texture, v_texCoord - 3.0 * blurSize) * 0.09;
	sum += texture2D(u_texture, v_texCoord - 2.0 * blurSize) * 0.12;
	sum += texture2D(u_texture, v_texCoord - 1.0 * blurSize) * 0.15;
	sum += texture2D(u_texture, v_texCoord                 ) * 0.16;
	sum += texture2D(u_texture, v_texCoord + 1.0 * blurSize) * 0.15;
	sum += texture2D(u_texture, v_texCoord + 2.0 * blurSize) * 0.12;
	sum += texture2D(u_texture, v_texCoord + 3.0 * blurSize) * 0.09;
	sum += texture2D(u_texture, v_texCoord + 4.0 * blurSize) * 0.05;

	gl_FragColor = (sum - substract) * v_fragmentColor;
}

