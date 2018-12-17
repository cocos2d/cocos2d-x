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

NS_CC_BEGIN

CustomCommand::CustomCommand()
//: func(nullptr)
{
    _type = RenderCommand::Type::CUSTOM_COMMAND;
}

CustomCommand& CustomCommand::operator=(const CustomCommand& rhs)
{
    RenderCommand::operator = (rhs);
    
    _vertexBuffer = rhs._vertexBuffer;
    CC_SAFE_RETAIN(_vertexBuffer);
    
    _indexBuffer = rhs._indexBuffer;
    CC_SAFE_RETAIN(_indexBuffer);
    
    _indexCount = rhs._indexCount;
    _vertexCount = rhs._vertexCount;
    
    _vertexStart = rhs._vertexStart;
    _vertexDrawCount = rhs._vertexDrawCount;
    
    _indexBufferOffset = rhs._indexBufferOffset;
    _indexDrawCount = rhs._indexDrawCount;
    
    _drawType = rhs._drawType;
    _primitiveType = rhs._primitiveType;
    
    return *this;
}

void CustomCommand::init(float depth, const cocos2d::Mat4 &modelViewTransform, uint32_t flags)
{
    RenderCommand::init(depth, modelViewTransform, flags);
}

void CustomCommand::init(float globalOrder)
{
    _globalOrder = globalOrder;
}

void CustomCommand::createVertexBuffer(size_t sizePerVertex, size_t count)
{
    CC_SAFE_RELEASE(_vertexBuffer);
    
    _vertexCount = count;
    
    auto device = backend::Device::getInstance();
    _vertexBuffer = device->newBuffer(sizePerVertex * count, backend::BufferType::VERTEX, backend::BufferUsage::READ);
}

void CustomCommand::createIndexBuffer(size_t sizePerIndex, size_t count)
{
    CC_SAFE_RELEASE(_indexBuffer);
    
    _indexCount = count;
    
    auto device = backend::Device::getInstance();
    _indexBuffer = device->newBuffer(sizePerIndex * count, backend::BufferType::INDEX, backend::BufferUsage::READ);
}

void CustomCommand::updateVertexBuffer(void* data, size_t offset, size_t length)
{   
    assert(_vertexBuffer);
    _vertexBuffer->updateData(data, offset, length);
}

void CustomCommand::updateIndexBuffer(void* data, size_t offset, size_t length)
{
    assert(_indexBuffer);
    _indexBuffer->updateData(data, offset, length);
}

CustomCommand::~CustomCommand()
{
    CC_SAFE_RELEASE(_vertexBuffer);
    CC_SAFE_RELEASE(_indexBuffer);
}

void CustomCommand::execute()
{
   if(func)
   {
       func();
   }
}

NS_CC_END
