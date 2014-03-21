"											\n\
#ifdef GL_ES \n\
precision lowp float; \n\
#endif \n\
 \n\
varying vec4 v_fragmentColor; \n\
varying vec2 v_texCoord; \n\
uniform sampler2D CC_Texture0; \n\
uniform vec4 v_effectColor; \n\
uniform vec4 v_textColor; \n\
 \n\
void main() \n\
{	\n\
  float dist = texture2D(CC_Texture0, v_texCoord).a; \n\
  //todo:Implementation 'fwidth' for glsl 1.0 \n\
  //float width = fwidth(dist); \n\
  //assign width for constant will lead to a little bit fuzzy,it's temporary measure.\n\
  float width = 0.04; \n\
  float alpha = smoothstep(0.5-width, 0.5+width, dist); \n\
  //glow \n\
  float mu = smoothstep(0.5, 1.0, sqrt(dist)); \n\
  vec4 color = v_effectColor*(1.0-alpha) + v_textColor*alpha; \n\
  gl_FragColor = v_fragmentColor * vec4(color.rgb, max(alpha,mu)*color.a); \n\
} \n\
";
