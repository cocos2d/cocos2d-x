
const char* cc3D_Terrain_vert = STRINGIFY(
attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec3 a_normal;
\n#ifdef GL_ES\n
varying mediump vec2 v_texCoord;
varying mediump vec3 v_normal;
\n#else\n
varying vec2 v_texCoord;
varying vec3 v_normal;
\n#endif\n
void main()
{
    gl_Position = CC_MVPMatrix * a_position;
    v_texCoord = a_texCoord;
    v_normal = a_normal;
}
);
