attribute vec4 a_position;
attribute vec3 a_normal;

varying vec3 v_reflect;
//uniforms
uniform mat4 u_MVPMatrix;
uniform mat4 u_MVMatrix;
uniform mat3 u_NormalMatrix;

void main(void)
{
    gl_Position = u_MVPMatrix * a_position;
    
    // compute reflect
    vec4 positionWorldViewSpace = u_MVMatrix * a_position;
    vec3 vEyeVertex     = normalize(positionWorldViewSpace.xyz);
    
    vec3 v_normalVector = u_NormalMatrix * a_normal;
    v_reflect           = normalize(reflect(-vEyeVertex, v_normalVector));
}
