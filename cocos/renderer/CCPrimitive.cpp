/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2011      Zynga Inc.
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

NS_CC_BEGIN

Primitive* Primitive::create(VertexData* verts, IndexBuffer* indices, PrimitiveType type)
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

VertexData* Primitive::getVertexData()
{
    return _verts;
}

IndexBuffer* Primitive::getIndexData()
{
    return _indices;
}

Primitive::Primitive()
: _verts(nullptr)
, _indices(nullptr)
, _type(PrimitiveType::POINTS)
{
}

Primitive::~Primitive()
{
    CC_SAFE_RELEASE_NULL(_verts);
    CC_SAFE_RELEASE_NULL(_indices);
}

bool Primitive::init(VertexData* verts, IndexBuffer* indices, PrimitiveType type)
{
    if( nullptr == verts ) return false;
    if(verts != _verts)
    {
        CC_SAFE_RELEASE(_verts);
        CC_SAFE_RETAIN(verts);
        _verts = verts;
    }
    
    if(indices != _indices)
    {
        CC_SAFE_RETAIN(indices);
        CC_SAFE_RELEASE(_indices);
        _indices = indices;
    }
    
    _type = type;
    
    return true;
}

void Primitive::draw()
{
    if(_verts && _indices)
    {
        _verts->use();
        switch (_type) {
            case PrimitiveType::POINTS:
                if(_indices!= nullptr)
                {
                    GLenum type = (_indices->getType() == IndexBuffer::IndexType::INDEX_TYPE_SHORT_16) ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT;
                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indices->getVBO());
                    glDrawElements(GL_POINTS, _count, type, (GLvoid*)(_start * _indices->getSizePerIndex()));
                }
                else
                {
                    glDrawArrays(GL_POINTS, _count, _start);
                }
                break;
            case PrimitiveType::LINES:
                if(_indices!= nullptr)
                {
                    GLenum type = (_indices->getType() == IndexBuffer::IndexType::INDEX_TYPE_SHORT_16) ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT;
                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indices->getVBO());
                    glDrawElements(GL_LINES, _count, type, (GLvoid*)(_start * _indices->getSizePerIndex()));
                }
                else
                {
                    glDrawArrays(GL_LINES, _count, _start);
                }
                break;
            case PrimitiveType::TRIANGLES:
                if(_indices!= nullptr)
                {
                    GLenum type = (_indices->getType() == IndexBuffer::IndexType::INDEX_TYPE_SHORT_16) ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT;
                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indices->getVBO());
                    glDrawElements(GL_TRIANGLES, _count, type, (GLvoid*)(_start * _indices->getSizePerIndex()));
                }
                else
                {
                    glDrawArrays(GL_TRIANGLES, _count, _start);
                }
                break;
            default:
                CC_ASSERT(0);
                break;
        }
    }
}

NS_CC_END
