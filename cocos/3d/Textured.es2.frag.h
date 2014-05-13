static const char* baseTexturedFrag = STRINGIFY(

#ifdef GL_ES
varying mediump vec2 TextureCoordOut;
#else
varying vec2 TextureCoordOut;
#endif
uniform vec4 u_color;

uniform sampler2D CC_Texture0;

void main(void)
{
    gl_FragColor = texture2D(CC_Texture0, TextureCoordOut) * u_color;
}
);