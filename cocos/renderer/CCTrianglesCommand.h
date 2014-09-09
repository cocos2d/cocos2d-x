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

NS_CC_BEGIN
class CC_DLL TrianglesCommand : public RenderCommand
{
public:
    static const int MATERIAL_ID_DO_NOT_BATCH = 0;
    
public:
    struct Triangles
    {
        V3F_C4B_T2F* verts;
        unsigned short* indices;
        ssize_t vertCount;
        ssize_t indexCount;
    };
    
    TrianglesCommand();
    ~TrianglesCommand();
    
    /** Initializes the command with a globalZOrder, a texture ID, a `GLProgram`, a blending function, a pointer to triangles,
     * quantity of quads, and the Model View transform to be used for the quads */
    void init(float globalOrder, GLuint textureID, GLProgramState* glProgramState, BlendFunc blendType, const Triangles& triangles,const Mat4& mv);
    
    void useMaterial() const;
    
    inline uint32_t getMaterialID() const { return _materialID; }
    inline GLuint getTextureID() const { return _textureID; }
    inline const Triangles& getTriangles() const { return _triangles; }
    inline ssize_t getVertexCount() const { return _triangles.vertCount; }
    inline ssize_t getIndexCount() const { return _triangles.indexCount; }
    inline const V3F_C4B_T2F* getVertices() const { return _triangles.verts; }
    inline const unsigned short* getIndices() const { return _triangles.indices; }
    inline GLProgramState* getGLProgramState() const { return _glProgramState; }
    inline BlendFunc getBlendType() const { return _blendType; }
    inline const Mat4& getModelView() const { return _mv; }
    
protected:
    void generateMaterialID();
    
    uint32_t _materialID;
    GLuint _textureID;
    GLProgramState* _glProgramState;
    BlendFunc _blendType;
    Triangles _triangles;
    Mat4 _mv;
};

NS_CC_END

#endif // defined(__CC_TRIANGLES_COMMAND__)
