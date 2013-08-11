#ifndef __CCGL_H__
#define __CCGL_H__

#define GL_GLEXT_PROTOTYPES 1

#include <qopengl.h>

#if defined(QT_OPENGL_ES_2)
  #include <qopengles2ext.h>

  #define GL_DEPTH24_STENCIL8		GL_DEPTH24_STENCIL8_OES

  // android defines GL_BGRA_EXT but not GL_BRGA
  #ifndef GL_BGRA
  #define GL_BGRA  0x80E1
  #endif
#else
  #include <qopenglext.h>
#endif

#define glClearDepth glClearDepthf

#endif // __CCGL_H__
