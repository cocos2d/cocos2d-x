#pragma once

#include "../CommandBuffer.h"
#include "DeviceMTL.h"

CC_BACKEND_BEGIN

class RenderPipelineMTL;

class CommandBufferMTL : public CommandBuffer
{
public:
    CommandBufferMTL(DeviceMTL* deviceMTL);
    ~CommandBufferMTL();
    
    virtual void beginRenderPass(RenderPass* renderPass) override;
    virtual void setRenderPipeline(RenderPipeline* renderPipeline) override;
    virtual void setViewport(int32_t x, int32_t y, int32_t w, int32_t h) override;
    virtual void setCullMode(CullMode mode) override;
    virtual void setVertexBuffer(uint32_t index, Buffer* buffer) override;
    virtual void setBindGroup(BindGroup* bindGroup) override;
    virtual void setIndexBuffer(Buffer* buffer) override;
    virtual void drawArrays(PrimitiveType primitiveType, uint32_t start,  uint32_t count) override;
    virtual void drawElements(PrimitiveType primitiveType, IndexFormat indexType, uint32_t count, uint32_t offset) override;
    virtual void endRenderPass() override;
    
private:
    void prepareDrawing() const;
    void setTextures() const;
    void doSetTextures(const std::vector<std::string>& textureNames, bool isVertex) const;
    void setUniformBuffer() const;
    uint32_t fillUniformBuffer(uint8_t* buffer, const std::vector<std::string>& uniforms) const;
    void afterDraw();
    
    id<MTLCommandBuffer> _mtlCommandBuffer = nil;
    id<MTLCommandQueue> _mtlCommandQueue = nil;
    id<MTLRenderCommandEncoder> _mtlRenderEncoder = nil;
    id<MTLBuffer> _mtlIndexBuffer = nil;
    
    DeviceMTL* _deviceMTL = nullptr;
    RenderPipelineMTL* _renderPipelineMTL = nullptr;
    BindGroup* _bindGroup = nullptr;
    RenderPass* _renderPass = nullptr; // weak reference
};

CC_BACKEND_END
