#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform vec2 resolution;

vec4 blur(vec2);

void main(void)
{
    vec4 col = blur(v_texCoord); //* v_fragmentColor.rgb;
    gl_FragColor = vec4(col) * v_fragmentColor;
}

vec4 blur(vec2 p)
{
        vec4 col = vec4(0);
        vec2 unit = 1.0 / resolution.xy;
        
        float count = 0.0;
        
        for(float x = -4.0; x <= 4.0; x += 2.0)
        {
            for(float y = -4.0; y <= 4.0; y += 2.0)
            {
                float weight = (4.0 - abs(x)) * (4.0 - abs(y));
                col += texture2D(CC_Texture0, p + vec2(x * unit.x, y * unit.y)) * weight;
                count += weight;
            }
        }
        
        return col / count;
}
