
const char* cc3D_Particle_tex_frag = STRINGIFY(

\n#ifdef GL_ES\n
varying mediump vec2 TextureCoordOut;
varying mediump vec4 ColorOut;
\n#else\n
varying vec4 ColorOut;
varying vec2 TextureCoordOut;
\n#endif\n
uniform vec4 u_color;

void main(void)
{
    gl_FragColor = texture2D(CC_Texture0, TextureCoordOut) * ColorOut * u_color;
}
);

const char* cc3D_Particle_color_frag = STRINGIFY(
                                               
\n#ifdef GL_ES\n
varying mediump vec4 ColorOut;
\n#else\n
varying vec4 ColorOut;
\n#endif\n
uniform vec4 u_color;

void main(void)
{
    gl_FragColor = ColorOut * u_color;
}
);
