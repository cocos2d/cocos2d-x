
#ifdef GL_ES
precision mediump float;
#endif


uniform sampler2D u_texture;
uniform sampler2D u_texture1;
uniform float u_interpolate;

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;



void main() {
    vec4 color1 = texture2D(u_texture, v_texCoord);
    vec4 color2 = texture2D(u_texture1, v_texCoord);
    gl_FragColor = v_fragmentColor * mix( color1, color2, u_interpolate);
}

