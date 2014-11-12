"#ifdef GL_ES\n\
precision highp float;\n\
#endif\n\
\n\
\n\
varying vec2 v_texCoord;\n\
varying vec2 v_oneStepBackTextureCoordinate;\n\
varying vec2 v_twoStepsBackTextureCoordinate;\n\
varying vec2 v_threeStepsBackTextureCoordinate;\n\
varying vec2 v_fourStepsBackTextureCoordinate;\n\
varying vec2 v_oneStepForwardTextureCoordinate;\n\
varying vec2 v_twoStepsForwardTextureCoordinate;\n\
varying vec2 v_threeStepsForwardTextureCoordinate;\n\
varying vec2 v_fourStepsForwardTextureCoordinate;\n\
\n\
void main()\n\
{\n\
#ifdef GL_ES\n\
    lowp vec4 fragmentColor = texture2D(CC_Texture0, v_texCoord) * 0.18;\n\
#else\n\
    vec4 fragmentColor = texture2D(CC_Texture0, v_texCoord) * 0.18;\n\
#endif\n\
    fragmentColor += texture2D(CC_Texture0, v_oneStepBackTextureCoordinate) * 0.15;\n\
    fragmentColor += texture2D(CC_Texture0, v_twoStepsBackTextureCoordinate) *  0.12;\n\
    fragmentColor += texture2D(CC_Texture0, v_threeStepsBackTextureCoordinate) * 0.09;\n\
    fragmentColor += texture2D(CC_Texture0, v_fourStepsBackTextureCoordinate) * 0.05;\n\
    fragmentColor += texture2D(CC_Texture0, v_oneStepForwardTextureCoordinate) * 0.15;\n\
    fragmentColor += texture2D(CC_Texture0, v_twoStepsForwardTextureCoordinate) *  0.12;\n\
    fragmentColor += texture2D(CC_Texture0, v_threeStepsForwardTextureCoordinate) * 0.09;\n\
    fragmentColor += texture2D(CC_Texture0, v_fourStepsForwardTextureCoordinate) * 0.05;\n\
\n\
    gl_FragColor = fragmentColor;\n\
}";
