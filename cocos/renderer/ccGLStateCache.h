/****************************************************************************
 Copyright (c) 2011      Ricardo Quesada
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2011      Zynga Inc.
 Copyright (C) 2013-2015 Chukong Technologies Inc.

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

#include <cstdint>

#include "platform/CCGL.h"
#include "platform/CCPlatformMacros.h"

NS_CC_BEGIN

/**
 * @addtogroup support
 * @{
 */

class GLProgram;

namespace GL {

/** @~english Vertex attrib flags.  @~chinese 枚举顶点属性的标示位。*/
enum {
    VERTEX_ATTRIB_FLAG_NONE       = 0,

    VERTEX_ATTRIB_FLAG_POSITION   = 1 << 0,
    VERTEX_ATTRIB_FLAG_COLOR      = 1 << 1,
    VERTEX_ATTRIB_FLAG_TEX_COORD = 1 << 2,
    VERTEX_ATTRIB_FLAG_NORMAL = 1 << 3,
    VERTEX_ATTRIB_FLAG_BLEND_WEIGHT = 1 << 4,
    VERTEX_ATTRIB_FLAG_BLEND_INDEX = 1 << 5,
    
    VERTEX_ATTRIB_FLAG_POS_COLOR_TEX = (VERTEX_ATTRIB_FLAG_POSITION | VERTEX_ATTRIB_FLAG_COLOR | VERTEX_ATTRIB_FLAG_TEX_COORD),
};

/** @~english
 * Invalidates the GL state cache.
 *
 * If CC_ENABLE_GL_STATE_CACHE it will reset the GL state cache.
 * @~chinese 
 * 设置GL状态缓存为失效状态。
 * 
 * 如果启用了CC_ENABLE_GL_STATE_CACHE，GL状态缓存将重置。
 * @since v2.0.0
 */
void CC_DLL invalidateStateCache(void);

/** @~english
 * Uses the GL program in case program is different than the current one.

 * If CC_ENABLE_GL_STATE_CACHE is disabled, it will the glUseProgram() directly.
 * @~chinese 
 * 使用openGL program来绘制。
 * 
 * 如果CC_ENABLE_GL_STATE_CACHE是禁用的,它将直接调用openGL函数glUseProgram。
 * 如果是启用的，就会与当前缓存进行比较，只有与缓存不一致才更新。
 * @since v2.0.0
 */
void CC_DLL useProgram(GLuint program);

/** @~english
 * Deletes the GL program. If it is the one that is being used, it invalidates it.
 *
 * If CC_ENABLE_GL_STATE_CACHE is disabled, it will the glDeleteProgram() directly.
 * @~chinese 
 * 删除openGL program。如果是它正在被使用,会先将其从openGL渲染管线上解绑。
 * 
 * 如果CC_ENABLE_GL_STATE_CACHE是禁用的,它将直接调用glDeleteProgram。
 * @since v2.0.0
 */
void CC_DLL deleteProgram(GLuint program);

/** @~english
 * Uses a blending function in case it not already used.
 *
 * If CC_ENABLE_GL_STATE_CACHE is disabled, it will the glBlendFunc() directly.
 * @~chinese 
 * 与cache比对，更新混合函数。
 * 
 * 如果CC_ENABLE_GL_STATE_CACHE是禁用的,它将直接调用glBlendFunc。
 * @since v2.0.0
 */
void CC_DLL blendFunc(GLenum sfactor, GLenum dfactor);

/** @~english
 * Resets the blending mode back to the cached state in case you used glBlendFuncSeparate() or glBlendEquation().
 *
 * If CC_ENABLE_GL_STATE_CACHE is disabled, it will just set the default blending mode using GL_FUNC_ADD.
 * @~chinese 
 * 重置blend状态，以防止外部调用了glBlendFuncSeparate() or glBlendEquation()这两个函数。
 * 
 * 如果CC_ENABLE_GL_STATE_CACHE是禁用的,它只会设置默认使用GL_FUNC_ADD混合模式。
 * @since v2.0.0
 */
void CC_DLL blendResetToCache(void);

/** @~english
 * Sets the projection matrix as dirty.
 * @~chinese 
 * 让投影矩阵的cache失效。
 * @since v2.0.0
 */
void CC_DLL setProjectionMatrixDirty(void);

/** @~english
 * Will enable the vertex attribs that are passed as flags.
 * Possible flags:
 * 
 *    * VERTEX_ATTRIB_FLAG_POSITION
 *    * VERTEX_ATTRIB_FLAG_COLOR
 *    * VERTEX_ATTRIB_FLAG_TEX_COORDS
 * 
 * These flags can be ORed. The flags that are not present, will be disabled.
 * 
 * @~chinese 
 * 启用一些顶点属性。
 * 可能的标志位有:
 *    * VERTEX_ATTRIB_FLAG_POSITION
 *    * VERTEX_ATTRIB_FLAG_COLOR
 *    * VERTEX_ATTRIB_FLAG_TEX_COORDS
 * 
 * 这些标志位可以通过或操作来组合。如果某一个标示位为0，对应的顶点属性将被禁用。
 * 
 * @since v2.0.0
 */
void CC_DLL enableVertexAttribs(uint32_t flags);

/** @~english
 * If the texture is not already bound to texture unit 0, it binds it.
 *
 * If CC_ENABLE_GL_STATE_CACHE is disabled, it will call glBindTexture() directly.
 * @~chinese 
 * 将一个纹理绑定到第0个纹理单元，如果纹理与在cache中的纹理一致，将跳过openGL调用。
 * 
 * 如果CC_ENABLE_GL_STATE_CACHE是禁用的,它将直接调用glBindTexture。
 * @since v2.0.0
 */
void CC_DLL bindTexture2D(GLuint textureId);

/** @~english
 * If the texture is not already bound to a given unit, it binds it.
 *
 * If CC_ENABLE_GL_STATE_CACHE is disabled, it will call glBindTexture() directly.
 * @~chinese 
 * 将一个纹理绑定到第textureUnit个纹理单元，如果纹理与在cache中的纹理一致，将跳过openGL调用。
 * 
 * 如果CC_ENABLE_GL_STATE_CACHE是禁用的,它将直接调用glBindTexture。
 * @since v2.1.0
 */
void CC_DLL bindTexture2DN(GLuint textureUnit, GLuint textureId);

/** @~english If the texture is not already bound to a given unit, it binds it.
 * If CC_ENABLE_GL_STATE_CACHE is disabled, it will call glBindTexture() directly.
 * @~chinese 将一个纹理绑定到第textureUnit个纹理单元，如果纹理与在cache中的纹理一致，将跳过openGL调用。
 * 如果CC_ENABLE_GL_STATE_CACHE是禁用的,它将直接调用glBindTexture()。
 * @since v3.6
 */
void CC_DLL bindTextureN(GLuint textureUnit, GLuint textureId, GLuint textureType = GL_TEXTURE_2D);

/** @~english
 * It will delete a given texture. If the texture was bound, it will invalidate the cached.
 *
 * If CC_ENABLE_GL_STATE_CACHE is disabled, it will call glDeleteTextures() directly.
 * @~chinese 
 * 它将删除给定的纹理。如果纹理已经绑定,那么对应缓存将失效，纹理从openGL渲染管线中解绑。
 * 
 * 如果CC_ENABLE_GL_STATE_CACHE是禁用的,它将直接调用glDeleteTextures。
 * @since v2.0.0
 */
void CC_DLL deleteTexture(GLuint textureId);

/** @~english
 * It will delete a given texture. If the texture was bound, it will invalidate the cached for the given texture unit.
 *
 * If CC_ENABLE_GL_STATE_CACHE is disabled, it will call glDeleteTextures() directly.
 * @~chinese 
 * 它将删除给定的纹理。如果纹理已经被绑定,它将是的绑定的缓存失效，并且从openGL渲染管线中解绑。
 * 
 * 如果CC_ENABLE_GL_STATE_CACHE是禁用的,它将直接调用glDeleteTextures。
 * @since v2.1.0
 */
CC_DEPRECATED_ATTRIBUTE void CC_DLL deleteTextureN(GLuint textureUnit, GLuint textureId);

/** @~english
 * Select active texture unit.
 *
 * If CC_ENABLE_GL_STATE_CACHE is disabled, it will call glActiveTexture() directly.
 * @~chinese 
 * 将对应的纹理单位设置为当前活动纹理单位。
 * 
 * 如果CC_ENABLE_GL_STATE_CACHE是禁用的,它将直接调用glActiveTexture。
 * @since v3.0
 */
void CC_DLL activeTexture(GLenum texture);

/** @~english
 * If the vertex array is not already bound, it binds it.
 *
 * If CC_ENABLE_GL_STATE_CACHE is disabled, it will call glBindVertexArray() directly.
 * @~chinese 
 * 绑定对应的VAO，如果cache的VAO和指定的VAO一致，将跳过openGL调用。
 * 
 * 如果CC_ENABLE_GL_STATE_CACHE是禁用的,它将直接调用glBindVertexArray。
 * @since v2.0.0
 */
void CC_DLL bindVAO(GLuint vaoId);

} // Namespace GL

/**end of support group
 @}
 */

NS_CC_END
    

#endif /* __CCGLSTATE_H__ */
