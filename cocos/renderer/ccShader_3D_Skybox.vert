const char* cc3D_Skybox_vert = STRINGIFY(

attribute vec3 a_position;
varying vec3 v_reflect;

void main(void)
{
    v_reflect   =  normalize(CC_NormalMatrix * a_position);
    gl_Position = CC_MVPMatrix * vec4(a_position, 1.0);
}
);