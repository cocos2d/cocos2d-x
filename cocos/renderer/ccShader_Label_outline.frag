/*
 * LICENSE ???
 */
const char* ccLabelOutline_frag = R"(
#ifdef GL_ES
precision lowp float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform vec4 u_effectColor;
uniform vec4 u_textColor;

void main()
{
    vec4 sample = texture2D(CC_Texture0, v_texCoord);
    float fontAlpha = sample.a; // sample.a == 1 indicates text, a == 0 indicates outline
    float outlineAlpha = sample.r; // sample.r always > 0

    if (u_effectColor.a > 0.0) // draw outline
    {
        if (fontAlpha < 1.0)
        {
            gl_FragColor = v_fragmentColor * vec4(u_effectColor.rgb, u_effectColor.a * outlineAlpha);
        }
        else
        {
            discard; // While drawing outline, text should not be drawn since it will be drawn in next step.
                     // discard this pixel could improve a little and fix wrong alpha blending if text contains
                     // alpha channel.
        }
    }
    else if (fontAlpha > 0.0) // draw text
    {
        gl_FragColor = v_fragmentColor * vec4(u_textColor.rgb, u_textColor.a * fontAlpha);
    }
    else // discard the pixel in texture rectangle which is transparent
    {
        discard;
    }
}
)";
