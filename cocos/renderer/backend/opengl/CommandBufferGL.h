#pragma once

#include "../Macros.h"
#include "../CommandBuffer.h"

#include "platform/CCGL.h"

#include <vector>

CC_BACKEND_BEGIN

class BufferGL;
class RenderPipelineGL;
class Program;

class CommandBufferGL : public CommandBuffer
{
public:
    CommandBufferGL();
    ~CommandBufferGL();
    
    virtual void beginFrame() override;
    virtual void beginRenderPass(const RenderPassDescriptor& descriptor) override;
    virtual void setRenderPipeline(RenderPipeline* renderPipeline) override;
    virtual void setViewport(ssize_t x, ssize_t y, size_t w, size_t h) override;
    virtual void setCullMode(CullMode mode) override;
    virtual void setVertexBuffer(size_t index, Buffer* buffer) override;
    virtual void setBindGroup(BindGroup* bindGroup) override;
    virtual void setIndexBuffer(Buffer* buffer) override;
    virtual void drawArrays(PrimitiveType primitiveType, uint32_t start,  uint32_t count) override;
    virtual void drawElements(PrimitiveType primitiveType, IndexFormat indexType, uint32_t count, uint32_t offset) override;
    virtual void endRenderPass() override;
    virtual void endFrame() override;
    
    virtual void setLineWidth(float_t lineWidth) override;
    
private:
    struct Viewport
    {
        ssize_t x = 0;
        ssize_t y = 0;
        size_t w = 0;
        size_t h = 0;
    };
    
    void prepareDrawing() const;
    void bindVertexBuffer(Program* program) const;
    void setUniforms(Program* program) const;
    void setUniform(bool isArray, GLuint location, uint32_t size, GLenum uniformType, void* data) const;
    void cleanResources();
    void applyRenderPassDescriptor(const RenderPassDescriptor& descirptor);
    
    struct Viewport _viewport;
    GLint _defaultFBO = 0;
    GLuint _currentFBO = 0;
    std::vector<BufferGL*> _vertexBuffers;
    BindGroup* _bindGroup = nullptr;
    BufferGL* _indexBuffer = nullptr;
    RenderPipelineGL* _renderPipeline = nullptr;
    CullMode _cullMode = CullMode::NONE;
};

CC_BACKEND_END
