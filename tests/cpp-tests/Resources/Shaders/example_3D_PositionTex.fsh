#ifdef GL_ES
varying mediump vec2 TextureCoordOut;
#else
varying vec2 TextureCoordOut;
#endif
uniform vec4 u_color;

uniform sampler2D u_texture;

void main(void)
{
    gl_FragColor = texture2D(u_texture, TextureCoordOut) * u_color;
}

