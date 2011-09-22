
// Uniforms
uniform bool u_texture0Enabled;
uniform bool u_texture1Enabled;
uniform bool u_texture2Enabled;
uniform bool u_texCoord0Enabled;
uniform bool u_texCoord1Enabled;
uniform bool u_texCoord2Enabled;

// Functions
void calcTexture0Coordinates();
void calcTexture1Coordinates();
void calcTexture2Coordinates();

void calcTextureCoordinates()
{
#if TEXCOORD0_ENABLED == 1 && TEXTURE0_ENABLED == 1
	calcTexture0Coordinates();
#elif TEXCOORD0_ENABLED == 1 && TEXTURE0_ENABLED == -1
	if (u_texture0Enabled) {
		calcTexture0Coordinates();
	}
#elif TEXCOORD0_ENABLED == -1 && TEXTURE0_ENABLED == 1
	if (u_texCoord0Enabled) {
		calcTexture0Coordinates();
	}
#elif TEXCOORD0_ENABLED == -1 && TEXTURE0_ENABLED == -1
	if (u_texture0Enabled && u_texCoord0Enabled) {
		calcTexture0Coordinates();
	}
#endif
	
#if TEXCOORD1_ENABLED == 1 && TEXTURE1_ENABLED == 1
	calcTexture1Coordinates();
#elif TEXCOORD1_ENABLED == 1 && TEXTURE1_ENABLED == -1
	if (u_texture1Enabled) {
		calcTexture1Coordinates();
	}
#elif TEXCOORD1_ENABLED == -1 && TEXTURE1_ENABLED == 1
	if (u_texCoord1Enabled) {
		calcTexture1Coordinates();
	}
#elif TEXCOORD1_ENABLED == -1 && TEXTURE1_ENABLED == -1
	if (u_texture1Enabled && u_texCoord1Enabled) {
		calcTexture1Coordinates();
	}
#endif
 
#if TEXCOORD2_ENABLED == 1 && TEXTURE2_ENABLED == 1
	calcTexture2Coordinates();
#elif TEXCOORD2_ENABLED == 1 && TEXTURE2_ENABLED == -1
	if (u_texture2Enabled) {
		calcTexture2Coordinates();
	}
#elif TEXCOORD2_ENABLED == -1 && TEXTURE2_ENABLED == 1
	if (u_texCoord2Enabled) {
		calcTexture2Coordinates();
	}
#elif TEXCOORD2_ENABLED == -1 && TEXTURE2_ENABLED == -1
	if (u_texture2Enabled && u_texCoord2Enabled) {
		calcTexture2Coordinates();
	}
#endif
}

