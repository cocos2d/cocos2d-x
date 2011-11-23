#define EPSILON         0.0000001
#define OGL_NEVER       512 //0x0200
#define OGL_LESS        513 //0x0201
#define OGL_EQUAL       514 //0x0202
#define OGL_LEQUAL      515 //0x0203
#define OGL_GREATER     516 //0x0204
#define OGL_NOTEQUAL    517 //0x0205
#define OGL_GEQUAL      518 //0x0206
#define OGL_ALWAYS      519 //0x0207
#if !defined(ALPHA_FUNC)
#define ALPHA_FUNC -1
#endif
uniform int u_alphaFunc;
uniform float u_alphaFuncValue;
void alphaTest(float alpha) 
{
#if ALPHA_FUNC == OGL_ALWAYS
    return;
#elif ALPHA_FUNC == OGL_LESS
    if (alpha >= u_alphaFuncValue) {
        discard;
    }
#elif ALPHA_FUNC == OGL_EQUAL
    if (u_alphaFuncValue - EPSILON > alpha || alpha > u_alphaFuncValue + EPSILON) {
        discard;
    }
#elif ALPHA_FUNC == OGL_LEQUAL
    if (alpha > u_alphaFuncValue) {
        discard;
    }
#elif ALPHA_FUNC == OGL_GREATER
    if (alpha <= u_alphaFuncValue) {
        discard;
    }
#elif ALPHA_FUNC == OGL_NOTEQUAL
    if (u_alphaFuncValue - EPSILON <= alpha && alpha <= u_alphaFuncValue + EPSILON) {
        discard;
    }
#elif ALPHA_FUNC == OGL_GEQUAL
    if (alpha < u_alphaFuncValue) {
        discard;
    }
#elif ALPHA_FUNC == OGL_NEVER
    discard;
#elif ALPHA_FUNC == -1
    if (u_alphaFunc == OGL_ALWAYS) {
        return;
    } else if (u_alphaFunc == OGL_LESS) {
        if (alpha >= u_alphaFuncValue) {
            discard;
        }
    } else if (u_alphaFunc == OGL_EQUAL) {
        if (u_alphaFuncValue - EPSILON > alpha || alpha > u_alphaFuncValue + EPSILON) {
            discard;
        }
    } else if (u_alphaFunc == OGL_LEQUAL) {
        if (alpha > u_alphaFuncValue) {
            discard;
        }
    } else if (u_alphaFunc == OGL_GREATER) {
        if (alpha <= u_alphaFuncValue) {
            discard;
        }
    } else if (u_alphaFunc == OGL_NOTEQUAL) {
        if (u_alphaFuncValue - EPSILON <= alpha && alpha <= u_alphaFuncValue + EPSILON) {
            discard;
        }
    } else if (u_alphaFunc == OGL_GEQUAL) {
        if (alpha < u_alphaFuncValue) {
            discard;
        }
    } else if (u_alphaFunc == OGL_NEVER) {
        discard;
    }
#endif
}
