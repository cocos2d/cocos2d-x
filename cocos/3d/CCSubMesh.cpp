/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

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

#include "CCSubMesh.h"

#include <list>
#include <fstream>
#include <iostream>
#include <sstream>

#include "3d/CCObjLoader.h"
#include "3d/CCSprite3DMaterial.h"

#include "base/ccMacros.h"
#include "base/CCEventCustom.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventType.h"
#include "base/CCDirector.h"
#include "renderer/ccGLStateCache.h"


using namespace std;

NS_CC_BEGIN

SubMesh::SubMesh()
: _indexBuffer(0)
, _primitiveType(PrimitiveType::TRIANGLES)
, _indexFormat(IndexFormat::INDEX16)
, _indexCount(0)
{
}

SubMesh::~SubMesh()
{
    cleanAndFreeBuffers();
}

SubMesh* SubMesh::create(PrimitiveType primitivetype, IndexFormat indexformat, const std::vector<unsigned short>& indices)
{
    auto submesh = new SubMesh();
    submesh->_primitiveType = primitivetype;
    submesh->_indexFormat = indexformat;
    submesh->autorelease();
    
    return submesh;
}

void SubMesh::cleanAndFreeBuffers()
{
    if(glIsBuffer(_indexBuffer))
    {
        glDeleteBuffers(1, &_indexBuffer);
        _indexBuffer = 0;
    }
    
    _indexCount = 0;
}

void SubMesh::buildBuffer(const std::vector<unsigned short>& indices)
{
    glGenBuffers(1, &_indexBuffer);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    
    unsigned int indexSize = 2;
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize * indices.size(), &indices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    _indexCount = indices.size();
}

NS_CC_END
