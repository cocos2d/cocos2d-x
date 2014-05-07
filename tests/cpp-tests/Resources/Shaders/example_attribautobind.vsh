attribute vec3 a_position;
attribute vec4 a_color;

uniform vec4 u_diffuseColor;

#ifdef GL_ES
varying lowp vec4 v_fragmentColor;
varying mediump vec4 v_diffColor;
#else
varying vec4 v_fragmentColor;
varying vec4 v_diffColor;
#endif

void main()
{
    gl_Position = CC_MVPMatrix * vec4(a_position, 1);
    v_fragmentColor = a_color;
    v_diffColor = u_diffuseColor;
}
