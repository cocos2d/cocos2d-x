#pragma once

#include "Macros.h"
#include "Types.h"
#include "RenderPipelineDescriptor.h"
#include "RenderPassDescriptor.h"
#include "Texture.h"
#include "DepthStencilState.h"
#include "BlendState.h"

#include "base/CCRef.h"

#include <string>

CC_BACKEND_BEGIN

class CommandBuffer;
class Buffer;
class ShaderModule;
class RenderPipeline;
class RenderPass;

class Device : public cocos2d::Ref
{
public:
    static Device* getInstance();
    
    virtual ~Device() = default;
    
    // Create a command buffer, not auto released.
    virtual CommandBuffer* newCommandBuffer() = 0;
    // Create a buffer, not auto released.
    virtual Buffer* newBuffer(uint32_t size, BufferType type, BufferUsage usage) = 0;
    // Create a texture, not auto released.
    virtual Texture* newTexture(const TextureDescriptor& descriptor) = 0;
    // Create a auto released shader module.
    virtual ShaderModule* createShaderModule(ShaderStage stage, const std::string& source) = 0;
    // Create a auto released depth stencil state.
    virtual DepthStencilState* createDepthStencilState(const DepthStencilDescriptor& descriptor) = 0;
    // Create a auto released blend state.
    virtual BlendState* createBlendState(const BlendDescriptor& descriptor) = 0;
    // Create a render pipeline, not auto released.
    virtual RenderPipeline* newRenderPipeline(const RenderPipelineDescriptor& descriptor) = 0;
    
private:
    static Device* _instance;
};

CC_BACKEND_END
