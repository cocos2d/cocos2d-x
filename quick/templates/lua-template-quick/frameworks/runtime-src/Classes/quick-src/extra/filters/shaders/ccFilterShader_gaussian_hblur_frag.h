"#ifdef GL_ES\n\
precision mediump float;\n\
#endif\n\
uniform float u_resolution;\n\
uniform float u_radius;\n\
\n\
varying vec4 v_fragmentColor;\n\
varying vec2 v_texCoord;\n\
\n\
const float f1 = 0.15;\n\
const float f2 = 0.12;\n\
const float f3 = 0.09;\n\
const float f4 = 0.05;\n\
const float fc = 0.16;\n\
\n\
void main() {\n\
	vec4 sum = vec4(0.0);\n\
	vec2 tc = v_texCoord;\n\
	float blur = u_radius/u_resolution; \n\
	\n\
	sum += texture2D(CC_Texture0, vec2(tc.x - 4.0*blur, tc.y)) * f4;\n\
	sum += texture2D(CC_Texture0, vec2(tc.x - 3.0*blur, tc.y)) * f3;\n\
	sum += texture2D(CC_Texture0, vec2(tc.x - 2.0*blur, tc.y)) * f2;\n\
	sum += texture2D(CC_Texture0, vec2(tc.x - 1.0*blur, tc.y)) * f1;\n\
	\n\
	sum += texture2D(CC_Texture0, vec2(tc.x, tc.y)) * fc;\n\
	\n\
	sum += texture2D(CC_Texture0, vec2(tc.x + 1.0*blur, tc.y)) * f1;\n\
	sum += texture2D(CC_Texture0, vec2(tc.x + 2.0*blur, tc.y)) * f2;\n\
	sum += texture2D(CC_Texture0, vec2(tc.x + 3.0*blur, tc.y)) * f3;\n\
	sum += texture2D(CC_Texture0, vec2(tc.x + 4.0*blur, tc.y)) * f4;\n\
\n\
	gl_FragColor = v_fragmentColor * sum;\n\
}";
