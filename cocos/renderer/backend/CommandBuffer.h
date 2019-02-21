#pragma once

#include <cstdint>

#include "base/CCRef.h"

#include "Macros.h"
#include "Types.h"
#include "RenderPassDescriptor.h"
#include "CCStdC.h"
#include "ProgramState.h"

CC_BACKEND_BEGIN

class RenderPass;
class RenderPipeline;
class Buffer;
class DepthStencilState;

class CommandBuffer : public cocos2d::Ref
{
public:
    virtual void pushCommandBuffer() = 0;
    virtual void popCommandBuffer() = 0;
    virtual void beginFrame() = 0;
    virtual void beginRenderPass(const RenderPassDescriptor& descriptor) = 0;
    virtual void setRenderPipeline(RenderPipeline* renderPipeline) = 0;
    virtual void setViewport(int x, int y, unsigned int w, unsigned int h) = 0;
    virtual void setCullMode(CullMode mode) = 0;
    virtual void setWinding(Winding winding) = 0;
    virtual void setVertexBuffer(unsigned int index, Buffer* buffer) = 0;
    virtual void setProgramState(ProgramState* programState) = 0;
    virtual void setIndexBuffer(Buffer* buffer) = 0;
    virtual void drawArrays(PrimitiveType primitiveType, unsigned int start,  unsigned int count) = 0;
    virtual void drawElements(PrimitiveType primitiveType, IndexFormat indexType, unsigned int count, unsigned int offset) = 0;
    virtual void endRenderPass() = 0;
    virtual void endFrame() = 0;
    
    virtual void setLineWidth(float lineWidth) = 0;
    virtual void setScissorRect(bool isEnabled, float x, float y, float width, float height) = 0;
    virtual void setDepthStencilState(DepthStencilState* depthStencilState) = 0;
    
    void setStencilReferenceValue(unsigned int value);
    void setStencilReferenceValue(unsigned int frontRef, unsigned int backRef);
    
protected:
    virtual ~CommandBuffer() = default;
    
    unsigned int _stencilReferenceValueFront = 0;
    unsigned int _stencilReferenceValueBack = 0;
};

CC_BACKEND_END
