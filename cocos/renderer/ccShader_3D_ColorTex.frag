
const char* cc3D_ColorTex_frag = R"(

#ifdef GL_ES
varying mediump vec2 TextureCoordOut;
#else
varying vec2 TextureCoordOut;
#endif
uniform vec4 u_color;

void main(void)
{
    gl_FragColor = texture2D(CC_Texture0, TextureCoordOut) * u_color;
}
)";
