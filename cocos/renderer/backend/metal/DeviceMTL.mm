#include "DeviceMTL.h"
#include "CommandBufferMTL.h"
#include "BufferMTL.h"
#include "RenderPipelineMTL.h"
#include "ShaderModuleMTL.h"
#include "DepthStencilStateMTL.h"
#include "TextureMTL.h"
#include "BlendStateMTL.h"
#include "Utils.h"
#include "ProgramMTL.h"
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
    ProgramCache::getInstance();
}

DeviceMTL::~DeviceMTL()
{
    ProgramCache::destroyInstance();
}

CommandBuffer* DeviceMTL::newCommandBuffer()
{
    return new (std::nothrow) CommandBufferMTL(this);
}

Buffer* DeviceMTL::newBuffer(unsigned int size, BufferType type, BufferUsage usage)
{
    return new (std::nothrow) BufferMTL(_mtlDevice, size, type, usage);
}

Texture* DeviceMTL::newTexture(const TextureDescriptor& descriptor)
{
    switch(descriptor.textureType)
    {
        case TextureType::TEXTURE_2D:
            return new (std::nothrow) TextureMTL(_mtlDevice, descriptor);
        case TextureType::TEXTURE_CUBE:
            //TODO arnold
            CCASSERT(false, "TextureCubMTL is not implemented!");
            return nullptr;
        default:
            CCASSERT(false, "invalidate texture type");
            return nullptr;
    }
}

ShaderModule* DeviceMTL::newShaderModule(ShaderStage stage, const std::string& source)
{
    return new (std::nothrow) ShaderModuleMTL(_mtlDevice, stage, source);;
}

DepthStencilState* DeviceMTL::createDepthStencilState(const DepthStencilDescriptor& descriptor)
{
    auto ret = new (std::nothrow) DepthStencilStateMTL(_mtlDevice, descriptor);
    if (ret)
        ret->autorelease();
    
    return ret;
}

BlendState* DeviceMTL::createBlendState(const BlendDescriptor& descriptor)
{
    auto ret = new (std::nothrow) BlendStateMTL(descriptor);
    if (ret)
        ret->autorelease();
    
    return ret;
}

RenderPipeline* DeviceMTL::newRenderPipeline(const RenderPipelineDescriptor& descriptor)
{
    return new (std::nothrow) RenderPipelineMTL(_mtlDevice, descriptor);
}

Program* DeviceMTL::newProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
    return new (std::nothrow) ProgramMTL(_mtlDevice, vertexShader, fragmentShader);
}

CC_BACKEND_END
