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
#include "renderer/CCTrianglesCommand.h"

NS_CC_BEGIN

/** Command used to render one or more Quads */
class CC_DLL QuadCommand : public TrianglesCommand
{
public:

    QuadCommand();
    ~QuadCommand();

    /** Initializes the command with a globalZOrder, a texture ID, a `GLProgram`, a blending function, a pointer to quads,
     * quantity of quads, and the Model View transform to be used for the quads */
    void init(float globalOrder, GLuint texutreID, GLProgramState* shader, BlendFunc blendType, V3F_C4B_T2F_Quad* quads, ssize_t quadCount,
              const Mat4& mv);

    inline const V3F_C4B_T2F_Quad* getQuads() const { return _quads; }
    inline ssize_t getQuadCount() const { return _quadsCount; }

protected:
    V3F_C4B_T2F_Quad* _quads;
    ssize_t _quadsCount;
};

NS_CC_END

#endif //_CC_QUADCOMMAND_H_
