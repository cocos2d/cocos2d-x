/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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
#include "renderer/CCPipelineDescriptor.h"

/**
 * @addtogroup renderer
 * @{
 */

NS_CC_BEGIN
/** 
 Command used to render one or more Triangles, which is similar to QuadCommand.
 Every TrianglesCommand will have generate material ID by give textureID, glProgramState, Blend function
 if the material id is the same, these TrianglesCommands could be batched to save draw call.
*/
namespace backend {
    class Texture;
}
class CC_DLL TrianglesCommand : public RenderCommand
{
public:
    /**The structure of Triangles. */
    struct Triangles
    {
        /**Vertex data pointer.*/
        V3F_C4B_T2F* verts;
        /**Index data pointer.*/
        unsigned short* indices;
        /**The number of vertices.*/
        int vertCount;
        /**The number of indices.*/
        int indexCount;
    };
    /**Constructor.*/
    TrianglesCommand();
    /**Destructor.*/
    ~TrianglesCommand();

    virtual size_t copyVertexData(void*) const override;
    virtual size_t copyIndexData(void*) const override;
    
    /** Initializes the command.
     @param globalOrder GlobalZOrder of the command.
     @param textureID The openGL handle of the used texture.
     @param glProgramState The specified glProgram and its uniform.
     @param blendType Blend function for the command.
     @param triangles Rendered triangles for the command.
     @param mv ModelView matrix for the command.
     @param flags to indicate that the command is using 3D rendering or not.
     */
    void init(float globalOrder, GLuint textureID, GLProgramState* glProgramState, BlendFunc blendType, const Triangles& triangles,const Mat4& mv, uint32_t flags);
    void init(float globalOrder, Texture2D* textureID, GLProgramState* glProgramState, BlendFunc blendType, const Triangles& triangles, const Mat4& mv, uint32_t flags);
    void init(float globalOrder, backend::Texture* textureID, GLProgramState* glProgramState, BlendFunc blendType, const Triangles& triangles, const Mat4& mv, uint32_t flags);
    void init(float globalOrder, const Triangles& triangles, const Mat4& mv, uint32_t flags);
    /**Apply the texture, shaders, programs, blend functions to GPU pipeline.*/
    void useMaterial() const;
    /**Get the material id of command.*/
    uint32_t getMaterialID() const { return _materialID; }
    /**Get the openGL texture handle.*/
    GLuint getTextureID() const { return _textureID; }
    /**Get a const reference of triangles.*/
    const Triangles& getTriangles() const { return _triangles; }
    /**Get the vertex count in the triangles.*/
    ssize_t getVertexCount() const { return _triangles.vertCount; }
    /**Get the index count of the triangles.*/
    ssize_t getIndexCount() const { return _triangles.indexCount; }
    size_t getIndexSize() const { return sizeof(_triangles.indices[0]); }
    /**Get the vertex data pointer.*/
    const V3F_C4B_T2F* getVertices() const { return _triangles.verts; }
    /**Get the index data pointer.*/
    const unsigned short* getIndices() const { return _triangles.indices; }
    /**Get the glprogramstate.*/
    GLProgramState* getGLProgramState() const { return _glProgramState; }
    /**Get the blend function.*/
    BlendFunc getBlendType() const { return _blendType; }
    /**Get the model view matrix.*/
    const Mat4& getModelView() const { return _mv; }
     /**Get the PipelineDescriptor.*/
    
protected:
    /**Generate the material ID by textureID, glProgramState, and blend function.*/
    void generateMaterialID();
    
    /**Generated material id.*/
    uint32_t _materialID = 0;
    /**OpenGL handle for texture.*/
    GLuint _textureID = 0;
    /**GLprogramstate for the command. encapsulate shaders and uniforms.*/
    GLProgramState* _glProgramState = nullptr;
    /**Blend function when rendering the triangles.*/
    BlendFunc _blendType = BlendFunc::DISABLE;
    /**Rendered triangles.*/
    Triangles _triangles;
    /**Model view matrix when rendering the triangles.*/
    Mat4 _mv;

    GLuint _alphaTextureID = 0; // ANDROID ETC1 ALPHA supports.
};

NS_CC_END
/**
 end of support group
 @}
 */
#endif // defined(__CC_TRIANGLES_COMMAND__)
