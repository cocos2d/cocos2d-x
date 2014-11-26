"varying vec2 v_texCoord;\n\
varying vec2 v_leftTexCoord;\n\
varying vec2 v_rightTexCoord; \n\
varying vec2 v_topTexCoord;\n\
varying vec2 v_bottomTexCoord;\n\
\n\
varying float v_centerMultiplier;\n\
varying float v_edgeMultiplier;\n\
\n\
void main()\n\
{\n\
    vec3 textureColor = texture2D(CC_Texture0, v_texCoord).rgb;\n\
    vec3 leftTexColor = texture2D(CC_Texture0, v_leftTexCoord).rgb;\n\
    vec3 rightTexColor = texture2D(CC_Texture0, v_rightTexCoord).rgb;\n\
    vec3 topTexColor = texture2D(CC_Texture0, v_topTexCoord).rgb;\n\
    vec3 bottomTexColor = texture2D(CC_Texture0, v_bottomTexCoord).rgb;\n\
\n\
	vec3 v1 = leftTexColor * v_edgeMultiplier + rightTexColor * v_edgeMultiplier + topTexColor * v_edgeMultiplier + bottomTexColor * v_edgeMultiplier;\n\
	vec3 v2 = textureColor * v_centerMultiplier - v1;\n\
	vec4 v3 = texture2D(CC_Texture0, v_bottomTexCoord);\n\
\n\
    gl_FragColor = vec4(v2, v3.w);\n\
}";
