#ifdef OPENGL_ES
precision highp float;
#endif

uniform sampler2D u_texture;

// Varyings
varying vec2 v_texCoord;
varying vec4 v_color;


void main()
{
    gl_FragColor = v_color * texture2D(u_texture, v_texCoord);
}