"precision mediump float;\n\
varying vec2 v_texCoord;\n\
uniform float u_factor;\n\
 \n\
void main()\n\
{\n\
  vec2 onePixel = vec2(0.5 / 480.0, 0.5 / 320.0);\n\
 \n\
  // 3\n\
  vec2 texCoord = v_texCoord;\n\
 \n\
  // 4\n\
  vec4 color;\n\
  color.rgb = vec3(0.5);\n\
  color -= texture2D(CC_Texture0, texCoord - onePixel) * 3.0;\n\
  color += texture2D(CC_Texture0, texCoord + onePixel) * 3.0;\n\
  // 5\n\
  color.rgb = vec3((color.r + color.g + color.b) / 3.0);\n\
  gl_FragColor = vec4(color.rgb, 1);\n\
}";

