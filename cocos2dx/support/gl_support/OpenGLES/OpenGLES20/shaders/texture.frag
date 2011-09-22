
#define GL_ALPHA 0x1906
#define GL_RGB 0x1907
#define GL_RGBA 0x1908
#define GL_LUMINANCE 0x1909
#define GL_LUMINANCE_ALPHA 0x190A

#define GL_MODULATE 0x2100
#define GL_ADD 0x0104
#define GL_DECAL 0x2101
#define GL_BLEND 0x0BE2
#define GL_REPLACE 0x1E01
#define GL_COMBINE 0x8570
#define GL_ADD_SIGNED 0x8574
#define GL_INTERPOLATE 0x8575
#define GL_SUBTRACT 0x84E7
#define GL_DOT3_RGB 0x86AE
#define GL_DOT3_RGBA 0x86AF
#define GL_BLUR 0x86FF
#define GL_CONSTANT 0x8576
#define GL_PRIMARY_COLOR 0x8577
#define GL_PREVIOUS 0x8578
#define GL_SRC_COLOR 0x0300
#define GL_ONE_MINUS_SRC_COLOR 0x0301
#define GL_SRC_ALPHA 0x0302
#define GL_ONE_MINUS_SRC_ALPHA 0x0303

// Uniforms
uniform bool u_texture0Enabled;
uniform bool u_texture1Enabled;
uniform bool u_texture2Enabled;

// Shader variables
vec4 texture0Color;
vec4 texture1Color;
vec4 texture2Color;

// Functions
void fetchTexture0Color();
void fetchTexture1Color();
void fetchTexture2Color();
void calcTexture0Environment(inout vec4 color);
void calcTexture1Environment(inout vec4 color);
void calcTexture2Environment(inout vec4 color);


void calcTextureColorContribution(inout vec4 color)
{
	// Fetch enabled texture colors
#if TEXTURE0_ENABLED == 1 || TEXTURE0_ENABLED == -1
	#if TEXTURE0_ENABLED == -1
	if (u_texture0Enabled) {
	#endif
		fetchTexture0Color();
	#if TEXTURE0_ENABLED == -1
	}
	#endif
#endif
	
#if TEXTURE1_ENABLED == 1 || TEXTURE1_ENABLED == -1
	#if TEXTURE1_ENABLED == -1
	if (u_texture1Enabled) {
	#endif
		fetchTexture1Color();
	#if TEXTURE1_ENABLED == -1
	}
	#endif
#endif
	
#if TEXTURE2_ENABLED == 1 || TEXTURE2_ENABLED == -1
	#if TEXTURE2_ENABLED == -1
	if (u_texture2Enabled) {
	#endif
		fetchTexture2Color();
	#if TEXTURE2_ENABLED == -1
	}
	#endif
#endif
	
	// Calc texture colors based on environment
#if TEXTURE0_ENABLED == 1 || TEXTURE0_ENABLED == -1
	#if TEXTURE0_ENABLED == -1
	if (u_texture0Enabled) {
	#endif
		calcTexture0Environment(color);
	#if TEXTURE0_ENABLED == -1
	}
	#endif
#endif

#if TEXTURE1_ENABLED == 1 || TEXTURE1_ENABLED == -1
	#if TEXTURE1_ENABLED == -1
	if (u_texture1Enabled) {
	#endif
		calcTexture1Environment(color);
	#if TEXTURE1_ENABLED == -1
	}
	#endif
#endif
	
#if TEXTURE2_ENABLED == 1 || TEXTURE2_ENABLED == -1
	#if TEXTURE2_ENABLED == -1
	if (u_texture2Enabled) {
	#endif
		calcTexture2Environment(color);
	#if TEXTURE2_ENABLED == -1
	}
	#endif
#endif
}
