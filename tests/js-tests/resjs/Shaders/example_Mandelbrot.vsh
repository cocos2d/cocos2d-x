// http://www.cocos2d-iphone.org

attribute vec4 a_position;

void main()
{
    gl_Position = CC_MVPMatrix * a_position;
}