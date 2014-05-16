attribute vec4 a_position;
attribute vec3 a_normal;
uniform float OutlineWidth;

void main(void)
{
    vec4 pos = a_position;
    vec3 normal = a_normal;
    pos.xyz += a_normal * OutlineWidth;
    gl_Position = CC_MVPMatrix * pos;
}