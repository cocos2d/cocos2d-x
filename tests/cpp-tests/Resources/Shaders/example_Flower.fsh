// Shader from http://www.iquilezles.org/apps/shadertoy/

#ifdef GL_ES
precision highp float;
#endif

uniform vec2 center;
uniform vec2 resolution;

//float u( float x ) { return 0.5+0.5*sign(x); }
float u( float x ) { return (x>0.0)?1.0:0.0; }
//float u( float x ) { return abs(x)/x; }

void main(void)
{
	float time = CC_Time[1];
	vec2 p = 2.0 * (gl_FragCoord.xy - center.xy) / resolution.xy;
	
	float a = atan(p.x,p.y);
	float r = length(p)*.75;

	float w = cos(3.1415927*time-r*2.0);
	float h = 0.5+0.5*cos(12.0*a-w*7.0+r*8.0);
	float d = 0.25+0.75*pow(h,1.0*r)*(0.7+0.3*w);

	float col = u( d-r ) * sqrt(1.0-r/d)*r*2.5;
	col *= 1.25+0.25*cos((12.0*a-w*7.0+r*8.0)/2.0);
	col *= 1.0 - 0.35*(0.5+0.5*sin(r*30.0))*(0.5+0.5*cos(12.0*a-w*7.0+r*8.0));
	gl_FragColor = vec4(
		col,
		col-h*0.5+r*.2 + 0.35*h*(1.0-r),
		col-h*r + 0.1*h*(1.0-r),
		1.0);
}