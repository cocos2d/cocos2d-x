"\n\
#ifdef GL_ES\n\
precision mediump float;\n\
#endif\n\
 \n\
 varying vec2 v_texCoord;\n\
 uniform sampler2D u_texture;\n\
 uniform float u_time;\n\
 \n\
void main()\n\
{\n\
  vec2 onePixel = vec2(1.0 / 480.0, 1.0 / 320.0);\n\
 \n\
  vec2 texCoord = v_texCoord;\n\
	texCoord.x += sin(u_time) * (onePixel.x * 20.0);\n\
	texCoord.y += cos(u_time) * (onePixel.y * 20.0);\n\
 \n\
  vec4 color;\n\
  color.rgb = vec3(0.5);\n\
  color -= texture2D(u_texture, texCoord - onePixel) * 2.0;\n\
  color += texture2D(u_texture, texCoord + onePixel) * 2.0;\n\
  color.rgb = vec3((color.r + color.g + color.b) / 3.0);\n\
  gl_FragColor = vec4(color.rgb, 1);\n\
}";

