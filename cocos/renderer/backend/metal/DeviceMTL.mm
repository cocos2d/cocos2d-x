/****************************************************************************
 Copyright (c) 2018-2019 Xiamen Yaji Software Co., Ltd.

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
 
#include "DeviceMTL.h"
#include "CommandBufferMTL.h"
#include "BufferMTL.h"
#include "RenderPipelineMTL.h"
#include "ShaderModuleMTL.h"
#include "DepthStencilStateMTL.h"
#include "TextureMTL.h"
#include "Utils.h"
#include "ProgramMTL.h"
#include "DeviceInfoMTL.h"

#include "base/ccMacros.h"

CC_BACKEND_BEGIN

CAMetalLayer* DeviceMTL::_metalLayer = nil;
id<CAMetalDrawable> DeviceMTL::_currentDrawable = nil;

Device* Device::getInstance()
{
    if (! Device::_instance)
        Device::_instance = new (std::nothrow) DeviceMTL();

    return Device::_instance;
}

void DeviceMTL::setCAMetalLayer(CAMetalLayer* metalLayer)
{
    DeviceMTL::_metalLayer = metalLayer;
}

id<CAMetalDrawable> DeviceMTL::getCurrentDrawable()
{
    if (! DeviceMTL::_currentDrawable)
        DeviceMTL::_currentDrawable = [DeviceMTL::_metalLayer nextDrawable];
    
    return DeviceMTL::_currentDrawable;
}

void DeviceMTL::resetCurrentDrawable()
{
    DeviceMTL::_currentDrawable = nil;
}

DeviceMTL::DeviceMTL()
{
    _mtlDevice = DeviceMTL::_metalLayer.device;
    _mtlCommandQueue = [_mtlDevice newCommandQueue];
    _deviceInfo = new (std::nothrow) DeviceInfoMTL(_mtlDevice);
    if(!_deviceInfo || _deviceInfo->init() == false)
    {
        delete _deviceInfo;
        _deviceInfo = nullptr;
    }
}

DeviceMTL::~DeviceMTL()
{
    ProgramCache::destroyInstance();
    delete _deviceInfo;
    _deviceInfo = nullptr;
}

CommandBuffer* DeviceMTL::newCommandBuffer()
{
    return new (std::nothrow) CommandBufferMTL(this);
}

Buffer* DeviceMTL::newBuffer(std::size_t size, BufferType type, BufferUsage usage)
{
    return new (std::nothrow) BufferMTL(_mtlDevice, size, type, usage);
}

TextureBackend* DeviceMTL::newTexture(const TextureDescriptor& descriptor)
{
    switch(descriptor.textureType)
    {
        case TextureType::TEXTURE_2D:
            return new (std::nothrow) TextureMTL(_mtlDevice, descriptor);
        case TextureType::TEXTURE_CUBE:
            return new (std::nothrow) TextureCubeMTL(_mtlDevice, descriptor);
        default:
            CCASSERT(false, "invalidate texture type");
            return nullptr;
    }
}

ShaderModule* DeviceMTL::newShaderModule(ShaderStage stage, const std::string& source)
{
    return new (std::nothrow) ShaderModuleMTL(_mtlDevice, stage, source);
}

DepthStencilState* DeviceMTL::createDepthStencilState(const DepthStencilDescriptor& descriptor)
{
    auto ret = new (std::nothrow) DepthStencilStateMTL(_mtlDevice, descriptor);
    if (ret)
        ret->autorelease();
    
    return ret;
}

RenderPipeline* DeviceMTL::newRenderPipeline()
{
    return new (std::nothrow) RenderPipelineMTL(_mtlDevice);
}

Program* DeviceMTL::newProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
    return new (std::nothrow) ProgramMTL(vertexShader, fragmentShader);
}

void DeviceMTL::setFrameBufferOnly(bool frameBufferOnly)
{
    [DeviceMTL::_metalLayer setFramebufferOnly:frameBufferOnly];
}

CC_BACKEND_END
