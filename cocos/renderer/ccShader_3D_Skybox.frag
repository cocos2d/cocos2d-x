const char* cc3D_Skybox_frag = STRINGIFY(
\n#ifdef GL_ES\n
varying mediump vec3        v_reflect;
\n#else\n
varying vec3        v_reflect;
\n#endif\n
uniform samplerCube u_Env;

void main(void)
{
    gl_FragColor = textureCube(u_Env, v_reflect);
}
);