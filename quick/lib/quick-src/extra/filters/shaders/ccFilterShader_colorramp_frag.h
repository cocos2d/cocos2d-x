"\n\
#ifdef GL_ES\n\
precision mediump float;\n\
#endif\n\
\n\
// 1\n\
varying vec2 v_texCoord;\n\
uniform sampler2D u_texture;\n\
uniform sampler2D u_colorRampTexture;\n\
\n\
void main()\n\
{\n\
	vec3 normalColor = texture2D(u_texture, v_texCoord).rgb;\n\
\n\
	float rampedR = texture2D(u_colorRampTexture, vec2(normalColor.r, 0)).r;\n\
	float rampedG = texture2D(u_colorRampTexture, vec2(normalColor.g, 0)).g;\n\
	float rampedB = texture2D(u_colorRampTexture, vec2(normalColor.b, 0)).b;\n\
\n\
	gl_FragColor = vec4(rampedR, rampedG, rampedB, 1);\n\
}\n\
";
