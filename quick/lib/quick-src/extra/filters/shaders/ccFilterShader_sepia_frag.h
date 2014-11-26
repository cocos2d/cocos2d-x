"varying vec4 v_fragmentColor;\n\
varying vec2 v_texCoord;\n\
\n\
const vec3 SEPIA = vec3(1.2, 1.0, 0.8);\n\
\n\
void main() {\n\
	vec4 texColor = texture2D(CC_Texture0, v_texCoord);\n\
	float gray = dot(texColor.rgb, vec3(0.299, 0.587, 0.144));\n\
	vec3 sepiaColor = vec3(gray)*SEPIA;\n\
	gl_FragColor = vec4(mix(texColor.rgb, sepiaColor, 0.75), 1.0)*v_fragmentColor;\n\
}";
