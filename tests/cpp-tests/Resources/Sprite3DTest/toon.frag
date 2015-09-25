#ifdef GL_ES
varying mediump vec2 v_texture_coord;
#else
varying vec2 v_texture_coord;
#endif
uniform vec4 u_color;
uniform sampler2D u_sampler0; 
varying vec3 v_normal;
void main(void)
{
	vec3 light_direction = vec3(1,-1,-1);
	light_direction = normalize(light_direction);
	vec3 light_color = vec3(1,1,1);
	vec3 normal  = normalize(v_normal);
	float diffuse_factor = dot(normal,-light_direction);
	vec4 diffuse_color = texture2D(u_sampler0,v_texture_coord);

    if (diffuse_factor > 0.95)      diffuse_factor=1.0;
    else if (diffuse_factor > 0.75) diffuse_factor = 0.8;
    else if (diffuse_factor > 0.50) diffuse_factor = 0.6;
    else                       diffuse_factor = 0.4;

	light_color = light_color * diffuse_factor;
    gl_FragColor = vec4(light_color,1.0) * diffuse_color * u_color;
}