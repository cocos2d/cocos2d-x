
#define OGL_ALPHA 0x1906
#define OGL_RGB 0x1907
#define OGL_RGBA 0x1908
#define OGL_LUMINANCE 0x1909
#define OGL_LUMINANCE_ALPHA 0x190A

#define OGL_MODULATE 0x2100
#define OGL_ADD 0x0104
#define OGL_DECAL 0x2101
#define OGL_BLEND 0x0BE2
#define OGL_REPLACE 0x1E01
#define OGL_COMBINE 0x8570
#define OGL_ADD_SIGNED 0x8574
#define OGL_INTERPOLATE 0x8575
#define OGL_SUBTRACT 0x84E7
#define OGL_DOT3_RGB 0x86AE
#define OGL_DOT3_RGBA 0x86AF
#define OGL_BLUR 0x86FF
#define OGL_CONSTANT 0x8576
#define OGL_PRIMARY_COLOR 0x8577
#define OGL_PREVIOUS 0x8578
#define OGL_SRC_COLOR 0x0300
#define OGL_ONE_MINUS_SRC_COLOR 0x0301
#define OGL_SRC_ALPHA 0x0302
#define OGL_ONE_MINUS_SRC_ALPHA 0x0303

uniform bool u_texture0Enabled;
uniform bool u_texture1Enabled;
uniform bool u_texture2Enabled;

vec4 texture0Color;
vec4 texture1Color;
vec4 texture2Color;

void fetchTexture0Color();
void fetchTexture1Color();
void fetchTexture2Color();
void calcTexture0Environment(inout vec4 color);
void calcTexture1Environment(inout vec4 color);
void calcTexture2Environment(inout vec4 color);


void calcTextureColorContribution(inout vec4 color)
{
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
