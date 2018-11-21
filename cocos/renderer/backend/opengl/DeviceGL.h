#include "../Device.h"

CC_BACKEND_BEGIN

class DeviceGL : public Device
{
public:
    virtual CommandBuffer* newCommandBuffer() override;
    virtual Buffer* newBuffer(uint32_t size, BufferType type, BufferUsage usage) override;
    virtual RenderPass* newRenderPass(const RenderPassDescriptor& descriptor) override;
    virtual Texture* newTexture(const TextureDescriptor& descriptor) override;
    virtual ShaderModule* createShaderModule(ShaderStage stage, const std::string& source) override;
    virtual DepthStencilState* createDepthStencilState(const DepthStencilDescriptor& descriptor) override;
    virtual BlendState* createBlendState(const BlendDescriptor& descriptor) override;
    virtual RenderPipeline* newRenderPipeline(const RenderPipelineDescriptor& descriptor) override;
};

CC_BACKEND_END
