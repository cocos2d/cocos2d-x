"uniform sampler2D u_texture1;\n\
uniform sampler2D u_mask;\n\
\n\
varying vec4 v_fragmentColor;\n\
varying vec2 v_texCoord;\n\
\n\
void main() {\n\
	vec4 texColor0 = texture2D(CC_Texture0, v_texCoord);\n\
	vec4 texColor1 = texture2D(u_texture1, v_texCoord);\n\
	float mask = texture2D(u_mask, v_texCoord).a;\n\
	gl_FragColor = mix(texColor0, texColor1, mask);\n\
}";
