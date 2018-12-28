/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
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
#include "renderer/CCCustomCommand.h"
#include "renderer/CCTextureAtlas.h"
#include "renderer/backend/Buffer.h"
#include "renderer/backend/Device.h"
#include "base/ccUtils.h"

NS_CC_BEGIN

CustomCommand::CustomCommand()
{
    _type = RenderCommand::Type::CUSTOM_COMMAND;
}

void CustomCommand::init(float depth, const cocos2d::Mat4 &modelViewTransform, unsigned int flags)
{
    RenderCommand::init(depth, modelViewTransform, flags);
}

void CustomCommand::init(float globalZOrder)
{
    _globalOrder = globalZOrder;
}

void CustomCommand::init(float globalZOrder, const BlendFunc& blendFunc)
{
    _globalOrder = globalZOrder;

    auto& blendDescriptor = _pipelineDescriptor.blendDescriptor;
    blendDescriptor.blendEnabled = true;
    blendDescriptor.sourceRGBBlendFactor = blendDescriptor.sourceAlphaBlendFactor = utils::toBackendBlendFactor(blendFunc.src);
    blendDescriptor.destinationRGBBlendFactor = blendDescriptor.destinationAlphaBlendFactor = utils::toBackendBlendFactor(blendFunc.dst);
}

void CustomCommand::createVertexBuffer(unsigned int vertexSize, unsigned int count)
{
    CC_SAFE_RELEASE(_vertexBuffer);
    
    _vertexSize = vertexSize;
    
    auto device = backend::Device::getInstance();
    _vertexBuffer = device->newBuffer(vertexSize * count, backend::BufferType::VERTEX, backend::BufferUsage::READ);
}

void CustomCommand::createIndexBuffer(unsigned int indexSize, unsigned int count)
{
    CC_SAFE_RELEASE(_indexBuffer);
    
    _indexSize = indexSize;
    
    auto device = backend::Device::getInstance();
    _indexBuffer = device->newBuffer(indexSize * count, backend::BufferType::INDEX, backend::BufferUsage::READ);
}

void CustomCommand::updateVertexBuffer(void* data, unsigned int offset, unsigned int length)
{   
    assert(_vertexBuffer);
    if (offset)
        _vertexCount += length / _vertexSize;
    else
        _vertexCount = length / _vertexSize;
    
    _vertexBuffer->updateSubData(data, offset, length);
}

void CustomCommand::updateIndexBuffer(void* data, unsigned int offset, unsigned int length)
{
    assert(_indexBuffer);
    if (offset)
        _indexCount += length / _indexSize;
    else
        _indexCount = length / _indexSize;
    
    _indexBuffer->updateSubData(data, offset, length);
}

void CustomCommand::updateVertexBuffer(void* data, unsigned int length)
{
    assert(_vertexBuffer);
    _vertexCount = length/_vertexSize;
    _vertexBuffer->updateData(data, length);
}

void CustomCommand::updateIndexBuffer(void* data, unsigned int length)
{
    assert(_indexBuffer);
    _indexCount = length / _indexSize;
    _indexBuffer->updateData(data, length);
}

CustomCommand::~CustomCommand()
{
    CC_SAFE_RELEASE(_vertexBuffer);
    CC_SAFE_RELEASE(_indexBuffer);
}

void CustomCommand::clear()
{
    _vertexCount = 0;
    _indexCount = 0;
    _vertexStart = 0;
    _vertexDrawCount = 0;
    _indexBufferOffset = 0;
    _indexDrawCount = 0;
}

NS_CC_END
