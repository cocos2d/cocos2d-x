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

#ifndef _CC_MESHCOMMAND_H_
#define _CC_MESHCOMMAND_H_

#include <unordered_map>
#include "renderer/CCRenderCommand.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCRenderState.h"
#include "math/CCMath.h"

NS_CC_BEGIN

class GLProgramState;
class EventListenerCustom;
class EventCustom;
class Material;

/**
 * @addtogroup support
 * @{
 */

/**
 * @class MeshCommand
 * @brief
 * @~english
 * Command used to draw a mesh.
 * @~chinese
 * 用于渲染Mesh。
 */
class CC_DLL MeshCommand : public RenderCommand
{
public:

    /**
     @~english Constructor.
     @~chinese 构造函数。
     */
    MeshCommand();
    /**
     @~english Destructor.
     @~chinese 析构函数。
     */
    virtual ~MeshCommand();

    /**@~english Init the mesh command.
     * @~chinese 初始化MeshCommand。
     @param globalZOrder @~english GlobalZOrder of the render command.
     * @~chinese 命令的GlobalZOrder。
     @param material @~english material used for draw mesh.
     * @~chinese 用于渲染mesh的材质。
     @param vertexBuffer @~english vertex buffer to be drawn.
     * @~chinese 将要绘制的顶点buffer。
     @param indexBuffer @~english index buffer to be draw.
     * @~chinese 将要绘制的顶点索引buffer。
     @param primitive @~english Specifices what kind of primitives to render, GL_TRIANGLES, GL_TRIANGLE_STRIP, and so on. Please refer to glDrawElements
     * @~chinese 指定绘制的图元类型，GL_TRIANGLES, GL_TRIANGLE_STRIP等等，请参考glDrawElements函数。
     @param indexFormat @~english Specifies the type of the values in index buffer. It GL_UNSIGNED_BYTE or GL_UNSIGNED_SHORT.
     * @~chinese 索引缓冲区中index的类型，GL_UNSIGNED_BYTE或者GL_UNSIGNED_SHORT。
     @param indexCount @~english number of index.
     * @~chinese 索引缓冲区中的索引数量。
     @param mv @~english Model view transform used for rendering.
     * @~chinese 渲染的model view矩阵。
     @param flags @~english Indicate the render command should be rendered in 3D mode or not.
     * @~chinese 渲染命令是否使用3D模式。
     */
    void init(float globalZOrder, Material* material, GLuint vertexBuffer, GLuint indexBuffer, GLenum primitive, GLenum indexFormat, ssize_t indexCount, const Mat4 &mv, uint32_t flags);

    /**@~english Init the mesh command.
     * @~chinese 初始化MeshCommand。
     @param globalZOrder @~english GlobalZOrder of the render command.
     * @~chinese 命令的GlobalZOrder。
     @param textureID @~english the texture id to be used drawing the mesh.
     * @~chinese 用于渲染mesh的贴图。
     @param glProgramState @~english GLProgramState used to draw the mesh.
     * @~chinese 用于渲染mesh的GLProgramState。
     @param stateBlock @~english render state used to draw the mesh.
     * @~chinese 用于渲染mesh的渲染状态块。
     @param vertexBuffer @~english vertex buffer to be drawn.
     * @~chinese 将要绘制的顶点buffer。
     @param indexBuffer @~english index buffer to be draw.
     * @~chinese 将要绘制的顶点索引buffer。
     @param primitive @~english Specifices what kind of primitives to render, GL_TRIANGLES, GL_TRIANGLE_STRIP, and so on. Please refer to glDrawElements
     * @~chinese 指定绘制的图元类型，GL_TRIANGLES, GL_TRIANGLE_STRIP等等，请参考glDrawElements函数。
     @param indexFormat @~english Specifies the type of the values in index buffer. It GL_UNSIGNED_BYTE or GL_UNSIGNED_SHORT.
     * @~chinese 索引缓冲区中index的类型，GL_UNSIGNED_BYTE或者GL_UNSIGNED_SHORT。
     @param indexCount @~english number of index.
     * @~chinese 索引缓冲区中的索引数量。
     @param mv @~english Model view transform used for rendering.
     * @~chinese 渲染的model view矩阵。
     @param flags @~english Indicate the render command should be rendered in 3D mode or not.
     * @~chinese 渲染命令是否使用3D模式。
     */
    void init(float globalZOrder, GLuint textureID, GLProgramState* glProgramState, RenderState::StateBlock* stateBlock, GLuint vertexBuffer, GLuint indexBuffer, GLenum primitive, GLenum indexFormat, ssize_t indexCount, const Mat4 &mv, uint32_t flags);

    /**
     * @~english Set display color, the final color is the diplay color multiply texture color if it has.
     * @~chinese 设置显示的颜色，最终渲染出的颜色值为display color乘以贴图颜色。
     * @param color @~english Color to be shown. @~chinese 要显示的颜色
     */
    void setDisplayColor(const Vec4& color);
    /**
     * @~english Set matrix palette used to draw skeletal model.
     * @~chinese 设置用来渲染骨骼动画模型的矩阵数组。
     * @param matrixPalette @~english Matrix palette. @~chinese 矩阵数组
     */
    void setMatrixPalette(const Vec4* matrixPalette);
    /**
     * @~english Set matrix palette size.
     * @~chinese 设置用来渲染骨骼动画模型的矩阵数组大小。
     * @param size @~english Matrix palette size. @~chinese 矩阵数组大小
     */
    void setMatrixPaletteSize(int size);
    /**
     * @~english Set light mask, only the light whose light flag & light mask is not zero will illuminates this mesh.
     * @~chinese 设置灯光掩码，只有当灯光标记和灯光掩码相与不为0的时候，该灯光才会照亮这个mesh。
     * @param lightmask @~english light mask. @~chinese 灯光掩码
     */
    void setLightMask(unsigned int lightmask);

    /**
     @~english Execute the command, which will call openGL function to draw the mesh.
     @~chinese 执行命令,它将调用openGL函数绘制mesh。
     */
    void execute();
    
    /**
     @~english Used for batch, Renderer will batch all the mesh with the same material id, it calls preBatchDraw, then calls batchDraw for each mesh, calls postBatchDraw at last.
     @~chinese 用来批处理渲染，Renderer会把所有的具有相同材质id的mesh batch起来一起渲染，它先调用preBatchDraw，然后为每个mesh调用batchDraw，最后调用postBatchDraw。
     */
    void preBatchDraw();
    /**
     @~english Used for batch, Renderer will batch all the mesh with the same material id, it calls preBatchDraw, then calls batchDraw for each mesh, calls postBatchDraw at last.
     @~chinese 用来批处理渲染，Renderer会把所有的具有相同材质id的mesh batch起来一起渲染，它先调用preBatchDraw，然后为每个mesh调用batchDraw，最后调用postBatchDraw。
     */
    void batchDraw();
    /**
     @~english Used for batch, Renderer will batch all the mesh with the same material id, it calls preBatchDraw, then calls batchDraw for each mesh, calls postBatchDraw at last.
     @~chinese 用来批处理渲染，Renderer会把所有的具有相同材质id的mesh batch起来一起渲染，它先调用preBatchDraw，然后为每个mesh调用batchDraw，最后调用postBatchDraw。
     */
    void postBatchDraw();
    /**
     * @~english Generate material id, material id is used to batch the same mesh.
     * @~chinese 生成材质ID，材质ID用来batch相同的mesh。
     * @param texID @~english texture id. @~chinese 贴图ID号
     * @param glProgramState @~english GLProgramState used to draw the mesh. @~chinese 用来渲染的GLProgramState。
     * @param vertexBuffer @~english vertex buffer. @~chinese 顶点缓冲。
     * @param indexBuffer @~english index buffer. @~chinese 索引缓冲。
     * @param blend @~english blend function. @~chinese 混合函数。
     */
    void genMaterialID(GLuint texID, void* glProgramState, GLuint vertexBuffer, GLuint indexBuffer, BlendFunc blend);
    
    /**
     @~english Get material id.
     @~chinese 获取材质ID。
     * @return @~english material id. @~chinese 材质ID
     */
    uint32_t getMaterialID() const;
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    void listenRendererRecreated(EventCustom* event);
#endif

protected:
    //build & release vao
    void buildVAO();
    void releaseVAO();
    
    // apply renderstate, not used when using material
    void applyRenderState();


    Vec4 _displayColor; // in order to support tint and fade in fade out
    
    // used for skin
    const Vec4* _matrixPalette;
    int   _matrixPaletteSize;
    
    uint32_t _materialID; //material ID
    
    GLuint   _vao; //use vao if possible
    
    GLuint _vertexBuffer;
    GLuint _indexBuffer;
    GLenum _primitive;
    GLenum _indexFormat;
    ssize_t _indexCount;
    
    // States, default value all false


    // ModelView transform
    Mat4 _mv;

    // Mode A: Material
    // weak ref
    Material* _material;

    // Mode B: StateBlock
    // weak ref
    GLProgramState* _glProgramState;
    RenderState::StateBlock* _stateBlock;
    GLuint _textureID;


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    EventListenerCustom* _rendererRecreatedListener;
#endif
};

/**
 end of support group
 @}
 */

NS_CC_END

#endif //_CC_MESHCOMMAND_H_
