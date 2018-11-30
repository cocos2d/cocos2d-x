#include "CommandBufferGL.h"
#include "BufferGL.h"
#include "RenderPipelineGL.h"
#include "RenderPassGL.h"
#include "TextureGL.h"
#include "DepthStencilStateGL.h"
#include "../RenderPass.h"
#include "../BindGroup.h"
#include "Program.h"
#include "BlendStateGL.h"

CC_BACKEND_BEGIN

namespace
{
    GLenum toGLPrimitiveType(PrimitiveType primitiveType)
    {
        GLenum ret = GL_TRIANGLES;
        switch (primitiveType)
        {
            case PrimitiveType::POINT:
                ret = GL_POINTS;
                break;
            case PrimitiveType::LINE:
                ret = GL_LINES;
                break;
            case PrimitiveType::LINE_STRIP:
                ret = GL_LINE_STRIP;
                break;
            case PrimitiveType::TRIANGLE:
                ret = GL_TRIANGLES;
                break;
            case PrimitiveType::TRIANGLE_STRIP:
                ret = GL_TRIANGLE_STRIP;
                break;
            default:
                break;
        }
        return ret;
    }
    
    GLenum toGLIndexType(IndexFormat indexType)
    {
        GLenum ret = GL_BYTE;
        switch (indexType)
        {
            case IndexFormat::U_INT:
                ret = GL_UNSIGNED_INT;
                break;
            case IndexFormat::U_SHORT:
                ret = GL_UNSIGNED_SHORT;
                break;
            default:
                break;
        }
        return ret;
    }
    
    GLenum toGLCullMode(CullMode mode)
    {
        if (CullMode::BACK == mode)
            return GL_BACK;
        else
            return GL_FRONT;
    }
}

CommandBufferGL::CommandBufferGL()
{
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_defaultFBO);
}

CommandBufferGL::~CommandBufferGL()
{
    cleanResources();
}

void CommandBufferGL::beginRenderPass(RenderPass *renderPass)
{
    // use default frame buffer
    if (nullptr == renderPass)
        glBindFramebuffer(GL_FRAMEBUFFER, _defaultFBO);
    else
        static_cast<RenderPassGL*>(renderPass)->apply(_defaultFBO);
}

void CommandBufferGL::setRenderPipeline(RenderPipeline* renderPipeline)
{
    assert(renderPipeline != nullptr);
    if (renderPipeline == nullptr)
        return;
    
    RenderPipelineGL* rp = static_cast<RenderPipelineGL*>(renderPipeline);
    rp->retain();
    CC_SAFE_RELEASE(_renderPipeline);
    _renderPipeline = rp;
}

void CommandBufferGL::setViewport(int32_t x, int32_t y, int32_t w, int32_t h)
{
    _viewport.x = x;
    _viewport.y = y;
    _viewport.w = w;
    _viewport.h = h;
}

void CommandBufferGL::setCullMode(CullMode mode)
{
    _cullMode = mode;
}

void CommandBufferGL::setIndexBuffer(Buffer* buffer)
{
    assert(buffer != nullptr);
    if (buffer == nullptr)
        return;
    
    buffer->retain();
    CC_SAFE_RELEASE(_indexBuffer);
    _indexBuffer = static_cast<BufferGL*>(buffer);
}

void CommandBufferGL::setVertexBuffer(uint32_t index, Buffer* buffer)
{
    assert(buffer != nullptr);
    if (buffer == nullptr)
        return;
    
    buffer->retain();
    
    if (index >= _vertexBuffers.size())
        _vertexBuffers.resize(index + 1);

    CC_SAFE_RELEASE(_vertexBuffers[index]);
    _vertexBuffers[index] = static_cast<BufferGL*>(buffer);
}

void CommandBufferGL::setBindGroup(BindGroup* bindGroup)
{
    CC_SAFE_RETAIN(bindGroup);
    CC_SAFE_RELEASE(_bindGroup);
    _bindGroup = bindGroup;
}

void CommandBufferGL::drawArrays(PrimitiveType primitiveType, uint32_t start,  uint32_t count)
{
    prepareDrawing();
    glDrawArrays(toGLPrimitiveType(primitiveType), start, count);
    
    cleanResources();
}

void CommandBufferGL::drawElements(PrimitiveType primitiveType, IndexFormat indexType, size_t count, size_t offset)
{
    prepareDrawing();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer->getHandler());
    glDrawElements(toGLPrimitiveType(primitiveType), count, toGLIndexType(indexType), (GLvoid*)(uintptr_t)offset);
    
    cleanResources();
}

void CommandBufferGL::endRenderPass()
{
}

void CommandBufferGL::prepareDrawing() const
{
    glViewport(_viewport.x, _viewport.y, _viewport.w, _viewport.h);
    
    const auto& program = _renderPipeline->getProgram();
    glUseProgram(program->getHandler());
    
    bindVertexBuffer(program);
    setUniforms(program);

    // Set depth/stencil state.
    if (_renderPipeline->getDepthStencilState())
        _renderPipeline->getDepthStencilState()->apply(_stencilReferenceValueFront,
                                                       _stencilReferenceValueBack);
    else
        DepthStencilStateGL::reset();
    
    // Set blend state.
    if (_renderPipeline->getBlendState())
        _renderPipeline->getBlendState()->apply();
    else
        BlendStateGL::reset();
    
    // Set cull mode.
    if (CullMode::NONE == _cullMode)
    {
        glDisable(GL_CULL_FACE);
    }
    else
    {
        glEnable(GL_CULL_FACE);
        glCullFace(toGLCullMode(_cullMode));
    }
}

void CommandBufferGL::bindVertexBuffer(Program *program) const
{
    // Bind vertex buffers and set the attributes.
    int i = 0;
    const auto& attributeInfos = program->getAttributeInfos();
    for (const auto& vertexBuffer : _vertexBuffers)
    {
        if (! vertexBuffer)
            continue;
        
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->getHandler());
        
        const auto& attributeInfo = attributeInfos[i];
        for (const auto& attribute : attributeInfo)
        {
            glEnableVertexAttribArray(attribute.location);
            glVertexAttribPointer(attribute.location,
                                  attribute.size,
                                  attribute.type,
                                  attribute.normalized,
                                  attribute.stride,
                                  (GLvoid*)(uintptr_t)attribute.offset);
        }
        
        ++i;
    }
}

void CommandBufferGL::setUniforms(Program* program) const
{
    if (_bindGroup)
    {
        const auto& texutreInfos = _bindGroup->getTextureInfos();
        const auto& bindUniformInfos = _bindGroup->getUniformInfos();
        const auto& activeUniformInfos = program->getUniformInfos();
        for (const auto& activeUinform : activeUniformInfos)
        {
            // Set normal uniforms.
            const auto& bindUniformInfo = bindUniformInfos.find(activeUinform.name);
            if (bindUniformInfos.end() != bindUniformInfo)
            {
                setUniform(activeUinform.isArray,
                           activeUinform.location,
                           activeUinform.size,
                           activeUinform.type,
                           (*bindUniformInfo).second.data);
            }
            
            // Bind textures.
            const auto& bindUniformTextureInfo = texutreInfos.find(activeUinform.name);
            if (texutreInfos.end() != bindUniformTextureInfo)
            {
                const auto& textures = (*bindUniformTextureInfo).second.textures;
                const auto& indices = (*bindUniformTextureInfo).second.indices;
                
                int i = 0;
                for (const auto& texture: textures)
                {
                    static_cast<TextureGL*>(texture)->apply(indices[i]);
                    ++i;
                }
                
                setUniform(activeUinform.isArray,
                           activeUinform.location,
                           activeUinform.size,
                           activeUinform.type,
                           (void*)indices.data());
            }
        }
    }
}

#define DEF_TO_INT(pointer, index)     (*((GLint*)(pointer) + index))
#define DEF_TO_FLOAT(pointer, index)   (*((GLfloat*)(pointer) + index))
void CommandBufferGL::setUniform(bool isArray, GLuint location, uint32_t size, GLenum uniformType, void* data) const
{
    GLsizei count = size;
    switch (uniformType)
    {
        case GL_INT:
        case GL_BOOL:
        case GL_SAMPLER_2D:
        case GL_SAMPLER_CUBE:
            if (isArray)
                glUniform1iv(location, count, (GLint*)data);
            else
                glUniform1i(location, DEF_TO_INT(data, 0));
            break;
        case GL_INT_VEC2:
        case GL_BOOL_VEC2:
            if (isArray)
                glUniform2iv(location, count, (GLint*)data);
            else
                glUniform2i(location, DEF_TO_INT(data, 0), DEF_TO_INT(data, 1));
            break;
        case GL_INT_VEC3:
        case GL_BOOL_VEC3:
            if (isArray)
                glUniform3iv(location, count, (GLint*)data);
            else
                glUniform3i(location,
                            DEF_TO_INT(data, 0),
                            DEF_TO_INT(data, 1),
                            DEF_TO_INT(data, 2));
            break;
        case GL_INT_VEC4:
        case GL_BOOL_VEC4:
            if (isArray)
                glUniform4iv(location, count, (GLint*)data);
            else
                glUniform4i(location,
                            DEF_TO_INT(data, 0),
                            DEF_TO_INT(data, 1),
                            DEF_TO_INT(data, 2),
                            DEF_TO_INT(data, 4));
            break;
        case GL_FLOAT:
            if (isArray)
                glUniform1fv(location, count, (GLfloat*)data);
            else
                glUniform1f(location, DEF_TO_FLOAT(data, 0));
            break;
        case GL_FLOAT_VEC2:
            if (isArray)
                glUniform2fv(location, count, (GLfloat*)data);
            else
                glUniform2f(location, DEF_TO_FLOAT(data, 0), DEF_TO_FLOAT(data, 1));
            break;
        case GL_FLOAT_VEC3:
            if (isArray)
                glUniform3fv(location, count, (GLfloat*)data);
            else
                glUniform3f(location,
                            DEF_TO_FLOAT(data, 0),
                            DEF_TO_FLOAT(data, 1),
                            DEF_TO_FLOAT(data, 2));
            break;
        case GL_FLOAT_VEC4:
            if (isArray)
                glUniform4fv(location, count, (GLfloat*)data);
            else
                glUniform4f(location,
                            DEF_TO_FLOAT(data, 0),
                            DEF_TO_FLOAT(data, 1),
                            DEF_TO_FLOAT(data, 2),
                            DEF_TO_FLOAT(data, 3));
            break;
        case GL_FLOAT_MAT2:
            glUniformMatrix2fv(location, count, GL_FALSE, (GLfloat*)data);
            break;
        case GL_FLOAT_MAT3:
            glUniformMatrix3fv(location, count, GL_FALSE, (GLfloat*)data);
            break;
        case GL_FLOAT_MAT4:
            glUniformMatrix4fv(location, count, GL_FALSE, (GLfloat*)data);
            break;
        break;
        
        default:
        break;
    }
}

void CommandBufferGL::cleanResources()
{
    CC_SAFE_RELEASE_NULL(_indexBuffer);
    CC_SAFE_RELEASE_NULL(_renderPipeline);
    CC_SAFE_RELEASE_NULL(_bindGroup);
      
    for (const auto& vertexBuffer : _vertexBuffers)
        CC_SAFE_RELEASE(vertexBuffer);
    
    _vertexBuffers.clear();
}

CC_BACKEND_END
