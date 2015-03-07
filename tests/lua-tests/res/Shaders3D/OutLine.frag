uniform vec3 OutLineColor;
uniform vec4 u_color;

void main(void)
{
    gl_FragColor =  vec4(OutLineColor,1.0) * u_color;
}
