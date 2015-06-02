/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#ifndef _CC_BATCHCOMMAND_H_
#define _CC_BATCHCOMMAND_H_

#include "renderer/CCRenderCommand.h"

/**
 * @addtogroup support
 * @{
 */

NS_CC_BEGIN

class TextureAtlas;
class GLProgram;
/**
@class BatchCommand
@brief
@~english
Command used to draw batches in one TextureAtlas.
 * @~chinese 
 * 用于渲染TextureAtlas的命令，会在同一批次内执行完。
*/
class CC_DLL BatchCommand : public RenderCommand
{
public:
    /**
    @~english Constructor. 
    @~chinese 构造函数。
    */
    BatchCommand();
    /**
    @~english Destructor. 
    @~chinese 析构函数。
    */
    ~BatchCommand();
    /**@~english Init the batch command.
     * @~chinese 初始化。
    @param globalZOrder @~english GlobalZOrder of the render command.
     * @~chinese 命令的GlobalZOrder。
    @param shader @~english Shader used for draw the texture atlas.
     * @~chinese texture atlas的shader数据。
    @param blendType @~english Blend function for texture atlas.
     * @~chinese texture atlas的blend。
    @param textureAtlas @~english Texture atlas, will contain both quads and texture for rendering.
     * @~chinese texture atlas，包含渲染的四边形和纹理。
    @param modelViewTransform @~english Model view transform used for rendering.
     * @~chinese 渲染的model view矩阵。
    @param flags @~english Indicate the render command should be rendered in 3D mode or not.
     * @~chinese 渲染命令是否使用3D模式。
    */
    void init(float globalZOrder, GLProgram* shader, BlendFunc blendType, TextureAtlas *textureAtlas, const Mat4& modelViewTransform, uint32_t flags);
    /**Deprecated function, you should call upper init function instead.*/
    CC_DEPRECATED_ATTRIBUTE void init(float depth, GLProgram* shader, BlendFunc blendType, TextureAtlas *textureAtlas, const Mat4& modelViewTransform);

    /**
    @~english Execute the command, which will call openGL function to draw the texture atlas. 
    @~chinese 执行命令,它将调用openGL函数绘制texture atlas。
    */
    void execute();

protected:
    //TODO: This member variable is not used. It should be removed.
    int32_t _materialID;
    /** Texture ID used for texture atlas rendering.*/
    GLuint _textureID;
    /** Shaders used for rendering.*/
    GLProgram* _shader;
    /** Blend function for rendering.*/
    BlendFunc _blendType;
    /** Texture atlas for rendering.*/
    TextureAtlas *_textureAtlas;

    /** ModelView transform.*/
    Mat4 _mv;
};
NS_CC_END

/**
 end of support group
 @}
 */
#endif //_CC_BATCHCOMMAND_H_
