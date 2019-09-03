// Shader from here: http://www.iquilezles.org/

#ifdef GL_ES
precision highp float;
#endif

uniform vec2 resolution;
uniform sampler2D tex0;
uniform sampler2D tex1;
uniform vec2 u_screenSize;
uniform vec4 u_Time;
uniform vec4 u_CosTime

void main(void)
{
#ifdef METAL
	vec2 fragCoord = vec2(gl_FragCoord.x, u_screenSize.y - gl_FragCoord.y);
#else
	vec2 fragCoord = gl_FragCoord.xy;
#endif
    float time = u_Time[1];
    vec2 p = -1.0 + 2.0 * fragCoord / resolution.xy;
    vec2 uv;

    float a = atan(p.y,p.x);
    float r = sqrt(dot(p,p));

    uv.x = r - u_Time[2];
    uv.y = sin(a*10.0 + 2.0*u_CosTime[0];

    vec3 col =  (.5+.5*uv.y)*texture2D(tex0,uv).xyz;

    gl_FragColor = vec4(col,1.0);
}
