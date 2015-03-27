const char* cc3D_Skybox_vert = STRINGIFY(

attribute vec4 a_position;
varying vec3 v_reflect;

void main(void)
{
    mat4 MVMatrixLimited = CC_MVMatrix;
    MVMatrixLimited[0][3] = 0.0;
    MVMatrixLimited[1][3] = 0.0;
    MVMatrixLimited[2][3] = 0.0;

    vec4 position = MVMatrixLimited* a_position;

    v_reflect = a_position.xyz;
    gl_Position = position.xyww;
}
);