#include "DeviceGL.h"
#include "RenderPipelineGL.h"
#include "BufferGL.h"
#include "ShaderModuleGL.h"
#include "CommandBufferGL.h"
#include "TextureGL.h"
#include "DepthStencilStateGL.h"
#include "BlendStateGL.h"

CC_BACKEND_BEGIN

Device* Device::getInstance()
{
    if (!_instance)
        _instance = new (std::nothrow) DeviceGL();
    
    return _instance;
}

CommandBuffer* DeviceGL::newCommandBuffer()
{
    return new (std::nothrow) CommandBufferGL();
}

Buffer* DeviceGL::newBuffer(uint32_t size, BufferType type, BufferUsage usage)
{
    return new (std::nothrow) BufferGL(size, type, usage);
}

Texture* DeviceGL::newTexture(const TextureDescriptor& descriptor)
{
    return new (std::nothrow) TextureGL(descriptor);
}

ShaderModule* DeviceGL::createShaderModule(ShaderStage stage, const std::string& source)
{
    auto ret = new (std::nothrow) ShaderModuleGL(stage, source);
    if (ret)
        ret->autorelease();
    
    return ret;
}

DepthStencilState* DeviceGL::createDepthStencilState(const DepthStencilDescriptor& descriptor)
{
    auto ret = new (std::nothrow) DepthStencilStateGL(descriptor);
    if (ret)
        ret->autorelease();
    
    return ret;
}

BlendState* DeviceGL::createBlendState(const BlendDescriptor& descriptor)
{
    auto ret = new (std::nothrow) BlendStateGL(descriptor);
    if (ret)
        ret->autorelease();
    
    return ret;
}

RenderPipeline* DeviceGL::newRenderPipeline(const RenderPipelineDescriptor& descriptor)
{
    return new (std::nothrow) RenderPipelineGL(descriptor);
}

CC_BACKEND_END
