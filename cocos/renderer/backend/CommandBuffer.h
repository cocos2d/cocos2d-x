#pragma once

#include "Macros.h"
#include "Types.h"

#include "base/CCRef.h"

#include <cstdint>

CC_BACKEND_BEGIN

class RenderPass;
class RenderPipeline;
class Buffer;
class BindGroup;

class CommandBuffer : public cocos2d::Ref
{
public:
    virtual void beginRenderPass(RenderPass* renderPass) = 0;
    virtual void setRenderPipeline(RenderPipeline* renderPipeline) = 0;
    virtual void setViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h) = 0;
    virtual void setCullMode(CullMode mode) = 0;
    virtual void setVertexBuffer(uint32_t index, Buffer* buffer) = 0;
    virtual void setBindGroup(BindGroup* bindGroup) = 0;
    virtual void setIndexBuffer(Buffer* buffer) = 0;
    virtual void drawArrays(PrimitiveType primitiveType, uint32_t start,  uint32_t count) = 0;
    virtual void drawElements(PrimitiveType primitiveType, IndexFormat indexType, uint32_t count, uint32_t offset) = 0;
    virtual void endRenderPass() = 0;
    
    void setStencilReferenceValue(uint32_t value);
    void setStencilReferenceValue(uint32_t frontRef, uint32_t backRef);
    
protected:
    virtual ~CommandBuffer() = default;
    
    uint32_t _stencilReferenceValueFront = 0;
    uint32_t _stencilReferenceValueBack = 0;
};

CC_BACKEND_END
