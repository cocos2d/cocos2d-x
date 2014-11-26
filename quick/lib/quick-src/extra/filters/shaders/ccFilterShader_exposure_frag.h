"#ifdef GL_ES\n\
precision highp float;\n\
varying mediump vec2 v_texCoord;\n\
#else\n\
varying vec2 v_texCoord;\n\
#endif\n\
\n\
uniform float u_exposure;\n\
\n\
void main()\n\
{\n\
    vec4 textureColor = texture2D(CC_Texture0, v_texCoord);\n\
    gl_FragColor = vec4(textureColor.rgb * pow(2.0, u_exposure), textureColor.w);\n\
}";

