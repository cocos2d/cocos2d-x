#include "CommandBufferGL.h"
#include "BufferGL.h"
#include "RenderPipelineGL.h"
#include "TextureGL.h"
#include "DepthStencilStateGL.h"
#include "ProgramGL.h"
#include "BlendStateGL.h"
#include "base/ccMacros.h"

#include <algorithm>

CC_BACKEND_BEGIN

namespace
{
    GLenum toGLFrontFace(Winding winding)
    {
        if (Winding::CLOCK_WISE == winding)
            return GL_CW;
        else
            return GL_CCW;
    }

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

    GLuint getHandler(Texture *texture)
    {
        switch (texture->getTextureType())
        {
        case TextureType::TEXTURE_2D:
            return static_cast<Texture2DGL*>(texture)->getHandler();
        case TextureType::TEXTURE_CUBE:
            return static_cast<TextureCubeGL*>(texture)->getHandler();
        default:
            assert(false);
            return 0;
        }
    }

    void applyTexture(Texture* texture, int slot)
    {
        switch (texture->getTextureType())
        {
        case TextureType::TEXTURE_2D:
            static_cast<Texture2DGL*>(texture)->apply(slot);
            break;
        case TextureType::TEXTURE_CUBE:
            static_cast<TextureCubeGL*>(texture)->apply(slot);
            break;
        default:
            assert(false);
            return ;
        }
    }
}

CommandBufferGL::CommandBufferGL()
{
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_defaultFBO);
}

CommandBufferGL::~CommandBufferGL()
{
    glDeleteFramebuffers(1, &_frameBuffer);
    cleanResources();
}

void CommandBufferGL::beginFrame()
{
}

void CommandBufferGL::beginRenderPass(const RenderPassDescriptor& descirptor)
{
    applyRenderPassDescriptor(descirptor);
}

void CommandBufferGL::applyRenderPassDescriptor(const RenderPassDescriptor& descirptor)
{
    bool useColorAttachmentExternal = descirptor.needColorAttachment && descirptor.colorAttachmentsTexture[0];
    bool useDepthAttachmentExternal = descirptor.needDepthAttachment && descirptor.depthAttachmentTexture;
    bool useStencilAttachmentExternal = descirptor.needStencilAttachment && descirptor.stencilAttachmentTexture;
    if (useColorAttachmentExternal || useDepthAttachmentExternal || useStencilAttachmentExternal)
    {
        if(_frameBuffer == 0)
        {
            glGenFramebuffers(1, &_frameBuffer);
        }
        _currentFBO = _frameBuffer;
    }
    else
    {
        _currentFBO = _defaultFBO;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, _currentFBO);
    
    if (useDepthAttachmentExternal)
    {
        glFramebufferTexture2D(GL_FRAMEBUFFER,
                               GL_DEPTH_ATTACHMENT,
                               GL_TEXTURE_2D,
                               getHandler(descirptor.depthAttachmentTexture),
                               0);
        CHECK_GL_ERROR_DEBUG();
    }
        
    if (useStencilAttachmentExternal)
    {
        glFramebufferTexture2D(GL_FRAMEBUFFER,
                               GL_STENCIL_ATTACHMENT,
                               GL_TEXTURE_2D,
                               getHandler(descirptor.depthAttachmentTexture),
                               0);
        CHECK_GL_ERROR_DEBUG();
    }
    
    if (descirptor.needColorAttachment)
    {
        int i = 0;
        for (const auto& texture : descirptor.colorAttachmentsTexture)
        {
            if (texture)
            {
                // TODO: support texture cube
                glFramebufferTexture2D(GL_FRAMEBUFFER,
                                       GL_COLOR_ATTACHMENT0 + i,
                                       GL_TEXTURE_2D,
                                       getHandler(texture),
                                       0);
            }
            CHECK_GL_ERROR_DEBUG();
            ++i;
        }
    }
    else
    {
        // If not draw buffer is needed, should invoke this line explicitly, or it will cause
        // GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER and GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER error.
        // https://stackoverflow.com/questions/28313782/porting-opengl-es-framebuffer-to-opengl
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
#endif
    }
    CHECK_GL_ERROR_DEBUG();
    
    // set clear color, depth and stencil
    GLbitfield mask = 0;
    if (descirptor.needClearColor)
    {
        mask |= GL_COLOR_BUFFER_BIT;
        const auto& clearColor = descirptor.clearColorValue;
        glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
    }
    
    CHECK_GL_ERROR_DEBUG();
    
    GLboolean oldDepthWrite = GL_FALSE;
    GLboolean oldDepthTest = GL_FALSE;
    GLfloat oldDepthClearValue = 0.f;
    GLint oldDepthFunc = GL_LESS;
    if (descirptor.needClearDepth)
    {
        glGetBooleanv(GL_DEPTH_WRITEMASK, &oldDepthWrite);
        glGetBooleanv(GL_DEPTH_TEST, &oldDepthTest);
        glGetFloatv(GL_DEPTH_CLEAR_VALUE, &oldDepthClearValue);
        glGetIntegerv(GL_DEPTH_FUNC, &oldDepthFunc);
        
        mask |= GL_DEPTH_BUFFER_BIT;
        glClearDepth(descirptor.clearDepthValue);
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_ALWAYS);
    }
    
    CHECK_GL_ERROR_DEBUG();
    
    if (descirptor.needClearStencil)
    {
        mask |= GL_STENCIL_BUFFER_BIT;
        glClearStencil(descirptor.clearStencilValue);
    }
    
    if(mask) glClear(mask);
    
    CHECK_GL_ERROR_DEBUG();
    
    // restore depth test
    if (descirptor.needClearDepth)
    {
        if (!oldDepthTest)
            glDisable(GL_DEPTH_TEST);
        
        glDepthMask(oldDepthWrite);
        glDepthFunc(oldDepthFunc);
        glClearDepth(oldDepthClearValue);
    }
    
    CHECK_GL_ERROR_DEBUG();
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

void CommandBufferGL::setViewport(int x, int y, unsigned int w, unsigned int h)
{
    glViewport(x, y, w, h);
}

void CommandBufferGL::setCullMode(CullMode mode)
{
    _cullMode = mode;
}

void CommandBufferGL::setWinding(Winding winding)
{
    glFrontFace(toGLFrontFace(winding));
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

void CommandBufferGL::setVertexBuffer(unsigned int index, Buffer* buffer)
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

void CommandBufferGL::setProgramState(ProgramState* programState)
{
    CC_SAFE_RETAIN(programState);
    CC_SAFE_RELEASE(_programState);
    _programState = programState;
}

void CommandBufferGL::drawArrays(PrimitiveType primitiveType, unsigned int start,  unsigned int count)
{
    prepareDrawing();
    glDrawArrays(toGLPrimitiveType(primitiveType), start, count);
    
    cleanResources();
}

void CommandBufferGL::drawElements(PrimitiveType primitiveType, IndexFormat indexType, unsigned int count, unsigned int offset)
{
    prepareDrawing();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer->getHandler());
    glDrawElements(toGLPrimitiveType(primitiveType), count, toGLIndexType(indexType), (GLvoid*)offset);
    CHECK_GL_ERROR_DEBUG();
    cleanResources();
}

void CommandBufferGL::endRenderPass()
{
}

void CommandBufferGL::endFrame()
{
}

void CommandBufferGL::setDepthStencilState(DepthStencilState* depthStencilState)	
{	
    if (depthStencilState)	
    {	
        _depthStencilStateGL = static_cast<DepthStencilStateGL*>(depthStencilState);	
    }	
    else	
    {	
        _depthStencilStateGL = nullptr;	
    }	
}

void CommandBufferGL::prepareDrawing() const
{   
    const auto& program = _renderPipeline->getProgram();
    glUseProgram(program->getHandler());
    
    bindVertexBuffer(program);
    setUniforms(program);

    // Set depth/stencil state.
    if (_depthStencilStateGL)
    {
        _depthStencilStateGL->apply(_stencilReferenceValueFront, _stencilReferenceValueBack);
    }
        
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

void CommandBufferGL::bindVertexBuffer(ProgramGL *program) const
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
                                  attribute.needToBeNormallized,
                                  attribute.stride,
                                  (GLvoid*)attribute.offset);
        }
        
        ++i;
    }
}

void CommandBufferGL::setUniforms(ProgramGL* program) const
{
    if (_programState)
    {
        auto& uniformInfos = _programState->getVertexUniformInfos();
        int i = 0;
        for(auto& iter : uniformInfos)
        {
            auto& uniformInfo = iter.uniformInfo;
            if(uniformInfo.bufferSize <= 0)
                continue;

            int elementCount = uniformInfo.count;
            if (uniformInfo.isArray)
            {
                CCASSERT(uniformInfo.count * uniformInfo.bufferSize >= iter.data.size(), "uniform data size mismatch!");
                //iter.data.reserve(uniformInfo.count * uniformInfo.bufferSize);
                elementCount = std::min(elementCount, (int)(iter.data.size() / uniformInfo.bufferSize));
            }

            setUniform(uniformInfo.isArray,
                uniformInfo.location,
                elementCount,
                uniformInfo.type,
                (void*)iter.data.data());
        }
        
        const auto& textureInfo = _programState->getVertexTextureInfos();
        for(const auto& iter : textureInfo)
        {
            const auto& textures = iter.second.textures;
            const auto& slot = iter.second.slot;
            
            int i = 0;
            for (const auto& texture: textures)
            {
                applyTexture(texture, slot[i]);
                ++i;
            }
            
            auto arrayCount = slot.size();
            if (arrayCount > 1)
                glUniform1iv(iter.first, (uint32_t)arrayCount, (GLint*)slot.data());
            else
                glUniform1i(iter.first, slot[0]);
        }
    }
}

#define DEF_TO_INT(pointer, index)     (*((GLint*)(pointer) + index))
#define DEF_TO_FLOAT(pointer, index)   (*((GLfloat*)(pointer) + index))
void CommandBufferGL::setUniform(bool isArray, GLuint location, unsigned int size, GLenum uniformType, void* data) const
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
            CCASSERT(false, "invalidate Uniform data type");
        break;
    }
}

void CommandBufferGL::cleanResources()
{
    CC_SAFE_RELEASE_NULL(_indexBuffer);
    CC_SAFE_RELEASE_NULL(_renderPipeline);
    CC_SAFE_RELEASE_NULL(_programState);
      
    for (const auto& vertexBuffer : _vertexBuffers)
        CC_SAFE_RELEASE(vertexBuffer);
    
    _vertexBuffers.clear();
}

void CommandBufferGL::setLineWidth(float lineWidth)
{
    if(lineWidth > 0.0f)
        glLineWidth(lineWidth);
}


void CommandBufferGL::setScissorRect(bool isEnabled, float x, float y, float width, float height)
{
    if(isEnabled)
    {
        glEnable(GL_SCISSOR_TEST);
        glScissor(x, y, width, height);
    }
    else
    {
        glDisable(GL_SCISSOR_TEST);
    }
}

CC_BACKEND_END
