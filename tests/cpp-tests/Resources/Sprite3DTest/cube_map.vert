attribute vec4 a_position;
attribute vec3 a_normal;

varying vec3 v_reflect;

void main(void)
{
    gl_Position = CC_MVPMatrix * a_position;
    
    // compute reflect
    vec4 positionWorldViewSpace = CC_MVMatrix * a_position;
    vec3 vEyeVertex     = normalize(positionWorldViewSpace.xyz);
    
    vec3 v_normalVector = CC_NormalMatrix * a_normal;
    v_reflect           = normalize(reflect(-vEyeVertex, v_normalVector));
}
