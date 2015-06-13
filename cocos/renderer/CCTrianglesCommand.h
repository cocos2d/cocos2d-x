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

#ifndef __CC_TRIANGLES_COMMAND__
#define __CC_TRIANGLES_COMMAND__

#include "renderer/CCRenderCommand.h"
#include "renderer/CCGLProgramState.h"

/**
 * @addtogroup support
 * @{
 */

NS_CC_BEGIN

/** @class TrianglesCommand
@brief
@~english
 Command used to render one or more Triangles, which is similar to QuadCommand.
 Every TrianglesCommand will have generate material ID by give textureID, glProgramState, Blend function
 if the material id is the same, these TrianglesCommands could be batched to save draw call.
 * @~chinese 
 * 该命令用于绘制一个或多个三角形,与QuadCommand相似。
 * 每个TrianglesCommand将使用textureID,glProgramState,混合功能等生成材质ID,
 * 如果材质ID是相同的,这些TrianglesCommands可以进行批处理绘制。
*/
class CC_DLL TrianglesCommand : public RenderCommand
{
public:
    /**@~english The structure of Triangles.  @~chinese 三角形的结构。*/
    struct Triangles
    {
        /**@~english Vertex data pointer. @~chinese 顶点数据指针。*/
        V3F_C4B_T2F* verts;
        /**@~english Index data pointer. @~chinese 索引数据指针。*/
        unsigned short* indices;
        /**@~english The number of vertices. @~chinese 顶点的数量。*/
        ssize_t vertCount;
        /**@~english The number of indices. @~chinese 索引的数量。*/
        ssize_t indexCount;
    };
    /**@~english Construtor. @~chinese 构造函数。*/
    TrianglesCommand();
    /**@~english Destructor. @~chinese 析构函数。*/
    ~TrianglesCommand();
    
    /** @~english Initializes the command.
     * @~chinese 初始化命令。
     @param globalOrder @~english GlobalZOrder of the command.
     * @~chinese 渲染命令的GlobalZOrder。
     @param textureID @~english The openGL handle of the used texture.
     * @~chinese 纹理的openGL句柄。
     @param glProgramState @~english The specified glProgram and its uniform.
     * @~chinese 指定的glProgram和其uniform参数。
     @param blendType @~english Blend function for the command.
     * @~chinese 渲染命令的混合函数。
     @param triangles @~english Rendered triangles for the command.
     * @~chinese 渲染的三角形。
     @param mv @~english ModelView matrix for the command.
     * @~chinese ModelView矩阵。
     @param flags @~english to indicate that the command is using 3D rendering or not.
     * @~chinese 该命令是否使用3d渲染。
     */
    void init(float globalOrder, GLuint textureID, GLProgramState* glProgramState, BlendFunc blendType, const Triangles& triangles,const Mat4& mv, uint32_t flags);
    /**
    @~english Deprecated function, the params is similar as the upper init function, with flags equals 0. 
    @~chinese Deprecated函数,参数为与init函数类似,但是其flags等于0。
    @param globalOrder @~english GlobalZOrder of the command.
     * @~chinese 渲染命令的GlobalZOrder。
     @param textureID @~english The openGL handle of the used texture.
     * @~chinese 纹理的openGL句柄。
     @param glProgramState @~english The specified glProgram and its uniform.
     * @~chinese 指定的glProgram和其uniform参数。
     @param blendType @~english Blend function for the command.
     * @~chinese 渲染命令的混合函数。
     @param triangles @~english Rendered triangles for the command.
     * @~chinese 渲染的三角形。
     @param mv @~english ModelView matrix for the command.
     * @~chinese ModelView矩阵。
    */
    CC_DEPRECATED_ATTRIBUTE void init(float globalOrder, GLuint textureID, GLProgramState* glProgramState, BlendFunc blendType, const Triangles& triangles,const Mat4& mv);
    /**
    @~english Apply the texture, shaders, programs, blend functions to GPU pipeline. 
    @~chinese 应用纹理、着色器程序,混合到openGL渲染管线中。
    */
    void useMaterial() const;
    /**
    @~english Get the material id of command. 
    @~chinese 得到的材质ID。
    @return @~english Material ID.
    @~chinese 材质ID。
    */
    inline uint32_t getMaterialID() const { return _materialID; }
    /**
    @~english Get the openGL texture handle. 
    @~chinese 得到纹理的openGL句柄。
    @return @~english openGL texture handle.
    @~chinese 纹理的openGL句柄。
    */
    inline GLuint getTextureID() const { return _textureID; }
    /**
    @~english Get a const reference of triangles. 
    @~chinese 得到渲染三角形的数据。
    @return @~english The triangles to be rendered.
    @~chinese 待渲染三角形。
    */
    inline const Triangles& getTriangles() const { return _triangles; }
    /**
    @~english Get the vertex count in the triangles. 
    @~chinese 三角形的顶点数。
    @return @~english the vertex count.
    @~chinese 三角形的顶点数目。
    */
    inline ssize_t getVertexCount() const { return _triangles.vertCount; }
    /**
    @~english Get the index count of the triangles. 
    @~chinese 得到三角形的索引数目。
    @return @~english The index count.
    @~chinese 三角形的索引数目。
    */
    inline ssize_t getIndexCount() const { return _triangles.indexCount; }
    /**
    @~english Get the vertex data pointer. 
    @~chinese 得到顶点数据的指针。
    @return @~english The pointer of the vertex data.
    @~chinese 顶点数据的指针。
    */
    inline const V3F_C4B_T2F* getVertices() const { return _triangles.verts; }
    /**
    @~english Get the index data pointer. 
    @~chinese 得到索引数据的指针。
    @return @~english The pointer of index data.
    @~chinese 索引数据的指针。
    */
    inline const unsigned short* getIndices() const { return _triangles.indices; }
    /**
    @~english Get the GLProgram and uniform. 
    @~chinese 得到渲染的GLProgram和unifrom参数
    @return @~english GLProgram and its uniform.
    @~chinese GLProgram和uniform参数。
    */
    inline GLProgramState* getGLProgramState() const { return _glProgramState; }
    /**
    @~english Get the blend function. 
    @~chinese 得到混合函数。
    @return @~english The blend function.
    @~chinese 混合函数。
    */
    inline BlendFunc getBlendType() const { return _blendType; }
    /**
    @~english Get the model view matrix. 
    @~chinese 得到ModelView矩阵。
    @return @~english The ModelView matrix.
    @~chinese ModelView矩阵。
    */
    inline const Mat4& getModelView() const { return _mv; }
    
protected:
    /** Generate the material ID by textureID, glProgramState, and blend function. */
    void generateMaterialID();
    
    /** Generated material id. */
    uint32_t _materialID;
    /** OpenGL handle for texture.*/
    GLuint _textureID;
    /** GLprogramstate for the commmand. encapsulate shaders and uniforms. */
    GLProgramState* _glProgramState;
    /** Blend function when rendering the triangles.*/
    BlendFunc _blendType;
    /** Rendered triangles. */
    Triangles _triangles;
    /** Model view matrix when rendering the triangles.*/
    Mat4 _mv;
};

NS_CC_END
/**
 end of support group
 @}
 */
#endif // defined(__CC_TRIANGLES_COMMAND__)
