"											\n\
#ifdef GL_ES \n\
precision lowp float; \n\
#endif \n\
 \n\
varying vec4 v_fragmentColor; \n\
varying vec2 v_texCoord; \n\
uniform sampler2D CC_Texture0; \n\
uniform vec4 v_textColor; \n\
 \n\
void main() \n\
{	\n\
  vec4 color = texture2D(CC_Texture0, v_texCoord); \n\
  //the texture use dual channel 16-bit output for distance_map \n\
  //float dist = color.b+color.g/256.0; \n\
  // the texture use single channel 8-bit output for distance_map \n\
  float dist = color.a; \n\
  //todo:Implementation 'fwidth' for glsl 1.0 \n\
  //float width = fwidth(dist); \n\
  //assign width for constant will lead to a little bit fuzzy,it's temporary measure.\n\
  float width = 0.04; \n\
  float alpha = smoothstep(0.5-width, 0.5+width, dist) * v_textColor.a; \n\
  gl_FragColor = v_fragmentColor * vec4(v_textColor.rgb,alpha); \n\
} \n\
";
