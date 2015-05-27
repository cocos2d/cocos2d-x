// http://www.cocos2d-iphone.org

attribute vec4 a_position;
attribute vec2 a_texCoord;

#ifdef GL_ES
varying mediump vec2 v_texCoord;
#else
varying vec2 v_texCoord;
#endif

void main()
{
    //gl_Position = CC_MVPMatrix * a_position;
    gl_Position = (CC_PMatrix * CC_MVMatrix) * a_position;
	v_texCoord = a_texCoord;
}

