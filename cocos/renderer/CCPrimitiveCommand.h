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

#ifndef _CC_PRIMITIVE_COMMAND_H__
#define _CC_PRIMITIVE_COMMAND_H__

#include "renderer/CCPrimitive.h"
#include "renderer/CCRenderCommand.h"

/**
 * @addtogroup renderer
 * @{
 */

NS_CC_BEGIN
class GLProgramState;
/**@~english
 Command used to render primitive, similar to QuadCommand.
 Every QCommand will have generate material ID by give textureID, glProgramState, Blend function. 
 However, primitive command could not be batched.
 * @~chinese 
 * 类似于QuadCommand，这个命令可以渲染各种图元。
 * 每个Command将使用textureID, glProgramState、混合函数来生成材质ID。
 * 该命令不能batch渲染。
 */
class CC_DLL PrimitiveCommand : public RenderCommand
{
public:
    /**@~english
     Constructor.
     * @~chinese 
     * 构造函数。
     */
    PrimitiveCommand();
    /**@~english
     Destructor.
     * @~chinese 
     * 析构函数。
     */
    ~PrimitiveCommand();
    
    
    /** @~english Initializes the command.
     * @~chinese 初始化渲染命令。
     @param globalOrder @~english GlobalZOrder of the command.
     * @~chinese 命令的GlobalZOrder。
     @param textureID @~english The openGL handle of the used texture.
     * @~chinese 命令使用的纹理。
     @param glProgramState @~english The specified glProgram and its uniform.
     * @~chinese 命令使用的GLProgramState，包含GLProgram和对应的uniform。
     @param blendType @~english Blend function for the command.
     * @~chinese 命令的混合函数。
     @param primitive @~english Rendered primitive for the command.
     * @~chinese 命令的绘制图元。
     @param mv @~english ModelView matrix for the command.
     * @~chinese 命令的ModelView矩阵。
     @param flags @~english to indicate that the command is using 3D rendering or not.
     * @~chinese 表明该命令是否使用3 d渲染。
     */
    void init(float globalOrder, GLuint textureID, GLProgramState* glProgramState, BlendFunc blendType, Primitive* primitive, const Mat4& mv, uint32_t flags);
    CC_DEPRECATED_ATTRIBUTE void init(float globalOrder, GLuint textureID, GLProgramState* glProgramState, BlendFunc blendType, Primitive* primitive,const Mat4& mv);
    
    /**@~english Get the generated material ID. @~chinese 生成的材质ID。*/
    inline uint32_t getMaterialID() const { return _materialID; }
    /**@~english Get the texture ID used for drawing. @~chinese 绘制使用的纹理。*/
    inline GLuint getTextureID() const { return _textureID; }
    /**@~english Get the glprogramstate used for drawing. @~chinese 渲染使用的GLProgramState。*/
    inline GLProgramState* getGLProgramState() const { return _glProgramState; }
    /**@~english Get the blend funcion for drawing. @~chinese 得到的绘制时使用的混合函数。*/
    inline BlendFunc getBlendType() const { return _blendType; }
    /**@~english Get the modelview matrix when draw the primtive. @~chinese 绘制primtive时候的ModelView矩阵。*/
    inline const Mat4& getModelView() const { return _mv; }
    /**@~english Execute and draw the commmand, called by renderer. @~chinese 执行和绘制该命令,被渲染器调用。*/
    void execute() const;
protected:
    
    uint32_t _materialID;
    GLuint _textureID;
    GLProgramState* _glProgramState;
    BlendFunc _blendType;
    Primitive* _primitive;
    Mat4 _mv;
};

NS_CC_END

/**
 end of support group
 @}
 */
#endif //_CC_PRIMITIVE_COMMAND_H__
