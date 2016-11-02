const char* cc3D_Skybox_frag = R"(
#ifdef GL_ES
varying mediump vec3        v_reflect;
#else
varying vec3        v_reflect;
#endif
uniform samplerCube u_Env;
uniform vec4 u_color;

void main(void)
{
    gl_FragColor = textureCube(u_Env, v_reflect) * u_color;
}
)";
