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

#ifndef _CC_PRIMITIVE_COMMAND_H__
#define _CC_PRIMITIVE_COMMAND_H__

#include "renderer/CCPrimitive.h"
#include "renderer/CCRenderCommand.h"

NS_CC_BEGIN
class GLProgramState;
class CC_DLL PrimitiveCommand : public RenderCommand
{
public:
    PrimitiveCommand();
    ~PrimitiveCommand();
    
    void init(float globalOrder, GLuint textureID, GLProgramState* glProgramState, BlendFunc blendType, Primitive* primitive, const Mat4& mv, uint32_t flags);
    CC_DEPRECATED_ATTRIBUTE void init(float globalOrder, GLuint textureID, GLProgramState* glProgramState, BlendFunc blendType, Primitive* primitive,const Mat4& mv);
    
    inline uint32_t getMaterialID() const { return _materialID; }
    inline GLuint getTextureID() const { return _textureID; }
    inline GLProgramState* getGLProgramState() const { return _glProgramState; }
    inline BlendFunc getBlendType() const { return _blendType; }
    inline const Mat4& getModelView() const { return _mv; }
    
    void execute() const;
protected:
    
    uint32_t _materialID;
    GLuint _textureID;
    GLProgramState* _glProgramState;
    BlendFunc _blendType;
    Primitive* _primitive;
    Mat4 _mv;
};

NS_CC_END

#endif //_CC_PRIMITIVE_COMMAND_H__
