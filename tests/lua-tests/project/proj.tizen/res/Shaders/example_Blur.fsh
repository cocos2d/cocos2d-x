#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform vec2 resolution;
uniform float blurRadius;
uniform float sampleNum;

vec3 blur(vec2);

void main(void)
{
	vec3 col = blur(v_texCoord);
	gl_FragColor = vec4(col, 1.0) * v_fragmentColor;
}

vec3 blur(vec2 p)
{
    if (blurRadius > 0.0 && sampleNum > 1.0)
    {
        vec3 col = vec3(0);
        vec2 unit = 1.0 / resolution.xy;
        
        float r = blurRadius;
        float sampleStep = r / sampleNum;
        
        float count = 0.0;
        
        for(float x = -r; x < r; x += sampleStep)
        {
            for(float y = -r; y < r; y += sampleStep)
            {
                float weight = (r - abs(x)) * (r - abs(y));
                col += texture2D(CC_Texture0, p + vec2(x * unit.x, y * unit.y)).rgb * weight;
                count += weight;
            }
        }
        
        return col / count;
    }
    
    return texture2D(CC_Texture0, p).rgb;
}
