"\n\
#ifdef GL_ES\n\
precision mediump float;\n\
#endif\n\
 \n\
varying vec2 v_texCoord;\n\
uniform sampler2D u_texture;\n\
uniform float u_time;\n\
 \n\
// 1\n\
const float speed = 3.0;\n\
const float bendFactor = 0.2;\n\
void main()\n\
{\n\
  // 2\n\
  float height = 1.0 - v_texCoord.y;\n\
  // 3\n\
  float offset = pow(height, 1.5);\n\
 \n\
  // 4 multiply by sin since it gives us nice bending\n\
  offset *= (sin(u_time * speed) * bendFactor);\n\
 \n\
  // 5\n\
  vec3 normalColor = texture2D(u_texture, fract(vec2(v_texCoord.x + offset, v_texCoord.y))).rgb;\n\
  gl_FragColor = vec4(normalColor, 1);\n\
}";

