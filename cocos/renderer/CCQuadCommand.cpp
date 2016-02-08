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


#include "renderer/CCQuadCommand.h"

#include "renderer/ccGLStateCache.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCMaterial.h"
#include "renderer/CCTechnique.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCPass.h"

#include "xxhash.h"

NS_CC_BEGIN

int QuadCommand::__indexCapacity = -1;
GLushort* QuadCommand::__indices = nullptr;

QuadCommand::QuadCommand()
: _indexSize(-1)
{
}

QuadCommand::~QuadCommand()
{
}

void QuadCommand::init(float globalOrder, GLuint textureID, GLProgramState* glProgramState, const BlendFunc& blendType, V3F_C4B_T2F_Quad* quads, ssize_t quadCount,
                       const Mat4& mv, uint32_t flags)
{
    CCASSERT(glProgramState, "Invalid GLProgramState");
    CCASSERT(glProgramState->getVertexAttribsFlags() == 0, "No custom attributes are supported in QuadCommand");

    if (quadCount * 6 > _indexSize)
        reIndex((int)quadCount*6);

    Triangles triangles;
    triangles.verts = &quads->tl;
    triangles.vertCount = (int)quadCount * 4;
    triangles.indices = __indices;
    triangles.indexCount = (int)quadCount * 6;
    TrianglesCommand::init(globalOrder, textureID, glProgramState, blendType, triangles, mv, flags);
}

void QuadCommand::reIndex(int indicesCount)
{
    if (indicesCount > __indexCapacity)
    {
        CCLOG("cocos2d: QuadCommand: resizing index size from [%d] to [%d]", __indexCapacity, indicesCount);
        __indices = (GLushort*) realloc(__indices, indicesCount * sizeof(__indices[0]));
        __indexCapacity = indicesCount;
    }

    for( int i=0; i < __indexCapacity/6; i++)
    {
        __indices[i*6+0] = (GLushort) (i*4+0);
        __indices[i*6+1] = (GLushort) (i*4+1);
        __indices[i*6+2] = (GLushort) (i*4+2);
        __indices[i*6+3] = (GLushort) (i*4+3);
        __indices[i*6+4] = (GLushort) (i*4+2);
        __indices[i*6+5] = (GLushort) (i*4+1);
    }

    _indexSize = indicesCount;
}

void QuadCommand::init(float globalOrder, GLuint textureID, GLProgramState* shader, const BlendFunc& blendType, V3F_C4B_T2F_Quad* quads, ssize_t quadCount, const Mat4 &mv)
{
    init(globalOrder, textureID, shader, blendType, quads, quadCount, mv, 0);
}


NS_CC_END