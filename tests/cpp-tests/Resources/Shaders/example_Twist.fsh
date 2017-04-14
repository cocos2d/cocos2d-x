// Shader from here: http://www.iquilezles.org/

#ifdef GL_ES
precision highp float;
#endif

uniform vec2 resolution;
uniform sampler2D tex0;
uniform sampler2D tex1;

void main(void)
{
    float time = CC_Time[1];
    vec2 p = -1.0 + 2.0 * gl_FragCoord.xy / resolution.xy;
    vec2 uv;

    float a = atan(p.y,p.x);
    float r = sqrt(dot(p,p));

    uv.x = r - CC_Time[2];
    uv.y = sin(a*10.0 + 2.0*CC_CosTime[0];

    vec3 col =  (.5+.5*uv.y)*texture2D(tex0,uv).xyz;

    gl_FragColor = vec4(col,1.0);
}
