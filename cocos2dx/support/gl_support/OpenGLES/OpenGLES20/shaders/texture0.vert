
#if TEXCOORD0_ENABLED != 0 && TEXTURE0_ENABLED != 0

#if !defined(TEXTURE0_MATRIX_ENABLED)
	#define TEXTURE0_MATRIX_ENABLED -1
#endif

// Attributes
attribute vec4 a_texCoord0;

// Uniforms
uniform bool u_texture0MatrixEnabled;
uniform mat4 u_texture0Matrix;

// Varyings
varying vec4 v_texCoord0;

void calcTexture0Coordinates()
{
#if TEXTURE0_MATRIX_ENABLED == 1 || TEXTURE0_MATRIX_ENABLED == -1
	#if TEXTURE0_MATRIX_ENABLED == -1
	if (u_texture0MatrixEnabled) {
	#endif
		v_texCoord0 = u_texture0Matrix * a_texCoord0; 
	#if TEXTURE0_MATRIX_ENABLED == -1
	} else {
		v_texCoord0 = a_texCoord0;
	}
	#endif	
#else
	v_texCoord0 = a_texCoord0;
#endif
}

#endif
