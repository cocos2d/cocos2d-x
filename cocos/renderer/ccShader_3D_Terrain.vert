
const char* cc3D_Terrain_vert = R"(
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
void main()
{
    gl_Position = CC_MVPMatrix * a_position;
    v_texCoord = a_texCoord;
    v_normal = a_normal;
}
)";
