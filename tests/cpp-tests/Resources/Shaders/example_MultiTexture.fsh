
#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform sampler2D CC_Texture0;
uniform sampler2D u_texture1;


void main() {
    vec4 color1 = texture2D(CC_Texture0, v_texCoord) * vec4(1,1,1,CC_SinTime[3]);
    vec4 color2 = texture2D(u_texture1, v_texCoord) * vec4(1,1,1,CC_CosTime[3]);
    gl_FragColor = (color1 + color2) * v_fragmentColor;
}

