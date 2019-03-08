#include "../Device.h"

CC_BACKEND_BEGIN

class DeviceGL : public Device
{
public:
    DeviceGL();
    ~DeviceGL();

    virtual CommandBuffer* newCommandBuffer() override;
    virtual Buffer* newBuffer(unsigned int size, BufferType type, BufferUsage usage) override;
    virtual Texture* newTexture(const TextureDescriptor& descriptor) override;
    virtual DepthStencilState* createDepthStencilState(const DepthStencilDescriptor& descriptor) override;
    virtual BlendState* createBlendState(const BlendDescriptor& descriptor) override;
    virtual RenderPipeline* newRenderPipeline(const RenderPipelineDescriptor& descriptor) override;

protected:
    virtual ShaderModule* newShaderModule(ShaderStage stage, const std::string& source) override;
    virtual Program* newProgram(const std::string& vertexShader, const std::string& fragmentShader) override;

};

CC_BACKEND_END
