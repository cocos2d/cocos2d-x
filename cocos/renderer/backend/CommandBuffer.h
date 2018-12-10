#pragma once

#include <cstdint>

#include "base/CCRef.h"

#include "Macros.h"
#include "Types.h"
#include "RenderPassDescriptor.h"

CC_BACKEND_BEGIN

class RenderPass;
class RenderPipeline;
class Buffer;
class BindGroup;

class CommandBuffer : public cocos2d::Ref
{
public:
    virtual void beginFrame() = 0;
    virtual void beginRenderPass(const RenderPassDescriptor& descriptor) = 0;
    virtual void setRenderPipeline(RenderPipeline* renderPipeline) = 0;
    virtual void setViewport(ssize_t x, ssize_t y, size_t w, size_t h) = 0;
    virtual void setCullMode(CullMode mode) = 0;
    virtual void setVertexBuffer(size_t index, Buffer* buffer) = 0;
    virtual void setBindGroup(BindGroup* bindGroup) = 0;
    virtual void setIndexBuffer(Buffer* buffer) = 0;
    virtual void drawArrays(PrimitiveType primitiveType, uint32_t start,  uint32_t count) = 0;
    virtual void drawElements(PrimitiveType primitiveType, IndexFormat indexType, uint32_t count, uint32_t offset) = 0;
    virtual void endRenderPass() = 0;
    virtual void endFrame() = 0;
    
    void setStencilReferenceValue(uint32_t value);
    void setStencilReferenceValue(uint32_t frontRef, uint32_t backRef);
    
protected:
    virtual ~CommandBuffer() = default;
    
    uint32_t _stencilReferenceValueFront = 0;
    uint32_t _stencilReferenceValueBack = 0;
};

CC_BACKEND_END
