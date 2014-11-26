"#ifdef GL_ES\n\
precision mediump float;\n\
#endif\n\
uniform vec2 u_resolution;\n\
\n\
varying vec4 v_fragmentColor;\n\
varying vec2 v_texCoord;\n\
\n\
const float RADIUS = 0.75;\n\
const float SOFTNESS = 0.45;\n\
const vec3 SEPIA = vec3(1.2, 1.0, 0.8);\n\
\n\
void main() {\n\
	vec4 texColor = texture2D(CC_Texture0, v_texCoord);\n\
	vec2 pos = (gl_FragCoord.xy/u_resolution.xy) - 0.5;\n\
	pos.x *= u_resolution.x/u_resolution.y;\n\
	float len = length(pos);\n\
	////gl_FragColor = vec4(texColor.rgb*(1.0-len), 1.0);\n\
	float vignette = smoothstep(RADIUS, RADIUS-SOFTNESS, len);\n\
	//texColor.rgb *= mix(texColor.rgb, texColor.rgb*vignette, 0.5);\n\
	texColor.rgb = mix(texColor.rgb, texColor.rgb*vignette, 0.5);\n\
	//gl_FragColor=texColor;\n\
	//gl_FragColor=texColor*v_fragmentColor;\n\
	//gl_FragColor = vec4(texColor.rgb*(1.0-len), 1);\n\
	float gray = dot(texColor.rgb, vec3(0.299, 0.587, 0.144));\n\
	vec3 sepiaColor = vec3(gray)*SEPIA;\n\
	gl_FragColor = vec4(mix(texColor.rgb, sepiaColor, 0.75), 1.0);\n\
}";
