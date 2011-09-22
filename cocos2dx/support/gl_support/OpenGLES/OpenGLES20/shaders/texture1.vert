
#if TEXCOORD1_ENABLED != 0 && TEXTURE1_ENABLED != 0

#if !defined(TEXTURE1_MATRIX_ENABLED)
	#define TEXTURE1_MATRIX_ENABLED -1
#endif

// Attributes
attribute vec4 a_texCoord1;

// Uniforms
uniform bool u_texture1MatrixEnabled;
uniform mat4 u_texture1Matrix;

// Varyings
varying vec4 v_texCoord1;

void calcTexture1Coordinates()
{
#if TEXTURE1_MATRIX_ENABLED == 1 || TEXTURE1_MATRIX_ENABLED == -1
	#if TEXTURE1_MATRIX_ENABLED == -1
	if (u_texture1MatrixEnabled) {
	#endif
		v_texCoord1 = u_texture1Matrix * a_texCoord1; 
	#if TEXTURE1_MATRIX_ENABLED == -1
	} else {
		v_texCoord1 = a_texCoord1;
	}
	#endif	
#else
	v_texCoord1 = a_texCoord1;
#endif
}

#endif
