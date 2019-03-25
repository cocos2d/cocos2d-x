// http://www.cocos2d-iphone.org

attribute vec4 a_position;
attribute vec2 a_texCoord;

#ifdef GL_ES
varying mediump vec2 v_texCoord;
#else
varying vec2 v_texCoord;
#endif

uniform mat4 u_PMatrix;

void main()
{
    gl_Position = u_PMatrix * a_position;
	v_texCoord = a_texCoord;
}

