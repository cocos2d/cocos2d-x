"#ifdef GL_ES\n\
precision mediump float;\n\
#endif\n\
varying vec2 v_texCoord;                    \n\
varying vec4 v_fragmentColor;\n\
\n\
uniform vec4 u_grayParam; \n\
\n\
void main(void)                             \n\
{                                           \n\
vec4 texColor = texture2D(CC_Texture0, v_texCoord);   \n\
float grey = dot(texColor.rgba, u_grayParam);       \n\
gl_FragColor = vec4(vec3(grey), texColor.a) * v_fragmentColor; \n\
}";
