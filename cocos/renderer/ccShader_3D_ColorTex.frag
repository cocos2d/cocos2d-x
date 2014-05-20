
const char* cc3D_ColorTex_frag = STRINGIFY(

\n#ifdef GL_ES\n
varying mediump vec2 TextureCoordOut;
\n#else\n
varying vec2 TextureCoordOut;
\n#endif\n
uniform vec4 u_color;

void main(void)
{
    gl_FragColor = texture2D(CC_Texture0, TextureCoordOut) * u_color;
}
);
