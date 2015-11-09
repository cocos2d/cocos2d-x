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

#include "renderer/CCRenderCommand.h"
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
class CC_DLL QuadCommand : public RenderCommand
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
    void init(float globalOrder, GLuint textureID, GLProgramState* shader, const BlendFunc& blendType, V3F_C4B_T2F_Quad* quads, ssize_t quadCount,
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
    /**
    @~english Apply the texture, shaders, programs, blend functions to GPU pipeline. 
    @~chinese 将纹理、shader, program, 和blend应用到GPU渲染管线。
    */
    void useMaterial() const;
    /**
    @~english Get the material id of command. 
    @~chinese 得到材质ID。
    @return
    @~english the material id.
    @~chinese 材质ID。
    */
    inline uint32_t getMaterialID() const { return _materialID; }
    /**
    @~english Get the openGL texture handle. 
    @~chinese 得到纹理的openGL句柄。
    @return
    @~english openGL texture handle.
    @~chinese 纹理的openGL句柄。
    */
    inline GLuint getTextureID() const { return _textureID; }
    /**
    @~english Get the pointer of the rendered quads. 
    @~chinese 得到四边形的数据。
    @return 
    @~english the pointer of the rendered quads.
    @~chinese 四边形数据的指针。
    */
    inline V3F_C4B_T2F_Quad* getQuads() const { return _quads; }
    /**
    @~english Get the number of quads for rendering. 
    @~chinese 获得四边形的个数。
    @return
    @~english the number of quads.
    @~chinese 四边形的个数。
    */
    inline ssize_t getQuadCount() const { return _quadsCount; }
    /**
    @~english Get the glprogramstate. 
    @~chinese 得到GLProgramState。
    @return
    @~english glprogramstate.
    @~chinese GLProgramState。
    */
    inline GLProgramState* getGLProgramState() const { return _glProgramState; }
    /**
    @~english Get the blend function. 
    @~chinese 得到混合功能。
    @return
    @~english blend function.
    @~chinese 混合功能。
    */
    inline BlendFunc getBlendType() const { return _blendType; }
    /**
    @~english Get the model view matrix. 
    @~chinese 得到模型视图矩阵。
    @return
    @~english model view matrix.
    @~chinese model view矩阵。
    */
    inline const Mat4& getModelView() const { return _mv; }
    
protected:
    /**Generate the material ID by textureID, glProgramState, and blend function.*/
    void generateMaterialID();
    
    /**Generated material id.*/
    uint32_t _materialID;
    /**OpenGL handle for texture.*/
    GLuint _textureID;
    /**GLprogramstate for the command. encapsulate shaders and uniforms.*/
    GLProgramState* _glProgramState;
    /**Blend function when rendering the triangles.*/
    BlendFunc _blendType;
    /**The pointer to the rendered quads.*/
    V3F_C4B_T2F_Quad* _quads;
    /**The number of quads for rendering.*/
    ssize_t _quadsCount;
    /**Model view matrix when rendering the triangles.*/
    Mat4 _mv;
};

NS_CC_END

/**
 end of support group
 @}
 */
#endif //_CC_QUADCOMMAND_H_
