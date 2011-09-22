
#if TEXCOORD2_ENABLED != 0 && TEXTURE2_ENABLED != 0

#if !defined(TEXTURE2_MATRIX_ENABLED)
	#define TEXTURE2_MATRIX_ENABLED -1
#endif

// Attributes
attribute vec4 a_texCoord2;

// Uniforms
uniform bool u_texture2MatrixEnabled;
uniform mat4 u_texture2Matrix;

// Varyings
varying vec4 v_texCoord2;

void calcTexture2Coordinates()
{
#if TEXTURE2_MATRIX_ENABLED == 1 || TEXTURE2_MATRIX_ENABLED == -1
	#if TEXTURE2_MATRIX_ENABLED == -1
	if (u_texture2MatrixEnabled) {
	#endif
		v_texCoord2 = u_texture2Matrix * a_texCoord2; 
	#if TEXTURE2_MATRIX_ENABLED == -1
	} else {
		v_texCoord2 = a_texCoord2;
	}
	#endif	
#else
	v_texCoord2 = a_texCoord2;
#endif
}

#endif
