
varying vec3        v_reflect;
uniform samplerCube u_cubeTex;

void main(void)
{
    gl_FragColor = textureCube(u_cubeTex, v_reflect);
}