
const char* cc3D_ColorTex_frag = STRINGIFY(

\n#ifdef GL_ES\n
varying mediump vec2 TextureCoordOut;
varying mediump vec4 LightIntensityOut;
\n#else\n
varying vec2 TextureCoordOut;
varying vec4 LightIntensityOut;
\n#endif\n
uniform vec4 u_color;

void main(void)
{	
	if (LightIntensityOut.w == 0.0)
		gl_FragColor = texture2D(CC_Texture0, TextureCoordOut) * u_color;
	else
		gl_FragColor = texture2D(CC_Texture0, TextureCoordOut) * u_color * LightIntensityOut;
}
);
