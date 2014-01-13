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

#include "CCRenderCommand.h"
#include "CCGLProgram.h"
#include "CCRenderCommandPool.h"
#include "kazmath/kazmath.h"

NS_CC_BEGIN

#define CC_NO_TEXTURE 0

class QuadCommand : public RenderCommand
{
public:

    QuadCommand();
    ~QuadCommand();

    void init(int viewport, int32_t depth, GLuint texutreID, GLProgram* shader, BlendFunc blendType, V3F_C4B_T2F_Quad* quad, ssize_t quadCount,
              const kmMat4& mv);

    // +----------+----------+-----+-----------------------------------+
    // |          |          |     |                |                  |
    // | ViewPort | Transluc |     |      Depth     |  Material ID     |
    // |   3 bits |    1 bit |     |    24 bits     |      24 bit2     |
    // +----------+----------+-----+----------------+------------------+
    virtual int64_t generateID();

    void useMaterial();

    //TODO use material to decide if it is translucent
    inline bool isTranslucent() const { return true; }

    inline int32_t getMaterialID() const { return _materialID; }

    inline GLuint getTextureID() const { return _textureID; }

    inline V3F_C4B_T2F_Quad* getQuad() const { return _quad; }

    inline ssize_t getQuadCount() const { return _quadCount; }

    inline GLProgram* getShader() const { return _shader; }

    inline BlendFunc getBlendType() const { return _blendType; }
    
protected:
    int32_t _materialID;

    //Key Data
    int _viewport;          /// Which view port it belongs to

    //TODO use material to determine if it's translucent
    int32_t _depth;

    //Maternal
    GLuint _textureID;

    GLProgram* _shader;
//    GLuint _shaderID;

    BlendFunc _blendType;

    V3F_C4B_T2F_Quad* _quad;
    ssize_t _quadCount;
    ssize_t _capacity;
};
NS_CC_END

#endif //_CC_QUADCOMMAND_H_
