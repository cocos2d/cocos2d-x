
const char* cc3D_Particle_tex_frag = R"(

#ifdef GL_ES
varying mediump vec2 TextureCoordOut;
varying mediump vec4 ColorOut;
#else
varying vec4 ColorOut;
varying vec2 TextureCoordOut;
#endif
uniform vec4 u_color;

void main(void)
{
    gl_FragColor = texture2D(CC_Texture0, TextureCoordOut) * ColorOut * u_color;
}
)";

const char* cc3D_Particle_color_frag = R"(

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
