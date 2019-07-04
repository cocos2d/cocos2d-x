/****************************************************************************
 Copyright (c) 2018-2019 Xiamen Yaji Software Co., Ltd.

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

#include "base/ccMacros.h"
#include "platform/CCGL.h"
#include "renderer/backend/Types.h"

CC_BACKEND_BEGIN

class UtilsGL
{
public:
    static GLenum toGLAttributeType(VertexFormat texture);
    static GLsizei getGLAttributeSize(VertexFormat vertexFormat);
    static GLsizei getGLDataTypeSize(GLenum size);

    static GLint toGLMagFilter(SamplerFilter magFilter);
    static GLint toGLMinFilter(SamplerFilter minFilter, bool hasMipmaps, bool isPow2);
    static GLint toGLAddressMode(SamplerAddressMode addressMode, bool isPow2);
    static void toGLTypes(PixelFormat textureFormat, GLint &internalFormat, GLuint &format, GLenum &type, bool &isCompressed);

    static GLenum toGLComareFunction(CompareFunction compareFunction);
    static GLenum toGLStencilOperation(StencilOperation stencilOperation);

    static GLenum toGLBlendOperation(BlendOperation blendOperation);
    static GLenum toGLBlendFactor(BlendFactor blendFactor);

    static GLenum toGLFrontFace(Winding winding);
    static GLenum toGLPrimitiveType(PrimitiveType primitiveType);
    static GLenum toGLIndexType(IndexFormat indexType);
    static GLenum toGLCullMode(CullMode mode);
};

CC_BACKEND_END