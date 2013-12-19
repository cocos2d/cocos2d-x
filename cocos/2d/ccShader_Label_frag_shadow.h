"											\n\
#ifdef GL_ES \n\
precision lowp float; \n\
#endif \n\
 \n\
varying vec4 v_fragmentColor; \n\
varying vec2 v_texCoord; \n\
uniform sampler2D CC_Texture0; \n\
uniform vec3 v_effectColor; \n\
uniform vec2 v_shadowOffset; \n\
 \n\
void main() \n\
{	\n\
  float dist = texture2D(CC_Texture0, v_texCoord).a; \n\
  //todo:support for assign offset,but the shadow is limited by renderable area \n\
  vec2 offset = vec2(-0.0015,-0.0015); \n\
  float dist2 = texture2D(CC_Texture0, v_texCoord+offset).a; \n\
  //todo:Implementation 'fwidth' for glsl 1.0 \n\
  //float width = fwidth(dist); \n\
  //assign width for constant will lead to a little bit fuzzy,it's temporary measure.\n\
  float width = 0.04; \n\
  // If v is 1 then it's inside the Glyph; if it's 0 then it's outside \n\
  float v = smoothstep(0.5-width, 0.5+width, dist); \n\
  // If s is 1 then it's inside the shadow; if it's 0 then it's outside \n\
  float s = smoothstep(0.5-width, 0.5+width, dist2); \n\
  if(v == 1.0) gl_FragColor = vec4(v_fragmentColor.rgb,1.0); \n\
  else if(v == 0.0) gl_FragColor = vec4(v_effectColor,s); \n\
  else \n\
  { \n\
    vec3 color = v_fragmentColor.rgb*v + v_effectColor*s*(1.0-v); \n\
    gl_FragColor = vec4(color,max(s,v)); \n\
  } \n\
} \n\
";
