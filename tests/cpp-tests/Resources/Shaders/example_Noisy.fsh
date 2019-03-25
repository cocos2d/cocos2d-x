// Shader taken from: http://webglsamples.googlecode.com/hg/electricflower/electricflower.html

#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform vec2 resolution;
uniform sampler2D u_texture;
uniform vec4 u_Time;

const float intensity = 0.05;
vec3 noise(vec2 uv)
{
	vec2 p = abs(sin(uv * 13.0 + uv.x * u_Time[1] * sin(uv.y)));
	
	return vec3(sin (0.2 * u_Time[1] + sin(p * 0.5) * u_Time[1] / cos(50.0)) * 10.0,0.3+0.5 * abs(sin(u_Time[1] * tan(5.0))));

}

void main(void)
{
	gl_FragColor.xyz = intensity * noise(gl_FragCoord.xy / sin(resolution.xy * u_Time[1] * 0.01)) + (1. - intensity) *
			texture2D(u_texture,v_texCoord.xy).xyz;
	gl_FragColor.w = 1.;
}