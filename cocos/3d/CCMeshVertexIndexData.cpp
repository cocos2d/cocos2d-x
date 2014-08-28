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

#include <list>
#include <fstream>
#include <iostream>
#include <sstream>

#include "3d/CCMeshVertexIndexData.h"
#include "3d/CCObjLoader.h"
#include "3d/CCSprite3DMaterial.h"
#include "3d/CCMesh.h"

#include "base/ccMacros.h"
#include "base/CCEventCustom.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventType.h"
#include "base/CCDirector.h"
#include "renderer/ccGLStateCache.h"


using namespace std;

NS_CC_BEGIN


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
MeshIndexData* MeshIndexData::create(const std::string& id, MeshVertexData* vertexData, IndexBuffer* indexbuffer, const AABB& aabb)
{
    auto meshindex = new (std::nothrow) MeshIndexData();
    
    meshindex->_id = id;
    meshindex->_indexBuffer = indexbuffer;
    meshindex->_vertexData = vertexData;
    indexbuffer->retain();
    vertexData->retain();
    meshindex->_aabb = aabb;
    
    meshindex->autorelease();
    return meshindex;
}

const VertexBuffer* MeshIndexData::getVertexBuffer() const
{
    return _vertexData->getVertexBuffer();
}

MeshIndexData::MeshIndexData()
: _indexBuffer(nullptr)
, _vertexData(nullptr)
, _primitiveType(GL_TRIANGLES)
{
    
}
MeshIndexData::~MeshIndexData()
{
    CC_SAFE_RELEASE(_indexBuffer);
    CC_SAFE_RELEASE(_vertexData);
}

MeshVertexData* MeshVertexData::create(const MeshData& meshdata)
{
    auto vertexdata = new (std::nothrow) MeshVertexData();
    int pervertexsize = meshdata.getPerVertexSize();
    vertexdata->_vertexBuffer = VertexBuffer::create(pervertexsize, (int)(meshdata.vertex.size() / (pervertexsize / 4)));
    vertexdata->_vertexData = VertexData::create();
    CC_SAFE_RETAIN(vertexdata->_vertexData);
    CC_SAFE_RETAIN(vertexdata->_vertexBuffer);
    
    int offset = 0;
    for (const auto& it : meshdata.attribs) {
        vertexdata->_vertexData->setStream(vertexdata->_vertexBuffer, VertexStreamAttribute(offset, it.vertexAttrib, it.type, it.size));
        offset += it.attribSizeBytes;
    }
    vertexdata->_vertexData->setStream(vertexdata->_vertexBuffer, VertexStreamAttribute(0, GLProgram::VERTEX_ATTRIB_POSITION, GL_FLOAT, 3));
    vertexdata->_vertexData->setStream(vertexdata->_vertexBuffer, VertexStreamAttribute(offsetof(V3F_C4B_T2F, colors), GLProgram::VERTEX_ATTRIB_COLOR, GL_UNSIGNED_BYTE, 4, true));
    vertexdata->_vertexData->setStream(vertexdata->_vertexBuffer, VertexStreamAttribute(offsetof(V3F_C4B_T2F, texCoords), GLProgram::VERTEX_ATTRIB_TEX_COORD, GL_FLOAT, 2));
    
    vertexdata->_attribs = meshdata.attribs;
    
    if(vertexdata->_vertexBuffer)
    {
        vertexdata->_vertexBuffer->updateVertices((void*)&meshdata.vertex[0], (int)meshdata.vertex.size() * 4, 0);
    }
    
    AABB aabb;
    for (size_t i = 0; i < meshdata.subMeshIndices.size(); i++) {
        
        auto& index = meshdata.subMeshIndices[i];
        auto indexBuffer = IndexBuffer::create(IndexBuffer::IndexType::INDEX_TYPE_SHORT_16, (int)(index.size()));
        indexBuffer->updateIndices(&index[0], (int)index.size(), 0);
        aabb = MeshVertexData::calculateAABB(meshdata.vertex, meshdata.getPerVertexSize(), index);
        std::string id = (i < meshdata.subMeshIds.size() ? meshdata.subMeshIds[i] : "");
        MeshIndexData* indexdata = MeshIndexData::create(id, vertexdata, indexBuffer, aabb);
        vertexdata->_indexs.pushBack(indexdata);
    }
    
    vertexdata->autorelease();
    return vertexdata;
}

const AABB& MeshVertexData::calculateAABB(const std::vector<float>& vertex, int stride, const std::vector<unsigned short>& index)
{
    static AABB aabb;
    stride /= 4;
    for(const auto& it : index)
    {
        Vec3 point = Vec3(vertex[it * stride ], vertex[ it * stride + 1], vertex[it * stride + 2 ]);
        aabb.updateMinMax(&point, 1);
    }
    return aabb;
}

MeshIndexData* MeshVertexData::getMeshIndexDataById(const std::string& id) const
{
    for (auto it : _indexs) {
        if (it->getId() == id)
            return it;
    }
    return nullptr;
}

bool MeshVertexData::hasVertexAttrib(int attrib) const
{
    for (const auto& it : _attribs) {
        if (it.vertexAttrib == attrib)
            return true;
    }
    return false;
}

MeshVertexData::MeshVertexData()
: _vertexData(nullptr)
, _vertexBuffer(nullptr)
, _vertexCount(0)
{
    
}
MeshVertexData::~MeshVertexData()
{
    CC_SAFE_RELEASE(_vertexData);
    CC_SAFE_RELEASE(_vertexBuffer);
    _indexs.clear();
}

NS_CC_END
