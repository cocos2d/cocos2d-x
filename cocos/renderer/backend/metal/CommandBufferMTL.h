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
    
    virtual void beginFrame() override;
    virtual void beginRenderPass(const RenderPassDescriptor& descriptor) override;
    virtual void setRenderPipeline(RenderPipeline* renderPipeline) override;
    virtual void setViewport(int x, int y, unsigned int w, unsigned int h) override;
    virtual void setCullMode(CullMode mode) override;
    virtual void setVertexBuffer(unsigned int index, Buffer* buffer) override;
    virtual void setBindGroup(BindGroup* bindGroup) override;
    virtual void setIndexBuffer(Buffer* buffer) override;
    virtual void drawArrays(PrimitiveType primitiveType, unsigned int start,  unsigned int count) override;
    virtual void drawElements(PrimitiveType primitiveType, IndexFormat indexType, unsigned int count, unsigned int offset) override;
    virtual void endRenderPass() override;
    virtual void endFrame() override;
    
    virtual void setLineWidth(float lineWidth) override;
    
    virtual void setScissorRect(bool isEnabled, float x, float y, float width, float height) override;
    
private:
    void prepareDrawing() const;
    void setTextures() const;
    void doSetTextures(const std::vector<std::string>& textures, bool isVertex) const;
    void setUniformBuffer() const;
    unsigned int fillUniformBuffer(uint8_t* buffer, const std::vector<std::string>& uniforms) const;
    void afterDraw();
    
    id<MTLCommandBuffer> _mtlCommandBuffer = nil;
    id<MTLCommandQueue> _mtlCommandQueue = nil;
    id<MTLRenderCommandEncoder> _mtlRenderEncoder = nil;
    id<MTLBuffer> _mtlIndexBuffer = nil;
    
    DeviceMTL* _deviceMTL = nullptr;
    RenderPipelineMTL* _renderPipelineMTL = nullptr;
    BindGroup* _bindGroup = nullptr;
    unsigned int _renderTargetHeight = 0;
    
    dispatch_semaphore_t _frameBoundarySemaphore;
};

CC_BACKEND_END
