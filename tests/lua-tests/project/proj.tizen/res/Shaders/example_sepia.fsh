#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

void main(void)
{
	vec4 c = texture2D(CC_Texture0, v_texCoord);
    vec4 final = c;
    final.r = (c.r * 0.393) + (c.g * 0.769) + (c.b * 0.189);
    final.g = (c.r * 0.349) + (c.g * 0.686) + (c.b * 0.168);
    final.b = (c.r * 0.272) + (c.g * 0.534) + (c.b * 0.131);

	gl_FragColor = final;
}