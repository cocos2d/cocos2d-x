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
    
    virtual void beginRenderPass(RenderPass* renderPass) override;
    virtual void setRenderPipeline(RenderPipeline* renderPipeline) override;
    virtual void setViewport(int32_t x, int32_t y, int32_t w, int32_t h) override;
    virtual void setCullMode(CullMode mode) override;
    virtual void setVertexBuffer(uint32_t index, Buffer* buffer) override;
    virtual void setBindGroup(BindGroup* bindGroup) override;
    virtual void setIndexBuffer(Buffer* buffer) override;
    virtual void drawArrays(PrimitiveType primitiveType, uint32_t start,  uint32_t count) override;
    virtual void drawElements(PrimitiveType primitiveType, IndexFormat indexType, size_t count, size_t offset) override;
    virtual void endRenderPass() override;
    
private:
    struct Viewport
    {
        GLint x = 0;
        GLint y = 0;
        GLint w = 0;
        GLint h = 0;
    };
    
    void prepareDrawing() const;
    void bindVertexBuffer(Program* program) const;
    void setUniforms(Program* program) const;
    void setUniform(bool isArray, GLuint location, uint32_t size, GLenum uniformType, void* data) const;
    void cleanResources();
    
    struct Viewport _viewport;
    GLint _defaultFBO = 0;
    std::vector<BufferGL*> _vertexBuffers;
    BindGroup* _bindGroup = nullptr;
    BufferGL* _indexBuffer = nullptr;
    RenderPipelineGL* _renderPipeline = nullptr;
    CullMode _cullMode = CullMode::NONE;
};

CC_BACKEND_END
