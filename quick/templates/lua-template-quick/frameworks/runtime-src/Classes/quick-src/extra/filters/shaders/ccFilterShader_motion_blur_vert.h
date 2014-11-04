"attribute vec4 a_position;\n\
attribute vec2 a_texCoord;\n\
\n\
uniform vec2 u_directionalTexelStep;\n\
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
	gl_Position = CC_PMatrix * a_position;\n\
    //gl_Position = a_position;\n\
    \n\
    v_texCoord = a_texCoord;\n\
    v_oneStepBackTextureCoordinate = a_texCoord - u_directionalTexelStep;\n\
    v_twoStepsBackTextureCoordinate = a_texCoord - 2.0 * u_directionalTexelStep;\n\
    v_threeStepsBackTextureCoordinate = a_texCoord - 3.0 * u_directionalTexelStep;\n\
    v_fourStepsBackTextureCoordinate = a_texCoord - 4.0 * u_directionalTexelStep;\n\
    v_oneStepForwardTextureCoordinate = a_texCoord + u_directionalTexelStep;\n\
    v_twoStepsForwardTextureCoordinate = a_texCoord + 2.0 * u_directionalTexelStep;\n\
    v_threeStepsForwardTextureCoordinate = a_texCoord + 3.0 * u_directionalTexelStep;\n\
    v_fourStepsForwardTextureCoordinate = a_texCoord + 4.0 * u_directionalTexelStep;\n\
}";
