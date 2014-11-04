"#ifdef GL_ES\n\
precision lowp float;\n\
varying highp vec2 v_texCoord;\n\
#else\n\
varying vec2 v_texCoord;\n\
#endif\n\
\n\
uniform float u_saturation;\n\
\n\
const vec3 luminanceWeighting = vec3(0.2125, 0.7154, 0.0721);\n\
\n\
void main()\n\
{\n\
   vec4 textureColor = texture2D(CC_Texture0, v_texCoord);\n\
   float luminance = dot(textureColor.rgb, luminanceWeighting);\n\
   vec3 greyScaleColor = vec3(luminance);\n\
   \n\
   gl_FragColor = vec4(mix(greyScaleColor, textureColor.rgb, u_saturation), textureColor.w);\n\
}";

