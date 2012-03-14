// Shader from http://www.iquilezles.org/apps/shadertoy/

#ifdef GL_ES
precision highp float;
#endif

uniform vec2 center;
uniform vec2 resolution;
uniform float time;

void main(void)
{
    vec2 p = 2.0 * (gl_FragCoord.xy - center.xy) / resolution.xy;
	p.x *= resolution.x/resolution.y;

	float zoo = .62+.38*sin(.1*time);
	float coa = cos( 0.1*(1.0-zoo)*time );
	float sia = sin( 0.1*(1.0-zoo)*time );
	zoo = pow( zoo,8.0);
	vec2 xy = vec2( p.x*coa-p.y*sia, p.x*sia+p.y*coa);
	vec2 cc = vec2(-.745,.186) + xy*zoo;

	vec2 z  = vec2(0.0);
	vec2 z2 = z*z;
	float m2;
	float co = 0.0;

	for( int i=0; i<256; i++ )
	{
		z = cc + vec2( z.x*z.x - z.y*z.y, 2.0*z.x*z.y );
		m2 = dot(z,z);
		if( m2>1024.0 ) break;
		co += 1.0;
	}
	co = co + 1.0 - log2(.5*log2(m2));

	co = sqrt(co/256.0);
	gl_FragColor = vec4( .5+.5*cos(6.2831*co+0.0),
						.5+.5*cos(6.2831*co+0.4),
						.5+.5*cos(6.2831*co+0.7),
						1.0 );
}