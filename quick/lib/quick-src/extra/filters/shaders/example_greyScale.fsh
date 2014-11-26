
const GLchar * FilterShader_greyscale_frag = STRINGIFY(

\n#ifdef GL_ES\n
precision mediump float;
\n#endif\n

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

void main(void)
{
	vec4 c = texture2D(CC_Texture0, v_texCoord);
	gl_FragColor.xyz = vec3(0.2126*c.r + 0.7152*c.g + 0.0722*c.b);
	gl_FragColor.w = c.w;
}

);