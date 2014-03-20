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
void main()											\n\
{													\n\
  vec4 sample = texture2D(CC_Texture0, v_texCoord); \n\
  float fontAlpha = sample.a; \n\
  float outlineAlpha = sample.r; \n\
  if (outlineAlpha > 0.0){ \n\
    vec4 color = v_textColor * fontAlpha + v_effectColor * (1.0 - fontAlpha);\n\
    gl_FragColor = v_fragmentColor * vec4( color.rgb,max(fontAlpha,outlineAlpha)*color.a);                             \n\
  }                                                                                        \n\
  else { \n\
    discard; \n\
  } \n\
}													\n\
";
