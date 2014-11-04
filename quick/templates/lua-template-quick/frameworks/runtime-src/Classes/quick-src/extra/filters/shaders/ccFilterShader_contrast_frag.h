"#ifdef GL_ES\n\
precision mediump float;\n\
#endif\n\
varying vec2 v_texCoord;\n\
\n\
uniform float u_contrast;\n\
\n\
void main()\n\
{\n\
    vec4 textureColor = texture2D(CC_Texture0, v_texCoord);\n\
    gl_FragColor = vec4(((textureColor.rgb - vec3(0.5)) * u_contrast + vec3(0.5)), textureColor.w);\n\
}";

