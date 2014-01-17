// Inputs
attribute vec2 a_position;
attribute vec2 a_texCoord;

// Varying
varying vec2 v_texCoord;



uniform float radius;
uniform float angle;

vec2 vortex( vec2 uv )
{
	uv -= vec2(0.5, 0.5);
	float dist = length(uv);
	float percent = (radius - dist) / radius;
	if ( percent < 1.0 && percent >= 0.0) 
	{
		float theta = percent * percent * angle * 8.0;
		float s = sin(theta);
		float c = cos(theta);
		uv = vec2(dot(uv, vec2(c, -s)), dot(uv, vec2(s, c)));
	}
	uv += vec2(0.5, 0.5);

	return uv;
}


void main()
{
    gl_Position = vec4(a_position, 0, 1);
    v_texCoord = vortex( a_texCoord );
}