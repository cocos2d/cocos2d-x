"											\n\
#ifdef GL_ES \n\
precision lowp float; \n\
#endif \n\
 \n\
varying vec4 v_fragmentColor; \n\
varying vec2 v_texCoord; \n\
uniform sampler2D CC_Texture0; \n\
uniform vec4 v_effectColor; \n\
 \n\
void main()											\n\
{													\n\
  vec4 sample = texture2D(CC_Texture0, v_texCoord); \n\
  float fontAlpha = sample.a; \n\
  float outlineAlpha = sample.r; \n\
  if (outlineAlpha > 0.0){ \n\
    vec3 color = v_fragmentColor.rgb * fontAlpha + v_effectColor.rgb * (1.0 - fontAlpha);\n\
    gl_FragColor = vec4( color,max(fontAlpha,outlineAlpha)*v_fragmentColor.a);                             \n\
  }                                                                                        \n\
  else { \n\
    discard; \n\
  } \n\
}													\n\
";
