/****************************************************************************
 Copyright (c) 2014-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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
#include "3d/CCBundle3D.h"

#include "base/ccMacros.h"
#include "base/CCEventCustom.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventType.h"
#include "base/CCDirector.h"

#include "renderer/backend/Buffer.h"
#include "renderer/backend/Device.h"

using namespace std;

NS_CC_BEGIN


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
MeshIndexData* MeshIndexData::create(const std::string& id, MeshVertexData* vertexData, backend::Buffer* indexbuffer, const AABB& aabb)
{
    auto meshindex = new (std::nothrow) MeshIndexData();
    
    meshindex->_id = id;
    meshindex->_indexBuffer = indexbuffer;
    meshindex->_vertexData = vertexData;
    indexbuffer->retain();
    meshindex->_aabb = aabb;
    
    meshindex->autorelease();
    return meshindex;
}

backend::Buffer* MeshIndexData::getVertexBuffer() const
{
    return _vertexData->getVertexBuffer();
}

MeshIndexData::MeshIndexData()
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    _backToForegroundListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom*){
        _indexBuffer->updateData((void*)_indexData.data(), _indexData.size() * sizeof(_indexData[0]));
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backToForegroundListener, 1);
#endif
}

void MeshIndexData::setIndexData(const cocos2d::MeshData::IndexArray &indexdata)
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    if(_indexData.size() > 0)
        return;
    _indexData = indexdata;
#endif
}

MeshIndexData::~MeshIndexData()
{
    CC_SAFE_RELEASE(_indexBuffer);
    _indexData.clear();
#if CC_ENABLE_CACHE_TEXTURE_DATA
    Director::getInstance()->getEventDispatcher()->removeEventListener(_backToForegroundListener);
#endif
}

void MeshVertexData::setVertexData(const std::vector<float> &vertexData)
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    if(_vertexData.size() > 0)
        return;
    _vertexData = vertexData;
#endif
}

MeshVertexData* MeshVertexData::create(const MeshData& meshdata)
{
    auto vertexdata = new (std::nothrow) MeshVertexData();
    vertexdata->_vertexBuffer = backend::Device::getInstance()->newBuffer(meshdata.vertex.size() * sizeof(meshdata.vertex[0]), backend::BufferType::VERTEX, backend::BufferUsage::STATIC);
    //CC_SAFE_RETAIN(vertexdata->_vertexBuffer);
    
    vertexdata->_sizePerVertex = meshdata.getPerVertexSize();

    vertexdata->_attribs = meshdata.attribs;
    
    if(vertexdata->_vertexBuffer)
    {
#if CC_ENABLE_CACHE_TEXTURE_DATA
        vertexdata->setVertexData(meshdata.vertex);
        vertexdata->_vertexBuffer->usingDefaultStoredData(false);
#endif
        vertexdata->_vertexBuffer->updateData((void*)&meshdata.vertex[0], meshdata.vertex.size() * sizeof(meshdata.vertex[0]));
    }
    
    bool needCalcAABB = (meshdata.subMeshAABB.size() != meshdata.subMeshIndices.size());
    for (size_t i = 0, size = meshdata.subMeshIndices.size(); i < size; ++i)
    {
        auto& index = meshdata.subMeshIndices[i];
        auto indexBuffer = backend::Device::getInstance()->newBuffer(index.size() * sizeof(index[0]), backend::BufferType::INDEX, backend::BufferUsage::STATIC);
        indexBuffer->autorelease();
#if CC_ENABLE_CACHE_TEXTURE_DATA
        indexBuffer->usingDefaultStoredData(false);
#endif
        indexBuffer->updateData((void*)index.data(), index.size() * sizeof(index[0]));
        
        std::string id = (i < meshdata.subMeshIds.size() ? meshdata.subMeshIds[i] : "");
        MeshIndexData* indexdata = nullptr;
        if (needCalcAABB)
        {
            auto aabb = Bundle3D::calculateAABB(meshdata.vertex, meshdata.getPerVertexSize(), index);
            indexdata = MeshIndexData::create(id, vertexdata, indexBuffer, aabb);
        }
        else
            indexdata = MeshIndexData::create(id, vertexdata, indexBuffer, meshdata.subMeshAABB[i]);
#if CC_ENABLE_CACHE_TEXTURE_DATA
        indexdata->setIndexData(index);
#endif
        vertexdata->_indexs.pushBack(indexdata);
    }
    
    vertexdata->autorelease();
    return vertexdata;
}

MeshIndexData* MeshVertexData::getMeshIndexDataById(const std::string& id) const
{
    for (auto it : _indexs) {
        if (it->getId() == id)
            return it;
    }
    return nullptr;
}

bool MeshVertexData::hasVertexAttrib(shaderinfos::VertexKey attrib) const
{
    for (const auto& it : _attribs) {
        if (it.vertexAttrib == attrib)
            return true;
    }
    return false;
}

MeshVertexData::MeshVertexData()
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    _backToForegroundListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom*){
        _vertexBuffer->updateData((void*)_vertexData.data(), _vertexData.size() * sizeof(_vertexData[0]));
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backToForegroundListener, 1);
#endif
}

MeshVertexData::~MeshVertexData()
{
    CC_SAFE_RELEASE(_vertexBuffer);
    _indexs.clear();
    _vertexData.clear();
#if CC_ENABLE_CACHE_TEXTURE_DATA
    Director::getInstance()->getEventDispatcher()->removeEventListener(_backToForegroundListener);
#endif
}

NS_CC_END
