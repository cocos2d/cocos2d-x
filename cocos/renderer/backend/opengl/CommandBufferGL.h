#pragma once

#include "../Macros.h"
#include "../CommandBuffer.h"

#include "platform/CCGL.h"

#include "CCStdC.h"

#include <vector>

CC_BACKEND_BEGIN

class BufferGL;
class RenderPipelineGL;
class ProgramGL;
class DepthStencilStateGL;

class CommandBufferGL final : public CommandBuffer
{
public:
    CommandBufferGL();
    ~CommandBufferGL();
    
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

    
private:
    struct Viewport
    {
        int x = 0;
        int y = 0;
        unsigned int w = 0;
        unsigned int h = 0;
    };
    
    void prepareDrawing() const;
    void bindVertexBuffer(ProgramGL* program) const;
    void setUniforms(ProgramGL* program) const;
    void setUniform(bool isArray, GLuint location, unsigned int size, GLenum uniformType, void* data) const;
    void cleanResources();
    void applyRenderPassDescriptor(const RenderPassDescriptor& descirptor);

    GLuint _frameBuffer = 0;
    GLint _defaultFBO = 0;
    GLuint _currentFBO = 0;
    std::vector<BufferGL*> _vertexBuffers;
    ProgramState* _programState = nullptr;
    BufferGL* _indexBuffer = nullptr;
    RenderPipelineGL* _renderPipeline = nullptr;
    CullMode _cullMode = CullMode::NONE;
    DepthStencilStateGL* _depthStencilStateGL = nullptr;
};

CC_BACKEND_END
