#ifdef GL_ES
varying mediump vec2 v_texture_coord;
varying mediump vec4 v_position;
#else
varying vec2 v_texture_coord;
varying vec4 v_position;
#endif
uniform sampler2D u_shadowTexture;
uniform vec3 u_target_pos;
uniform vec4 u_color;
void main(void)
{

	float Radius = 4.0;//project range
	vec3 UVector = vec3(1.0, 0.0, 0.0)/(2.0 * Radius);
	vec3 VVector = vec3(0.0, 0.0, -1.0)/(-2.0 * Radius);
	vec2 coord;  
	coord.x = dot(v_position.xyz - u_target_pos, UVector) + 0.5;
	coord.y = dot(v_position.xyz - u_target_pos, VVector) + 0.5;

	gl_FragColor = u_color*texture2D(CC_Texture0,v_texture_coord)*texture2D(u_shadowTexture,coord);
}