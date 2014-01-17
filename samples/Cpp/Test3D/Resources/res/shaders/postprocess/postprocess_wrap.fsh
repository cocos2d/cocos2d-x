#ifdef OPENGL_ES
precision mediump float;
#endif

uniform sampler2D u_texture;
uniform sampler2D u_pertubeSampler;
	
uniform float g_fWarpScale;


varying vec2 v_texcoord;
varying vec2 v_pertubeTC;

void main()
{
   vec2 pertube = texture2D(u_pertubeSampler, v_pertubeTC).rg;
	
	pertube = (pertube - vec2(0.5, 0.5)) * 2.0;
	vec2 tc = vec2(-1.0, 1.0) * vec2(g_fWarpScale, g_fWarpScale) * pertube.xy + v_texcoord;

	gl_FragColor = texture2D(u_texture,tc);
   
}