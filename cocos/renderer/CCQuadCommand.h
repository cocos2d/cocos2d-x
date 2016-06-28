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

#ifndef _CC_QUADCOMMAND_H_
#define _CC_QUADCOMMAND_H_

#include <vector>

#include "renderer/CCTrianglesCommand.h"
#include "renderer/CCGLProgramState.h"

/**
 * @addtogroup renderer
 * @{
 */

NS_CC_BEGIN

/**
@class QuadCommand
@brief
@~english
 Command used to render one or more Quads, similar to TrianglesCommand.
 Every QuadCommand will have generate material ID by give textureID, glProgramState, Blend function
 if the material id is the same, these QuadCommands could be batched to save draw call.
 * @~chinese 
 * 该类用于渲染一个或者多个四边形，与TrianglesCommand类似。
 * 每个QuadCommand将使用textureID glProgramState、Blend来生成材质ID
 * 如果材料ID是相同的,这些QuadCommands可以在同一批次渲染。
 */
class CC_DLL QuadCommand : public TrianglesCommand
{
public:
    /**
    @~english Constructor. 
    @~chinese 构造函数。
    */
    QuadCommand();
    /**
    @~english Destructor. 
    @~chinese 析构函数。
    */
    ~QuadCommand();
    
    /** @~english Initializes the command.
     * @~chinese 初始化渲染命令。
     @param globalOrder @~english GlobalZOrder of the command.
     * @~chinese 命令的GlobalZOrder。
     @param textureID @~english The openGL handle of the used texture.
     * @~chinese 纹理的openGL句柄。
     @param @~english glProgramState The glProgram with its uniform.
     * @~chinese 包含了uniform的glProgram
     @param shader @~english The specified glProgram and its uniform.
     * @~chinese 指定的glProgram和uniform数值。
     @param blendType @~english Blend function for the command.
     * @~chinese Blend状态。
     @param quads @~english Rendered quads for the command.
     * @~chinese 待渲染的四边形数据。
     @param quadCount @~english The number of quads when rendering.
     * @~chinese 待渲染的四边形数量。
     @param mv @~english ModelView matrix for the command.
     * @~chinese model view矩阵。
     @param flags @~english to indicate that the command is using 3D rendering or not.
     * @~chinese 是否使用3d渲染。
     */
    void init(float globalOrder, GLuint textureID, GLProgramState* glProgramState, const BlendFunc& blendType, V3F_C4B_T2F_Quad* quads, ssize_t quadCount,
              const Mat4& mv, uint32_t flags);

    /**
    @~english Deprecated function, the params is similar as the upper init function, with flags equals 0.
    @~chinese Deprecated函数，函数与init功能类似，flags被设置为0
    @param globalOrder @~english GlobalZOrder of the command.
     * @~chinese 命令的GlobalZOrder。
     @param textureID @~english The openGL handle of the used texture.
     * @~chinese 纹理的openGL句柄。
     @param shader @~english The specified glProgram and its uniform.
     * @~chinese 指定的glProgram和uniform数值。
     @param blendType @~english Blend function for the command.
     * @~chinese Blend状态。
     @param quads @~english Rendered quads for the command.
     * @~chinese 待渲染的四边形数据。
     @param quadCount @~english The number of quads when rendering.
     * @~chinese 待渲染的四边形数量。
     @param mv @~english ModelView matrix for the command.
     * @~chinese model view矩阵。
    */
    CC_DEPRECATED_ATTRIBUTE void init(float globalOrder, GLuint textureID, GLProgramState* shader, const BlendFunc& blendType, V3F_C4B_T2F_Quad* quads, ssize_t quadCount,
              const Mat4& mv);
    
protected:
    void reIndex(int indices);

    int _indexSize;
    std::vector<GLushort*> _ownedIndices;

    // shared across all instances
    static int __indexCapacity;
    static GLushort* __indices;
};

NS_CC_END

/**
 end of support group
 @}
 */
#endif //_CC_QUADCOMMAND_H_
