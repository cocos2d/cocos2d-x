const char* ccGradientLabel_vert = STRINGIFY(
attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec4 a_color;

\n#ifdef GL_ES\n
varying lowp vec4 v_fragmentColor;
varying mediump vec2 v_texCoord;
\n#else\n
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
\n#endif\n

uniform vec2 textSize;

uniform vec4 leftTopColor;
uniform vec4 rightTopColor;
uniform vec4 leftBottomColor;
uniform vec4 rightBottomColor;
uniform vec4 u_textColor;

void main()
{
    gl_Position = CC_MVPMatrix * a_position;

    vec4 colorText12 = vec4(mix(leftTopColor, rightTopColor, (textSize.y - a_position.y) / textSize.y));
    vec4 colorText34 = vec4(mix(leftBottomColor, rightBottomColor, (textSize.y - a_position.y) / textSize.y));
    vec4 colorText = vec4(mix(colorText12, colorText34, a_position.x / textSize.x));

    v_fragmentColor = colorText;
    v_fragmentColor.a = colorText.a * a_color.a;
    v_texCoord = a_texCoord;
}
);
