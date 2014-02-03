"											\n\
#ifdef GL_ES \n\
precision lowp float; \n\
#endif \n\
 \n\
varying vec4 v_fragmentColor; \n\
varying vec2 v_texCoord; \n\
uniform sampler2D CC_Texture0; \n\
uniform vec3 v_effectColor; \n\
 \n\
void main() \n\
{	\n\
  float dist = texture2D(CC_Texture0, v_texCoord).a; \n\
  //todo:Implementation 'fwidth' for glsl 1.0 \n\
  //float width = fwidth(dist); \n\
  //assign width for constant will lead to a little bit fuzzy,it's temporary measure.\n\
  float width = 0.04; \n\
  float alpha = smoothstep(0.5-width, 0.5+width, dist); \n\
  //outline \n\
  float mu = smoothstep(0.545-width, 0.545+width, dist); \n\
  vec3 rgb = v_effectColor*(1.0-mu) + v_fragmentColor.rgb*mu; \n\
  gl_FragColor = vec4(rgb, max(alpha,mu)); \n\
} \n\
";
