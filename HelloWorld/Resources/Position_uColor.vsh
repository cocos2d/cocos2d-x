// http://www.cocos2d-iphone.org

attribute vec4 a_position;

uniform	mat4 u_MVPMatrix;
uniform	vec4 u_color;
uniform float u_pointSize;

#ifdef GL_ES
varying lowp vec4 v_fragmentColor;
#else
varying vec4 v_fragmentColor;
#endif

void main()
{
    gl_Position = u_MVPMatrix * a_position;
	gl_PointSize = u_pointSize;
	v_fragmentColor = u_color;
}
