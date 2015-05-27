const char* cc3D_Skybox_vert = STRINGIFY(

uniform float u_scalef;
attribute vec3 a_position;
varying vec3 v_reflect;

void main(void)
{
    v_reflect   =  a_position;
    gl_Position = CC_MVPMatrix * vec4(u_scalef * a_position, 1.0);
}
);