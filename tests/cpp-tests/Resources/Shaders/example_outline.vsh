/* 
  Created by guanghui on 4/8/14.

*/


attribute vec4 a_position;
attribute vec4 a_color;
attribute vec2 a_texCoord;

varying vec2 v_texCoord;

varying vec4 v_fragmentColor;

void main()
{
    gl_Position = CC_MVPMatrix * a_position;
    v_fragmentColor = a_color;
    v_texCoord = a_texCoord;
}