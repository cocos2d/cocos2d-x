#ifndef __CCGL_H__
#define __CCGL_H__

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#define GL_DEPTH24_STENCIL8		GL_DEPTH24_STENCIL8_OES

#define glClearDepth glClearDepthf

// android defines GL_BGRA_EXT but not GL_BRGA
#ifndef GL_BGRA
#define GL_BGRA  0x80E1
#endif

#endif // __CCGL_H__
