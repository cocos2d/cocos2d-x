
#define EPSILON 0.0000001  // TODO: depends on precision

#define GL_NEVER 0x0200
#define GL_LESS 0x0201
#define GL_EQUAL 0x0202
#define GL_LEQUAL 0x0203
#define GL_GREATER 0x0204
#define GL_NOTEQUAL 0x0205
#define GL_GEQUAL 0x0206
#define GL_ALWAYS 0x0207

#if !defined(ALPHA_FUNC)
	#define ALPHA_FUNC -1
#endif

// Uniforms
uniform int u_alphaFunc;
uniform float u_alphaFuncValue;

void alphaTest(float alpha) 
{
#if ALPHA_FUNC == GL_ALWAYS
	return;
#elif ALPHA_FUNC == GL_LESS
	if (alpha >= u_alphaFuncValue) {
		discard;
	}
#elif ALPHA_FUNC == GL_EQUAL
	if (u_alphaFuncValue - EPSILON > alpha || alpha > u_alphaFuncValue + EPSILON) {
		discard;
	}
#elif ALPHA_FUNC == GL_LEQUAL
	if (alpha > u_alphaFuncValue) {
		discard;
	}
#elif ALPHA_FUNC == GL_GREATER
	if (alpha <= u_alphaFuncValue) {
		discard;
	}
#elif ALPHA_FUNC == GL_NOTEQUAL
	if (u_alphaFuncValue - EPSILON <= alpha && alpha <= u_alphaFuncValue + EPSILON) {
		discard;
	}
#elif ALPHA_FUNC == GL_GEQUAL
	if (alpha < u_alphaFuncValue) {
		discard;
	}
#elif ALPHA_FUNC == GL_NEVER
	discard;
#elif ALPHA_FUNC == -1
	if (u_alphaFunc == GL_ALWAYS) {
		return;
	} else if (u_alphaFunc == GL_LESS) {
		if (alpha >= u_alphaFuncValue) {
			discard;
		}
	} else if (u_alphaFunc == GL_EQUAL) {
		if (u_alphaFuncValue - EPSILON > alpha || alpha > u_alphaFuncValue + EPSILON) {
			discard;
		}
	} else if (u_alphaFunc == GL_LEQUAL) {
		if (alpha > u_alphaFuncValue) {
			discard;
		}
	} else if (u_alphaFunc == GL_GREATER) {
		if (alpha <= u_alphaFuncValue) {
			discard;
		}
	} else if (u_alphaFunc == GL_NOTEQUAL) {
		if (u_alphaFuncValue - EPSILON <= alpha && alpha <= u_alphaFuncValue + EPSILON) {
			discard;
		}
	} else if (u_alphaFunc == GL_GEQUAL) {
		if (alpha < u_alphaFuncValue) {
			discard;
		}
	} else if (u_alphaFunc == GL_NEVER) {
		discard;
	}
#endif
}
