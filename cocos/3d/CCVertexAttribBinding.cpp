/**
 Copyright 2013 BlackBerry Inc.
 Copyright (c) 2015-2017 Chukong Technologies
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.

 Original file from GamePlay3D: http://gameplay3d.org

 This file was modified to fit the cocos2d-x project
 */

#include "renderer/backend/Program.h"
#include "renderer/CCPass.h"
#include "base/CCConfiguration.h"
#include "3d/CCMeshVertexIndexData.h"
#include "3d/CC3DProgramInfo.h"
#include "3d/CCVertexAttribBinding.h"

NS_CC_BEGIN


static std::vector<VertexAttribBinding*> __vertexAttribBindingCache;

VertexAttribBinding::VertexAttribBinding() :
    _meshIndexData(nullptr), _programState(nullptr), _attributes()
{
}

VertexAttribBinding::~VertexAttribBinding()
{
    // Delete from the vertex attribute binding cache.
    std::vector<VertexAttribBinding*>::iterator itr = std::find(__vertexAttribBindingCache.begin(), __vertexAttribBindingCache.end(), this);
    if (itr != __vertexAttribBindingCache.end())
    {
        __vertexAttribBindingCache.erase(itr);
    }

    CC_SAFE_RELEASE(_meshIndexData);
    CC_SAFE_RELEASE(_programState);
    _attributes.clear();
}

VertexAttribBinding* VertexAttribBinding::create(MeshIndexData* meshIndexData, Pass* pass, MeshCommand *command)
{
    CCASSERT(meshIndexData && pass && pass->getProgramState(), "Invalid MeshIndexData and/or programState");

    // Search for an existing vertex attribute binding that can be used.
    VertexAttribBinding* b;
    for (size_t i = 0, count = __vertexAttribBindingCache.size(); i < count; ++i)
    {
        b = __vertexAttribBindingCache[i];
        CC_ASSERT(b);
        if (b->_meshIndexData == meshIndexData && b->_programState == pass->getProgramState())
        {
            // Found a match!
            return b;
        }
    }

    b = new (std::nothrow) VertexAttribBinding();
    if (b && b->init(meshIndexData, pass, command))
    {
        b->autorelease();
        __vertexAttribBindingCache.push_back(b);
    }

    return b;
}

bool VertexAttribBinding::init(MeshIndexData* meshIndexData, Pass* pass, MeshCommand *command)
{

    CCASSERT(meshIndexData && pass && pass->getProgramState(), "Invalid arguments");

    auto programState = pass->getProgramState();

    _vertexLayout = programState->getVertexLayout();

    _meshIndexData = meshIndexData;
    _meshIndexData->retain();
    _programState = programState;
    _programState->retain();

    auto meshVertexData = meshIndexData->getMeshVertexData();
    auto attributeCount = meshVertexData->getMeshVertexAttribCount();


    // Parse and set attributes
    parseAttributes();
    int offset = 0;
    for (auto k = 0; k < attributeCount; k++)
    {
        auto meshattribute = meshVertexData->getMeshVertexAttrib(k);
        setVertexAttribPointer(
                               shaderinfos::getAttributeName(meshattribute.vertexAttrib),
                               meshattribute.type,
                               false,
                               offset, 
                               1 << k 
            );
        offset += meshattribute.getAttribSizeBytes();
    }

    _vertexLayout->setLayout(offset);

    CCASSERT(offset == meshVertexData->getSizePerVertex(), "vertex layout mismatch!");

    return true;
}

uint32_t VertexAttribBinding::getVertexAttribsFlags() const
{
    return _vertexAttribsFlags;
}

void VertexAttribBinding::parseAttributes()
{
    CCASSERT(_programState, "invalid glprogram");

    _attributes.clear();
    _vertexAttribsFlags = 0;

    auto program = _programState->getProgram();
    auto& attributes = program->getActiveAttributes();
    _attributes =  attributes;
}

bool VertexAttribBinding::hasAttribute(const shaderinfos::VertexKey &key) const
{
    auto &name = shaderinfos::getAttributeName(key);
    return _attributes.find(name) != _attributes.end();
}

backend::AttributeBindInfo* VertexAttribBinding::getVertexAttribValue(const std::string& name)
{
    const auto itr = _attributes.find(name);
    if( itr != _attributes.end())
        return &itr->second;
    return nullptr;
}

void VertexAttribBinding::setVertexAttribPointer(const std::string &name, backend::VertexFormat type, bool normalized, int offset, int flag)
{
    auto v = getVertexAttribValue(name);
    if(v) {
        // CCLOG("cocos2d: set attribute '%s' location: %d, offset: %d", name.c_str(), v->location, offset);
        _vertexLayout->setAttribute(name, v->location, type, offset, normalized);
        _vertexAttribsFlags |= flag;
    }
    else
    {
        // CCLOG("cocos2d: warning: Attribute not found: %s", name.c_str());
    }
}

NS_CC_END
