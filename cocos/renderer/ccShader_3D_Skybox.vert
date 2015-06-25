const char* cc3D_Skybox_vert = STRINGIFY(

uniform mat4  u_cameraRot;
attribute vec3 a_position;
varying vec3 v_reflect;

void main(void)
{
    vec4 reflect =  u_cameraRot * vec4(a_position, 1.0);
    v_reflect = reflect.xyz;
    gl_Position = vec4(a_position.xy, 1.0 , 1.0);
}
);