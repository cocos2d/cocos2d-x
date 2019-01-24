
const char* CC3D_terrain_vert = R"(
attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec3 a_normal;
#ifdef GL_ES
varying mediump vec2 v_texCoord;
varying mediump vec3 v_normal;
#else
varying vec2 v_texCoord;
varying vec3 v_normal;
#endif

uniform mat4 u_MVPMatrix;
void main()
{
    gl_Position = u_MVPMatrix * a_position;
    v_texCoord = a_texCoord;
    v_normal = a_normal;
}
)";
