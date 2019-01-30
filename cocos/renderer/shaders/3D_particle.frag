
const char* CC3D_particleTexture_frag = R"(

#ifdef GL_ES
varying mediump vec2 TextureCoordOut;
varying mediump vec4 ColorOut;
#else
varying vec4 ColorOut;
varying vec2 TextureCoordOut;
#endif
uniform vec4 u_color;

uniform sampler2D u_texture;

void main(void)
{
    gl_FragColor = texture2D(u_texture, TextureCoordOut) * ColorOut * u_color;
}
)";

const char* CC3D_particleColor_frag = R"(

#ifdef GL_ES
varying mediump vec4 ColorOut;
#else
varying vec4 ColorOut;
#endif
uniform vec4 u_color;

void main(void)
{
    gl_FragColor = ColorOut * u_color;
}
)";
