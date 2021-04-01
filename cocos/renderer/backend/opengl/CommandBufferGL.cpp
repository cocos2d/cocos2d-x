/****************************************************************************
 Copyright (c) 2018-2019 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
 
#include "CommandBufferGL.h"
#include "BufferGL.h"
#include "RenderPipelineGL.h"
#include "TextureGL.h"
#include "DepthStencilStateGL.h"
#include "ProgramGL.h"
#include "base/ccMacros.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventType.h"
#include "base/CCDirector.h"
#include "renderer/backend/opengl/UtilsGL.h"
#include <algorithm>

CC_BACKEND_BEGIN

namespace
{

    GLuint getHandler(TextureBackend *texture)
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

    void applyTexture(TextureBackend* texture, int slot)
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

#if CC_ENABLE_CACHE_TEXTURE_DATA
    _backToForegroundListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom*){
       if(_generatedFBO)
           glGenFramebuffers(1, &_generatedFBO); //recreate framebuffer
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backToForegroundListener, -1);
#endif
}

CommandBufferGL::~CommandBufferGL()
{
    glDeleteFramebuffers(1, &_generatedFBO);
    CC_SAFE_RELEASE_NULL(_renderPipeline);

    cleanResources();

#if CC_ENABLE_CACHE_TEXTURE_DATA
    Director::getInstance()->getEventDispatcher()->removeEventListener(_backToForegroundListener);
#endif
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
    bool useDepthAttachmentExternal = descirptor.depthTestEnabled && descirptor.depthAttachmentTexture;
    bool useStencilAttachmentExternal = descirptor.stencilTestEnabled && descirptor.stencilAttachmentTexture;
    bool useGeneratedFBO = false;
    if (useColorAttachmentExternal || useDepthAttachmentExternal || useStencilAttachmentExternal)
    {
        if(_generatedFBO == 0)
        {
            glGenFramebuffers(1, &_generatedFBO);
        }
        _currentFBO = _generatedFBO;
        useGeneratedFBO = true;
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

        _generatedFBOBindDepth = true;
    }
    else
    {
        if (_generatedFBOBindDepth && useGeneratedFBO)
        {
            glFramebufferTexture2D(GL_FRAMEBUFFER,
                                   GL_DEPTH_ATTACHMENT,
                                   GL_TEXTURE_2D,
                                   0,
                                   0);
            CHECK_GL_ERROR_DEBUG();

            _generatedFBOBindDepth = false;
        }
    }
        
    if (useStencilAttachmentExternal)
    {
        glFramebufferTexture2D(GL_FRAMEBUFFER,
                               GL_STENCIL_ATTACHMENT,
                               GL_TEXTURE_2D,
                               getHandler(descirptor.depthAttachmentTexture),
                               0);
        CHECK_GL_ERROR_DEBUG();

        _generatedFBOBindStencil = true;
    }
    else
    {
        if (_generatedFBOBindStencil && useGeneratedFBO)
        {
            glFramebufferTexture2D(GL_FRAMEBUFFER,
                                   GL_STENCIL_ATTACHMENT,
                                   GL_TEXTURE_2D,
                                   0,
                                   0);
            CHECK_GL_ERROR_DEBUG();

            _generatedFBOBindStencil = false;
        }
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

        if (useGeneratedFBO)
            _generatedFBOBindColor = true;

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
        if (_framebufferReadWriteDisabled)
        {
            if (useGeneratedFBO) //user-defined framebuffer
            {
                glDrawBuffer(GL_COLOR_ATTACHMENT0);
                glReadBuffer(GL_COLOR_ATTACHMENT0);
            } 
            else //default framebuffer
            {
                glDrawBuffer(GL_BACK);
                glReadBuffer(GL_BACK);
            }
            _framebufferReadWriteDisabled = false;
        }
#endif
    }
    else
    {
        if (_generatedFBOBindColor && useGeneratedFBO)
        {
           // FIXME: Now only support attaching to attachment 0.
           glFramebufferTexture2D(GL_FRAMEBUFFER,
                                  GL_COLOR_ATTACHMENT0,
                                  GL_TEXTURE_2D,
                                  0,
                                  0);

            _generatedFBOBindColor = false;
        }

        // If not draw buffer is needed, should invoke this line explicitly, or it will cause
        // GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER and GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER error.
        // https://stackoverflow.com/questions/28313782/porting-opengl-es-framebuffer-to-opengl
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        _framebufferReadWriteDisabled = true;
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
    _viewPort.x = x;
    _viewPort.y = y;
    _viewPort.w = w;
    _viewPort.h = h;
}

void CommandBufferGL::setCullMode(CullMode mode)
{
    _cullMode = mode;
}

void CommandBufferGL::setWinding(Winding winding)
{
    glFrontFace(UtilsGL::toGLFrontFace(winding));
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

void CommandBufferGL::setVertexBuffer(Buffer* buffer)
{
    assert(buffer != nullptr);
    if (buffer == nullptr || _vertexBuffer == buffer)
        return;
    
    buffer->retain();
    _vertexBuffer = static_cast<BufferGL*>(buffer);
}

void CommandBufferGL::setProgramState(ProgramState* programState)
{
    CC_SAFE_RETAIN(programState);
    CC_SAFE_RELEASE(_programState);
    _programState = programState;
}

void CommandBufferGL::drawArrays(PrimitiveType primitiveType, std::size_t start,  std::size_t count)
{
    prepareDrawing();
    glDrawArrays(UtilsGL::toGLPrimitiveType(primitiveType), start, count);
    
    cleanResources();
}

void CommandBufferGL::drawElements(PrimitiveType primitiveType, IndexFormat indexType, std::size_t count, std::size_t offset)
{
    prepareDrawing();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer->getHandler());
    glDrawElements(UtilsGL::toGLPrimitiveType(primitiveType), count, UtilsGL::toGLIndexType(indexType), (GLvoid*)offset);
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
    
    // Set cull mode.
    if (CullMode::NONE == _cullMode)
    {
        glDisable(GL_CULL_FACE);
    }
    else
    {
        glEnable(GL_CULL_FACE);
        glCullFace(UtilsGL::toGLCullMode(_cullMode));
    }
}

void CommandBufferGL::bindVertexBuffer(ProgramGL *program) const
{
    // Bind vertex buffers and set the attributes.
    auto vertexLayout = _programState->getVertexLayout();
    
    if (!vertexLayout->isValid())
        return;
    
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer->getHandler());

    const auto& attributes = vertexLayout->getAttributes();
    for (const auto& attributeInfo : attributes)
    {
        const auto& attribute = attributeInfo.second;
        glEnableVertexAttribArray(attribute.index);
        glVertexAttribPointer(attribute.index,
            UtilsGL::getGLAttributeSize(attribute.format),
            UtilsGL::toGLAttributeType(attribute.format),
            attribute.needToBeNormallized,
            vertexLayout->getStride(),
            (GLvoid*)attribute.offset);
    }
}

void CommandBufferGL::setUniforms(ProgramGL* program) const
{
    if (_programState)
    {
        auto& callbacks = _programState->getCallbackUniforms();
        auto& uniformInfos = _programState->getProgram()->getAllActiveUniformInfo(ShaderStage::VERTEX);
        std::size_t bufferSize = 0;
        char* buffer = nullptr;
        _programState->getVertexUniformBuffer(&buffer, bufferSize);

        for (auto &cb : callbacks)
        {
            cb.second(_programState, cb.first);
        }

        int i = 0;
        for(auto& iter : uniformInfos)
        {
            auto& uniformInfo = iter.second;
            if(uniformInfo.size <= 0)
                continue;

            int elementCount = uniformInfo.count;
            setUniform(uniformInfo.isArray,
                uniformInfo.location,
                elementCount,
                uniformInfo.type,
                (void*)(buffer + uniformInfo.bufferOffset));
        }
        
        const auto& textureInfo = _programState->getVertexTextureInfos();
        for(const auto& iter : textureInfo)
        {
            const auto& textures = iter.second.textures;
            const auto& slot = iter.second.slot;
            auto location = iter.first;
#if CC_ENABLE_CACHE_TEXTURE_DATA
            location = iter.second.location;
#endif
            int i = 0;
            for (const auto& texture: textures)
            {
                applyTexture(texture, slot[i]);
                ++i;
            }
            
            auto arrayCount = slot.size();
            if (arrayCount > 1)
                glUniform1iv(location, (uint32_t)arrayCount, (GLint*)slot.data());
            else
                glUniform1i(location, slot[0]);
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
    CC_SAFE_RELEASE_NULL(_programState);  
    CC_SAFE_RELEASE_NULL(_vertexBuffer);
}

void CommandBufferGL::setLineWidth(float lineWidth)
{
    if(lineWidth > 0.0f)
        glLineWidth(lineWidth);
    else
        glLineWidth(1.0f);
    
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

void CommandBufferGL::captureScreen(std::function<void(const unsigned char*, int, int)> callback)
{
    int bufferSize = _viewPort.w * _viewPort.h *4;
    std::shared_ptr<GLubyte> buffer(new GLubyte[bufferSize], [](GLubyte* p){ CC_SAFE_DELETE_ARRAY(p); });
    memset(buffer.get(), 0, bufferSize);
    if (!buffer)
    {
        callback(nullptr, 0, 0);
        return;
    }
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadPixels(0, 0, _viewPort.w, _viewPort.h, GL_RGBA, GL_UNSIGNED_BYTE, buffer.get());

    std::shared_ptr<GLubyte> flippedBuffer(new GLubyte[bufferSize], [](GLubyte* p) { CC_SAFE_DELETE_ARRAY(p); });
    memset(flippedBuffer.get(), 0, bufferSize);
    if (!flippedBuffer)
    {
        callback(nullptr, 0, 0);
        return;
    }
    for (int row = 0; row < _viewPort.h; ++row)
    {
        memcpy(flippedBuffer.get() + (_viewPort.h - row - 1) * _viewPort.w * 4, buffer.get() + row * _viewPort.w * 4, _viewPort.w * 4);
    }

    callback(flippedBuffer.get(), _viewPort.w, _viewPort.h);
}

CC_BACKEND_END
