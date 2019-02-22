#pragma once

#include "../CommandBuffer.h"
#include "DeviceMTL.h"

#include <unordered_map>

CC_BACKEND_BEGIN

class RenderPipelineMTL;

class CommandBufferMTL final : public CommandBuffer
{
public:
    CommandBufferMTL(DeviceMTL* deviceMTL);
    ~CommandBufferMTL();
    
    virtual void beginFrame() override;
    virtual void beginRenderPass(const RenderPassDescriptor& descriptor) override;
    virtual void setRenderPipeline(RenderPipeline* renderPipeline) override;
    virtual void setViewport(int x, int y, unsigned int w, unsigned int h) override;
    virtual void setCullMode(CullMode mode) override;
    virtual void setWinding(Winding winding) override;
    virtual void setVertexBuffer(unsigned int index, Buffer* buffer) override;
    virtual void setProgramState(ProgramState* programState) override;
    virtual void setIndexBuffer(Buffer* buffer) override;
    virtual void drawArrays(PrimitiveType primitiveType, unsigned int start,  unsigned int count) override;
    virtual void drawElements(PrimitiveType primitiveType, IndexFormat indexType, unsigned int count, unsigned int offset) override;
    virtual void endRenderPass() override;
    virtual void endFrame() override;
    
    virtual void setLineWidth(float lineWidth) override;
    virtual void setScissorRect(bool isEnabled, float x, float y, float width, float height) override;
    virtual void setDepthStencilState(DepthStencilState* depthStencilState) override;
    virtual void setCallBackCommand(RenderCommand* comand) override;
    
private:
    void prepareDrawing() const;
    void setTextures() const;
    void doSetTextures(bool isVertex) const;
    void setUniformBuffer() const;
    unsigned int fillUniformBuffer(uint8_t* buffer, const std::vector<UniformBuffer>& unifornInfo) const;
    void afterDraw();
    id<MTLRenderCommandEncoder> getRenderCommandEncoder(const RenderPassDescriptor& renderPassDescriptor);

    NSMutableArray* _commandBufferStack = nil;
    id<MTLCommandBuffer> _mtlCommandBuffer = nil;
    id<MTLCommandQueue> _mtlCommandQueue = nil;
    id<MTLRenderCommandEncoder> _mtlRenderEncoder = nil;
    id<MTLBuffer> _mtlIndexBuffer = nil;
    
    RenderPipelineMTL* _renderPipelineMTL = nullptr;
    ProgramState* _programState = nullptr;
    id<MTLDepthStencilState> _mtlDepthStencilState = nil;
    
    unsigned int _renderTargetHeight = 0;
    
    dispatch_semaphore_t _frameBoundarySemaphore;
    RenderPassDescriptor _prevRenderPassDescriptor;
    
    SynchronizedCallbackCommand* _synchronizedCallback = nullptr;
};

CC_BACKEND_END
