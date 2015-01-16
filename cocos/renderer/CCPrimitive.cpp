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

#include "renderer/CCPrimitive.h"
#include "renderer/CCVertexIndexBuffer.h"

NS_CC_BEGIN

Primitive* Primitive::create(VertexData* verts, IndexBuffer* indices, int type)
{
    auto result = new (std::nothrow) Primitive();
    if( result && result->init(verts, indices, type))
    {
        result->autorelease();
        return result;
    }

    CC_SAFE_DELETE(result);
    return  nullptr;
}

const VertexData* Primitive::getVertexData() const
{
    return _verts;
}

const IndexBuffer* Primitive::getIndexData() const
{
    return _indices;
}

NS_CC_END

