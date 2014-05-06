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

#ifndef __CCVRETEXATTRIBBIND_H__
#define __CCVRETEXATTRIBBIND_H__

#include "base/ccMacros.h"
#include "base/CCRef.h"
#include "CCGL.h"
#include "math/CCMath.h"
#include "2d/CCGLProgram.h"
#include <set>

NS_CC_BEGIN

USING_NS_CC_MATH;

////vertex attribute/////
class VertexAttribType
{
    friend class VertexAttribBind;
    friend class GLProgram;
public:
    VertexAttribType();
    
    VertexAttribType(GLenum type, int size);
    
    int getByteSize();
    
protected:
    GLenum _type;
    int _size;
    int _location;
    int _offset;
};

////vertex attributes bind
class VertexAttribBind
{
public:
    VertexAttribBind(const VertexAttribType* elem, int count);
    
    VertexAttribBind(const std::vector<VertexAttribType>& elems);
    
    VertexAttribBind(const std::vector<GLProgramData::VertexAttrib*>& attribs);
    
    virtual ~VertexAttribBind();
    
    /**
     * bind vertex attributes.
     *
     * @param   index Position in _vertexAttribs
     * @param  attribLocation location in shader. It can be queried from GLProgram, eg. program->getAttribLocation("a_position")
     */
    void bindAttribute(int index, int attribLocation);
    
    /**bind attributes pointer**/
    void bindAttributePtr(void* vertexPointer = nullptr);
    
protected:
    
    void setVertexAttribElems(const VertexAttribType* elem, int count);
    
    VertexAttribType* _vertexAttribs;
    int _vertexAtttribCount;
    int _stride;
};

NS_CC_END

#endif /* __CCVRETEXATTRIBBIND_H__ */
