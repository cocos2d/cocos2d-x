#ifdef GL_ES
precision mediump float;
#endif

varying vec3 v_reflect;
uniform samplerCube u_cubeTex;
uniform vec4 u_color;

void main(void)
{
    gl_FragColor = textureCube(u_cubeTex, v_reflect) * u_color;
}
