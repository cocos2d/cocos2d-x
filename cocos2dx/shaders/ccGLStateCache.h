/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __CCGLSTATE_H__
#define __CCGLSTATE_H__

#include "CCGL.h"
#include "platform/CCPlatformMacros.h"

NS_CC_BEGIN

/**
 * @addtogroup shaders
 * @{
 */

class GLProgram;

/** vertex attrib flags */
enum {
    kVertexAttribFlag_None        = 0,

    kVertexAttribFlag_Position    = 1 << 0,
    kVertexAttribFlag_Color       = 1 << 1,
    kVertexAttribFlag_TexCoords   = 1 << 2,

    kVertexAttribFlag_PosColorTex = ( kVertexAttribFlag_Position | kVertexAttribFlag_Color | kVertexAttribFlag_TexCoords ),
};

/** GL server side states */
typedef enum {
//    CC_GL_SCISSOR_TEST = 1 << 0,
//    CC_GL_STENCIL_TEST = 1 << 1,
//    CC_GL_DEPTH_TEST = 1 << 2,
//    CC_GL_BLEND = 1 << 3,
//    CC_GL_DITHER = 1 << 4,

//    CC_GL_ALL = ( CC_GL_SCISSOR_TEST | CC_GL_STENCIL_TEST | CC_GL_DEPTH_TEST | CC_GL_BLEND | CC_GL_DITHER ),
//    CC_GL_ALL = ( CC_GL_BLEND ),
      CC_GL_ALL = 0,

} ccGLServerState;

/** @file ccGLStateCache.h
*/

/** Invalidates the GL state cache.
 If CC_ENABLE_GL_STATE_CACHE it will reset the GL state cache.
 @since v2.0.0
 */
void CC_DLL ccGLInvalidateStateCache(void);

/** Uses the GL program in case program is different than the current one.
 If CC_ENABLE_GL_STATE_CACHE is disabled, it will the glUseProgram() directly.
 @since v2.0.0
 */
void CC_DLL ccGLUseProgram(GLuint program);

/** Deletes the GL program. If it is the one that is being used, it invalidates it.
 If CC_ENABLE_GL_STATE_CACHE is disabled, it will the glDeleteProgram() directly.
 @since v2.0.0
 */
void CC_DLL ccGLDeleteProgram(GLuint program);

/** Uses a blending function in case it not already used.
 If CC_ENABLE_GL_STATE_CACHE is disabled, it will the glBlendFunc() directly.
 @since v2.0.0
 */
void CC_DLL ccGLBlendFunc(GLenum sfactor, GLenum dfactor);

/** Resets the blending mode back to the cached state in case you used glBlendFuncSeparate() or glBlendEquation().
 If CC_ENABLE_GL_STATE_CACHE is disabled, it will just set the default blending mode using GL_FUNC_ADD.
 @since v2.0.0
 */
void CC_DLL ccGLBlendResetToCache(void);

/** sets the projection matrix as dirty
 @since v2.0.0
 */
void CC_DLL ccSetProjectionMatrixDirty(void);

/** Will enable the vertex attribs that are passed as flags.
 Possible flags:

    * kVertexAttribFlag_Position
    * kVertexAttribFlag_Color
    * kVertexAttribFlag_TexCoords

 These flags can be ORed. The flags that are not present, will be disabled.

 @since v2.0.0
 */
void CC_DLL ccGLEnableVertexAttribs(unsigned int flags);

/** If the texture is not already bound to texture unit 0, it binds it.
 If CC_ENABLE_GL_STATE_CACHE is disabled, it will call glBindTexture() directly.
 @since v2.0.0
 */
void CC_DLL ccGLBindTexture2D(GLuint textureId);


/** If the texture is not already bound to a given unit, it binds it.
 If CC_ENABLE_GL_STATE_CACHE is disabled, it will call glBindTexture() directly.
 @since v2.1.0
 */
void CC_DLL ccGLBindTexture2DN(GLuint textureUnit, GLuint textureId);

/** It will delete a given texture. If the texture was bound, it will invalidate the cached.
 If CC_ENABLE_GL_STATE_CACHE is disabled, it will call glDeleteTextures() directly.
 @since v2.0.0
 */
void CC_DLL ccGLDeleteTexture(GLuint textureId);

/** It will delete a given texture. If the texture was bound, it will invalidate the cached for the given texture unit.
 If CC_ENABLE_GL_STATE_CACHE is disabled, it will call glDeleteTextures() directly.
 @since v2.1.0
 */
void CC_DLL ccGLDeleteTextureN(GLuint textureUnit, GLuint textureId);

/** If the vertex array is not already bound, it binds it.
 If CC_ENABLE_GL_STATE_CACHE is disabled, it will call glBindVertexArray() directly.
 @since v2.0.0
 */
void CC_DLL ccGLBindVAO(GLuint vaoId);

/** It will enable / disable the server side GL states.
 If CC_ENABLE_GL_STATE_CACHE is disabled, it will call glEnable() directly.
 @since v2.0.0
 */
void CC_DLL ccGLEnable( ccGLServerState flags );

// end of shaders group
/// @}

NS_CC_END
    

#endif /* __CCGLSTATE_H__ */
