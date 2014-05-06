/****************************************************************************
 Copyright 2014 Chukong Technologies Inc.

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
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN false EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "base/CCDirector.h"
#include "2d/CCVertexAttribBind.h"
#include "2d/ccGLStateCache.h"
#include "base/ccMacros.h"
#include "2d/platform/CCFileUtils.h"
#include "2d/uthash.h"
#include "deprecated/CCString.h"

NS_CC_BEGIN

VertexAttribType::VertexAttribType(): _type(GL_FLOAT), _size(0), _location(-1), _offset(0)
{
}
VertexAttribType::VertexAttribType(GLenum type, int size): _type(type), _size(size), _location(-1), _offset(0)
{
    switch (type) {
        case GL_FLOAT_VEC2:
            _type = GL_FLOAT;
            _size = 2;
            break;
        case GL_FLOAT_VEC3:
            _type = GL_FLOAT;
            _size = 3;
            break;
        case GL_FLOAT_VEC4:
            _type = GL_FLOAT;
            _size = 4;
            break;
            
        default:
            break;
    }
}


int VertexAttribType::getByteSize()
{
    int byteSize = 0;
    switch (_type) {
        case GL_BYTE:
        case GL_UNSIGNED_BYTE:
            byteSize = _size;
            break;
        case GL_SHORT:
        case GL_UNSIGNED_SHORT:
            byteSize = _size * sizeof(GLshort);
            break;
        case GL_FLOAT:
            byteSize = _size * sizeof(GLfloat);
            break;
        default:
            CCASSERT(0,"type error");
            break;
    }
    return byteSize;
}

VertexAttribBind::VertexAttribBind(const VertexAttribType* elem, int count)
{
    setVertexAttribElems(elem, count);
}

VertexAttribBind::VertexAttribBind(const std::vector<VertexAttribType>& elems)
{
    setVertexAttribElems(&elems[0], elems.size());
}

VertexAttribBind::VertexAttribBind(const std::vector<GLProgramData::VertexAttrib*>& attribs)
{
    std::vector<VertexAttribType> elems;
    for (auto it = attribs.begin(); it != attribs.end(); it++) {
        VertexAttribType type((*it)->_type, (*it)->_size);
        type._location = (*it)->_index;
        elems.push_back(type);
    }
    setVertexAttribElems(&elems[0], elems.size());
}

VertexAttribBind::~VertexAttribBind()
{
    delete[] _vertexAttribs;
}

void VertexAttribBind::bindAttribute(int index, int attribLocation)
{
    //make sure index and attribute location are validate
    _vertexAttribs[index]._location = attribLocation;
}

//bind attributes pointer
void VertexAttribBind::bindAttributePtr(void* vertexPointer)
{
    for (auto i = 0; i < _vertexAtttribCount; i++) {
        auto elem = _vertexAttribs[i];
        if (elem._location != -1)
        {
            glEnableVertexAttribArray(elem._location);
            void* pointer = vertexPointer ? (void*)(((unsigned char*)vertexPointer) + elem._offset) : (void*)elem._offset;
            glVertexAttribPointer(elem._location, elem._size, elem._type, GL_FALSE, _stride, pointer);
        }
    }
}

void VertexAttribBind::setVertexAttribElems(const VertexAttribType* elem, int count)
{
    _vertexAtttribCount = count;
    _vertexAttribs = new VertexAttribType[count];
    _stride = 0;
    for (auto i = 0; i < count; i++) {
        _vertexAttribs[i] = elem[i];
        _vertexAttribs[i]._offset = _stride;
        _stride += _vertexAttribs[i].getByteSize();
    }
}

NS_CC_END
