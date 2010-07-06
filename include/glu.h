//
// cocos2d GLU implementation
//
// implementation of GLU functions
//
#ifndef __COCOS2D_GLU_H__
#define __COCOS2D_GLU_H__

#include <GLES/gl.h>

/**
 @file
 cocos2d OpenGL GLU implementation
 */

/** OpenGL gluLookAt implementation */
void gluLookAt(float eyeX, float eyeY, float eyeZ, float lookAtX, float lookAtY, float lookAtZ, float upX, float upY, float upZ);
/** OpenGL gluPerspective implementation */
void gluPerspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar);

#endif /* __COCOS2D_GLU_H__ */