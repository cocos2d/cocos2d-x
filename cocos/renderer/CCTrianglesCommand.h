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
#pragma once

#include "renderer/CCRenderCommand.h"
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
    class TextureBackend;
    class Program;
}

class Texture2D;

class CC_DLL TrianglesCommand : public RenderCommand
{
public:
    /**The structure of Triangles. */
    struct Triangles
    {
        Triangles(V3F_C4B_T2F* _verts, unsigned short* _indices, unsigned int _vertCount, unsigned int _indexCount)
        : verts(_verts)
        , indices(_indices)
        , vertCount(_vertCount)
        , indexCount(_indexCount)
        {}

        Triangles() {}

        /**Vertex data pointer.*/
        V3F_C4B_T2F* verts = nullptr;
        /**Index data pointer.*/
        unsigned short* indices = nullptr;
        /**The number of vertices.*/
        unsigned int vertCount = 0;
        /**The number of indices.*/
        unsigned int indexCount = 0;
    };

    /**Constructor.*/
    TrianglesCommand();
    /**Destructor.*/
    ~TrianglesCommand();
    
    /** Initializes the command.
     @param globalOrder GlobalZOrder of the command.
     @param texture The texture used in renderring.
     @param blendType Blend function for the command.
     @param triangles Rendered triangles for the command.
     @param mv ModelView matrix for the command.
     @param flags to indicate that the command is using 3D rendering or not.
     */
    void init(float globalOrder, cocos2d::Texture2D* texture, const BlendFunc& blendType,  const Triangles& triangles, const Mat4& mv, uint32_t flags);
    /**Get the material id of command.*/
    uint32_t getMaterialID() const { return _materialID; }
    /**Get a const reference of triangles.*/
    const Triangles& getTriangles() const { return _triangles; }
    /**Get the vertex count in the triangles.*/
    size_t getVertexCount() const { return _triangles.vertCount; }
    /**Get the index count of the triangles.*/
    size_t getIndexCount() const { return _triangles.indexCount; }
    /**Get the vertex data pointer.*/
    const V3F_C4B_T2F* getVertices() const { return _triangles.verts; }
    /**Get the index data pointer.*/
    const unsigned short* getIndices() const { return _triangles.indices; }
    /**Get the model view matrix.*/
    const Mat4& getModelView() const { return _mv; }
    
    /** update material ID */
    void updateMaterialID();
  
protected:
    /**Generate the material ID by textureID, glProgramState, and blend function.*/
    void generateMaterialID();
    
    /**Generated material id.*/
    uint32_t _materialID = 0;

    /**Rendered triangles.*/
    Triangles _triangles;
    /**Model view matrix when rendering the triangles.*/
    Mat4 _mv;

    uint8_t _alphaTextureID = 0; // ANDROID ETC1 ALPHA supports.

    // Cached value to determine to generate material id or not.
    BlendFunc _blendType = BlendFunc::DISABLE;
    backend::ProgramType _programType = backend::ProgramType::CUSTOM_PROGRAM;
    backend::TextureBackend* _texture = nullptr;
};

NS_CC_END
/**
 end of support group
 @}
 */
