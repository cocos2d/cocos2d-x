
const char * cameraClear_vert = R"(
uniform float depth;
attribute vec4 a_position;
attribute vec4 a_color;
attribute vec2 a_texCoord;

#ifdef GL_ES
varying mediump vec2 v_texCoord;
varying mediump vec4 v_color;
#else
varying vec2 v_texCoord;
varying vec4 v_color;
#endif

void main()
{
    gl_Position = a_position;
    gl_Position.z = depth;
    gl_Position.w = 1.0;
    v_texCoord = a_texCoord;
    v_color = a_color;
}

)";