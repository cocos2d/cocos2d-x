#ifdef GL_ES
precision lowp float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform int u_option;
uniform sampler2D u_alphaMask;

void main()
{
    if (u_option == 1)
    {
        if (v_texCoord.y > 0.5)
        {
            discard;
        }
        else
        {
            vec4 color = texture2D(CC_Texture0, v_texCoord);
            color.a = texture2D(CC_Texture0, v_texCoord + vec2(0, 0.5)).r;
            gl_FragColor = v_fragmentColor * color;
        }
    }
    else if (u_option == 2)
    {
        vec4 color = texture2D(CC_Texture0, v_texCoord);
        color.a = texture2D(u_alphaMask, v_texCoord).r;
        gl_FragColor = v_fragmentColor * color;
    }
    else if (u_option == 3)
    {
        vec4 color = texture2D(CC_Texture0, v_texCoord);
        color.a = texture2D(u_alphaMask, v_texCoord).a;
        gl_FragColor = v_fragmentColor * color;
    }
}

