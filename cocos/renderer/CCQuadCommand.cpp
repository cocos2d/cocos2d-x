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
#include "xxhash.h"
#include "renderer/CCRenderer.h"

NS_CC_BEGIN

QuadCommand::QuadCommand()
:_quads(nullptr)
,_quadsCount(0)
{
    _type = RenderCommand::Type::QUAD_COMMAND;
}

void QuadCommand::init(float globalOrder, GLuint textureID, GLProgramState* glProgramState, BlendFunc blendType, V3F_C4B_T2F_Quad* quad, ssize_t quadCount, const Mat4 &mv)
{
    CCASSERT(glProgramState, "Invalid GLProgramState");
    CCASSERT(glProgramState->getVertexAttribsFlags() == 0, "No custom attributes are supported in QuadCommand");

    _globalOrder = globalOrder;

    _quadsCount = quadCount;
    _quads = quad;
    
    //generate triangles
    {
        static std::vector<GLushort> QUADINDICESMAX;
        if(QUADINDICESMAX.size() == 0)
        {
            QUADINDICESMAX.resize(Renderer::INDEX_VBO_SIZE);
            for(ssize_t i = 0; i < Renderer::INDEX_VBO_SIZE / 6; ++i)
            {
                QUADINDICESMAX[ 6 * i + 0] = 4 * i + 0;
                QUADINDICESMAX[ 6 * i + 1] = 4 * i + 1;
                QUADINDICESMAX[ 6 * i + 2] = 4 * i + 2;
                QUADINDICESMAX[ 6 * i + 3] = 4 * i + 3;
                QUADINDICESMAX[ 6 * i + 4] = 4 * i + 2;
                QUADINDICESMAX[ 6 * i + 5] = 4 * i + 1;
            }
        }
        
        _triangles.vertCount = quadCount * 4;
        _triangles.indexCount = quadCount * 6;
        _triangles.indices = &QUADINDICESMAX[0];
        _triangles.verts = &quad->tl;
    }

    _mv = mv;

    if( _textureID != textureID || _blendType.src != blendType.src || _blendType.dst != blendType.dst || _glProgramState != glProgramState) {

        _textureID = textureID;
        _blendType = blendType;
        _glProgramState = glProgramState;

        generateMaterialID();
    }
}

QuadCommand::~QuadCommand()
{
}

NS_CC_END
