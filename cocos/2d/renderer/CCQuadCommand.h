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

    void init(float depth, GLuint texutreID, GLProgram* shader, BlendFunc blendType, V3F_C4B_T2F_Quad* quads, ssize_t quadCount,
              const kmMat4& mv);

    void useMaterial() const;

    //TODO use material to decide if it is translucent
    inline bool isTranslucent() const { return true; }

    void generateMaterialID();
    inline uint32_t getMaterialID() const { return _materialID; }

    inline GLuint getTextureID() const { return _textureID; }

    inline V3F_C4B_T2F_Quad* getQuads() const { return _quads; }

    inline ssize_t getQuadCount() const { return _quadsCount; }

    inline GLProgram* getShader() const { return _shader; }

    inline BlendFunc getBlendType() const { return _blendType; }

    inline const kmMat4& getModelView() const { return _mv; }
    
protected:
    uint32_t _materialID;

    //Maternal
    GLuint _textureID;

    GLProgram* _shader;
//    GLuint _shaderID;

    BlendFunc _blendType;

    V3F_C4B_T2F_Quad* _quads;
    ssize_t _quadsCount;

    kmMat4 _mv;
};
NS_CC_END

#endif //_CC_QUADCOMMAND_H_
