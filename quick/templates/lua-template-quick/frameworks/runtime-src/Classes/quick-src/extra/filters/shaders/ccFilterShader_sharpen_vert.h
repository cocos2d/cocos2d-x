"attribute vec4 a_position;\n\
attribute vec2 a_texCoord;\n\
attribute vec4 a_color;	\n\
\n\
uniform float u_widthFactor; \n\
uniform float u_heightFactor; \n\
uniform float u_sharpness;\n\
\n\
varying vec2 v_texCoord;\n\
varying vec2 v_leftTexCoord;\n\
varying vec2 v_rightTexCoord; \n\
varying vec2 v_topTexCoord;\n\
varying vec2 v_bottomTexCoord;\n\
\n\
varying float v_centerMultiplier;\n\
varying float v_edgeMultiplier;\n\
\n\
void main()\n\
{\n\
    gl_Position = CC_PMatrix * a_position;		\n\
    //gl_Position = a_position;\n\
    \n\
    vec2 widthStep = vec2(u_widthFactor, 0.0);\n\
    vec2 heightStep = vec2(0.0, u_heightFactor);\n\
    \n\
    v_texCoord = a_texCoord;\n\
    v_leftTexCoord = a_texCoord - widthStep;\n\
    v_rightTexCoord = a_texCoord + widthStep;\n\
    v_topTexCoord = a_texCoord + heightStep;\n\
    v_bottomTexCoord = a_texCoord - heightStep;\n\
    \n\
    v_centerMultiplier = 1.0 + 4.0 * u_sharpness;\n\
    v_edgeMultiplier = u_sharpness;\n\
}";
