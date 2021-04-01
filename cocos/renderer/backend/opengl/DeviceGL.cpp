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
 
#include "DeviceGL.h"
#include "RenderPipelineGL.h"
#include "BufferGL.h"
#include "ShaderModuleGL.h"
#include "CommandBufferGL.h"
#include "TextureGL.h"
#include "DepthStencilStateGL.h"
#include "ProgramGL.h"
#include "DeviceInfoGL.h"

CC_BACKEND_BEGIN

Device* Device::getInstance()
{
    if (!_instance)
        _instance = new (std::nothrow) DeviceGL();
    
    return _instance;
}

DeviceGL::DeviceGL()
{
    _deviceInfo = new (std::nothrow) DeviceInfoGL();
    if(!_deviceInfo || _deviceInfo->init() == false)
    {
        delete _deviceInfo;
        _deviceInfo = nullptr;
    }
}

DeviceGL::~DeviceGL()
{
    ProgramCache::destroyInstance();
    delete _deviceInfo;
    _deviceInfo = nullptr;
}

CommandBuffer* DeviceGL::newCommandBuffer()
{
    return new (std::nothrow) CommandBufferGL();
}

Buffer* DeviceGL::newBuffer(std::size_t size, BufferType type, BufferUsage usage)
{
    return new (std::nothrow) BufferGL(size, type, usage);
}

TextureBackend* DeviceGL::newTexture(const TextureDescriptor& descriptor)
{
    switch (descriptor.textureType)
    {
    case TextureType::TEXTURE_2D:
        return new (std::nothrow) Texture2DGL(descriptor);
    case TextureType::TEXTURE_CUBE:
        return new (std::nothrow) TextureCubeGL(descriptor);
    default:
        return nullptr;
    }
}

ShaderModule* DeviceGL::newShaderModule(ShaderStage stage, const std::string& source)
{
    return new (std::nothrow) ShaderModuleGL(stage, source);
}

DepthStencilState* DeviceGL::createDepthStencilState(const DepthStencilDescriptor& descriptor)
{
    auto ret = new (std::nothrow) DepthStencilStateGL(descriptor);
    if (ret)
        ret->autorelease();
    
    return ret;
}

RenderPipeline* DeviceGL::newRenderPipeline()
{
    return new (std::nothrow) RenderPipelineGL();
}

Program* DeviceGL::newProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
    return new (std::nothrow) ProgramGL(vertexShader, fragmentShader);
}

CC_BACKEND_END
