// http://www.cocos2d-iphone.org

attribute vec4 a_position;

uniform		mat4 u_MVPMatrix;

void main()
{
    gl_Position = u_MVPMatrix * a_position;
}