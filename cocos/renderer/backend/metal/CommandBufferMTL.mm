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
 
#include "CommandBufferMTL.h"
#include "BufferMTL.h"
#include "DeviceMTL.h"
#include "RenderPipelineMTL.h"
#include "TextureMTL.h"
#include "Utils.h"
#include "../Macros.h"
#include "BufferManager.h"
#include "DepthStencilStateMTL.h"

CC_BACKEND_BEGIN

namespace
{
    MTLWinding toMTLWinding(Winding winding)
    {
        if (Winding::CLOCK_WISE == winding)
            return MTLWindingClockwise;
        else
            return MTLWindingCounterClockwise;
    }

    MTLPrimitiveType toMTLPrimitive(PrimitiveType primitiveType)
    {
        MTLPrimitiveType ret = MTLPrimitiveTypeTriangle;
        switch (primitiveType)
        {
            case PrimitiveType::POINT:
                ret = MTLPrimitiveTypePoint;
                break;
            case PrimitiveType::LINE:
                ret = MTLPrimitiveTypeLine;
                break;
            case PrimitiveType::LINE_STRIP:
                ret = MTLPrimitiveTypeLineStrip;
                break;
            case PrimitiveType::TRIANGLE:
                ret = MTLPrimitiveTypeTriangle;
                break;
            case PrimitiveType::TRIANGLE_STRIP:
                ret = MTLPrimitiveTypeTriangleStrip;
                break;
            default:
                break;
        }
        return ret;
    }
    
    MTLIndexType toMTLIndexType(IndexFormat indexFormat)
    {
        if (IndexFormat::U_SHORT == indexFormat)
            return MTLIndexTypeUInt16;
        else
            return MTLIndexTypeUInt32;
    }
    
    MTLCullMode toMTLCullMode(CullMode mode)
    {
        switch (mode) {
            case CullMode::NONE:
                return MTLCullModeNone;
            case CullMode::FRONT:
                return MTLCullModeFront;
            case CullMode::BACK:
                return MTLCullModeBack;
        }
    }
    
    MTLRenderPassDescriptor* toMTLRenderPassDescriptor(const RenderPassDescriptor& descriptor)
    {
        MTLRenderPassDescriptor* mtlDescritpor = [MTLRenderPassDescriptor renderPassDescriptor];
        
        // Set color attachments.
        if (descriptor.needColorAttachment)
        {
            bool hasCustomColorAttachment = false;
            for (int i = 0; i < MAX_COLOR_ATTCHMENT; ++i)
            {
                if (! descriptor.colorAttachmentsTexture[i])
                    continue;
                
                mtlDescritpor.colorAttachments[i].texture = static_cast<TextureMTL*>(descriptor.colorAttachmentsTexture[i])->getMTLTexture();
                if (descriptor.needClearColor)
                {
                    mtlDescritpor.colorAttachments[i].loadAction = MTLLoadActionClear;
                    mtlDescritpor.colorAttachments[i].clearColor = MTLClearColorMake(descriptor.clearColorValue[0],
                                                                                     descriptor.clearColorValue[1],
                                                                                     descriptor.clearColorValue[2],
                                                                                     descriptor.clearColorValue[3]);
                }
                else
                    mtlDescritpor.colorAttachments[i].loadAction = MTLLoadActionLoad;
                
                hasCustomColorAttachment = true;
            }
            
            if (!hasCustomColorAttachment)
            {
                mtlDescritpor.colorAttachments[0].texture = DeviceMTL::getCurrentDrawable().texture;
                if (descriptor.needClearColor)
                {
                    mtlDescritpor.colorAttachments[0].loadAction = MTLLoadActionClear;
                    mtlDescritpor.colorAttachments[0].clearColor = MTLClearColorMake(descriptor.clearColorValue[0],
                                                                                     descriptor.clearColorValue[1],
                                                                                     descriptor.clearColorValue[2],
                                                                                     descriptor.clearColorValue[3]);
                }
                else
                    mtlDescritpor.colorAttachments[0].loadAction = MTLLoadActionLoad;
            }

            mtlDescritpor.colorAttachments[0].storeAction = MTLStoreActionStore;
        }
        
        if(descriptor.needDepthStencilAttachment())
        {
            // Set depth attachment
            {
                if (descriptor.depthAttachmentTexture)
                    mtlDescritpor.depthAttachment.texture = static_cast<TextureMTL*>(descriptor.depthAttachmentTexture)->getMTLTexture();
                else
                    mtlDescritpor.depthAttachment.texture = Utils::getDefaultDepthStencilTexture();
                
                if (descriptor.needClearDepth)
                {
                    mtlDescritpor.depthAttachment.loadAction = MTLLoadActionClear;
                    mtlDescritpor.depthAttachment.clearDepth = descriptor.clearDepthValue;
                }
                else
                    mtlDescritpor.depthAttachment.loadAction = MTLLoadActionLoad;

                mtlDescritpor.depthAttachment.storeAction = MTLStoreActionStore;
            }
            
            // Set stencil attachment
            {
                if (descriptor.stencilAttachmentTexture)
                    mtlDescritpor.stencilAttachment.texture = static_cast<TextureMTL*>(descriptor.stencilAttachmentTexture)->getMTLTexture();
                else
                    mtlDescritpor.stencilAttachment.texture = Utils::getDefaultDepthStencilTexture();
                
                if (descriptor.needClearStencil)
                {
                    mtlDescritpor.stencilAttachment.loadAction = MTLLoadActionClear;
                    mtlDescritpor.stencilAttachment.clearStencil = descriptor.clearStencilValue;
                }
                else
                    mtlDescritpor.stencilAttachment.loadAction = MTLLoadActionLoad;

                mtlDescritpor.stencilAttachment.storeAction = MTLStoreActionStore;
            }
        }
        
        return mtlDescritpor;
    }
    
    id<MTLTexture> getMTLTexture(TextureBackend* texture)
    {
        switch (texture->getTextureType())
        {
            case TextureType::TEXTURE_2D:
                return static_cast<TextureMTL*>(texture)->getMTLTexture();
            case TextureType::TEXTURE_CUBE:
                return static_cast<TextureCubeMTL*>(texture)->getMTLTexture();
            default:
                assert(false);
                return nil;
        }
    }
    
    id<MTLSamplerState> getMTLSamplerState(TextureBackend* texture)
    {
        switch (texture->getTextureType())
        {
            case TextureType::TEXTURE_2D:
                return static_cast<TextureMTL*>(texture)->getMTLSamplerState();
            case TextureType::TEXTURE_CUBE:
                return static_cast<TextureCubeMTL*>(texture)->getMTLSamplerState();
            default:
                assert(false);
                return nil;
        }
    }

    inline int clamp(int value, int min, int max) {
        return std::min(max, std::max(min, value));
    }
}

CommandBufferMTL::CommandBufferMTL(DeviceMTL* deviceMTL)
: _mtlCommandQueue(deviceMTL->getMTLCommandQueue())
, _frameBoundarySemaphore(dispatch_semaphore_create(MAX_INFLIGHT_BUFFER))
{
}

CommandBufferMTL::~CommandBufferMTL()
{
    dispatch_semaphore_signal(_frameBoundarySemaphore);
}

void CommandBufferMTL::beginFrame()
{
    _autoReleasePool = [[NSAutoreleasePool alloc] init];
    dispatch_semaphore_wait(_frameBoundarySemaphore, DISPATCH_TIME_FOREVER);

    _mtlCommandBuffer = [_mtlCommandQueue commandBuffer];
    [_mtlCommandBuffer enqueue];
    [_mtlCommandBuffer retain];

    BufferManager::beginFrame();
}

id<MTLRenderCommandEncoder> CommandBufferMTL::getRenderCommandEncoder(const RenderPassDescriptor& renderPassDescriptor)
{
    if(_mtlRenderEncoder != nil && _prevRenderPassDescriptor == renderPassDescriptor)
    {
        return _mtlRenderEncoder;
    }
    else
    {
        _prevRenderPassDescriptor = renderPassDescriptor;
    }
    
    if(_mtlRenderEncoder != nil)
    {
        [_mtlRenderEncoder endEncoding];
        [_mtlRenderEncoder release];
        _mtlRenderEncoder = nil;
    }

    auto mtlDescriptor = toMTLRenderPassDescriptor(renderPassDescriptor);
    _renderTargetWidth = (unsigned int)mtlDescriptor.colorAttachments[0].texture.width;
    _renderTargetHeight = (unsigned int)mtlDescriptor.colorAttachments[0].texture.height;
    id<MTLRenderCommandEncoder> mtlRenderEncoder = [_mtlCommandBuffer renderCommandEncoderWithDescriptor:mtlDescriptor];
    [mtlRenderEncoder retain];
    
    return mtlRenderEncoder;
}

void CommandBufferMTL::beginRenderPass(const RenderPassDescriptor& descriptor)
{
    _mtlRenderEncoder = getRenderCommandEncoder(descriptor);
//    [_mtlRenderEncoder setFrontFacingWinding:MTLWindingCounterClockwise];
}

void CommandBufferMTL::setRenderPipeline(RenderPipeline* renderPipeline)
{
    CC_SAFE_RETAIN(renderPipeline);
    CC_SAFE_RELEASE(_renderPipelineMTL);
    _renderPipelineMTL = static_cast<RenderPipelineMTL*>(renderPipeline);
    [_mtlRenderEncoder setRenderPipelineState:_renderPipelineMTL->getMTLRenderPipelineState()];
}

void CommandBufferMTL::setViewport(int x, int y, unsigned int w, unsigned int h)
{
    MTLViewport viewport;
    viewport.originX = x;
    viewport.originY = (int)(_renderTargetHeight - y - h);
    viewport.width = w;
    viewport.height = h;
    viewport.znear = -1;
    viewport.zfar = 1;
    [_mtlRenderEncoder setViewport:viewport];
}

void CommandBufferMTL::setCullMode(CullMode mode)
{
    [_mtlRenderEncoder setCullMode:toMTLCullMode(mode)];
}

void CommandBufferMTL::setWinding(Winding winding)
{
    [_mtlRenderEncoder setFrontFacingWinding:toMTLWinding(winding)];
}

void CommandBufferMTL::setVertexBuffer(Buffer* buffer)
{
    // Vertex buffer is bound in index 0.
    [_mtlRenderEncoder setVertexBuffer:static_cast<BufferMTL*>(buffer)->getMTLBuffer()
                                offset:0
                               atIndex:0];
}

void CommandBufferMTL::setProgramState(ProgramState* programState)
{
    CC_SAFE_RETAIN(programState);
    CC_SAFE_RELEASE(_programState);
    _programState = programState;
}

void CommandBufferMTL::setIndexBuffer(Buffer* buffer)
{
    assert(buffer != nullptr);
    if (!buffer)
        return;
    
    _mtlIndexBuffer = static_cast<BufferMTL*>(buffer)->getMTLBuffer();
    [_mtlIndexBuffer retain];
}

void CommandBufferMTL::drawArrays(PrimitiveType primitiveType, std::size_t start,  std::size_t count)
{
    prepareDrawing();
    [_mtlRenderEncoder drawPrimitives:toMTLPrimitive(primitiveType)
                          vertexStart:start
                          vertexCount:count];
}

void CommandBufferMTL::drawElements(PrimitiveType primitiveType, IndexFormat indexType, std::size_t count, std::size_t offset)
{
    prepareDrawing();
    [_mtlRenderEncoder drawIndexedPrimitives:toMTLPrimitive(primitiveType)
                                  indexCount:count
                                   indexType:toMTLIndexType(indexType)
                                 indexBuffer:_mtlIndexBuffer
                           indexBufferOffset:offset];
    
}

void CommandBufferMTL::endRenderPass()
{
    afterDraw();
}

void CommandBufferMTL::captureScreen(std::function<void(const unsigned char*, int, int)> callback)
{
    [_mtlCommandBuffer addCompletedHandler:^(id<MTLCommandBuffer> commandBufferMTL) {
        Utils::getTextureBytes(0, 0, _drawableTexture.width, _drawableTexture.height, _drawableTexture, callback);
        Device::getInstance()->setFrameBufferOnly(true);
    }];
}

void CommandBufferMTL::endFrame()
{
    [_mtlRenderEncoder endEncoding];
    [_mtlRenderEncoder release];
    _mtlRenderEncoder = nil;
    
    [_mtlCommandBuffer presentDrawable:DeviceMTL::getCurrentDrawable()];
    _drawableTexture = DeviceMTL::getCurrentDrawable().texture;
    [_mtlCommandBuffer addCompletedHandler:^(id<MTLCommandBuffer> commandBuffer) {
        // GPU work is complete
        // Signal the semaphore to start the CPU work
        dispatch_semaphore_signal(_frameBoundarySemaphore);
    }];

    [_mtlCommandBuffer commit];
    [_mtlCommandBuffer release];
    DeviceMTL::resetCurrentDrawable();
    [_autoReleasePool drain];
}

void CommandBufferMTL::afterDraw()
{
    if (_mtlIndexBuffer)
    {
        [_mtlIndexBuffer release];
        _mtlIndexBuffer = nullptr;
    }
    
    CC_SAFE_RELEASE_NULL(_programState);
}

void CommandBufferMTL::setDepthStencilState(DepthStencilState* depthStencilState)
{
    if (depthStencilState)
        _mtlDepthStencilState = static_cast<DepthStencilStateMTL*>(depthStencilState)->getMTLDepthStencilState();
    else
        _mtlDepthStencilState = nil;
    
}

void CommandBufferMTL::prepareDrawing() const
{
    setUniformBuffer();
    setTextures();
    
    if (_mtlDepthStencilState)
    {
        [_mtlRenderEncoder setDepthStencilState:_mtlDepthStencilState];
        [_mtlRenderEncoder setStencilFrontReferenceValue:_stencilReferenceValueFront
                                      backReferenceValue:_stencilReferenceValueBack];
    }
}

void CommandBufferMTL::setTextures() const
{
    if (_programState)
    {
        doSetTextures(true);
        doSetTextures(false);
    }
}

void CommandBufferMTL::doSetTextures(bool isVertex) const
{
    const auto& bindTextureInfos = (isVertex) ? _programState->getVertexTextureInfos() : _programState->getFragmentTextureInfos();

    for(const auto& iter : bindTextureInfos)
    {
        //FIXME: should support texture array.
        int i = 0;
        auto location = iter.first;
        const auto& textures = iter.second.textures;
        
        if (isVertex)
        {
            [_mtlRenderEncoder setVertexTexture:getMTLTexture(textures[i])
                                    atIndex:location];
            [_mtlRenderEncoder setVertexSamplerState:getMTLSamplerState(textures[i])
                                         atIndex:location];
        }
        else
        {
            [_mtlRenderEncoder setFragmentTexture:getMTLTexture(textures[i])
                                      atIndex:location];
            [_mtlRenderEncoder setFragmentSamplerState:getMTLSamplerState(textures[i])
                                           atIndex:location];
        }
        
        ++i;
    }
}

void CommandBufferMTL::setUniformBuffer() const
{
    if (_programState)
    {
        auto &callbackUniforms = _programState->getCallbackUniforms();
        
        for(auto &cb : callbackUniforms)
        {
            cb.second(_programState, cb.first);
        }
        
        // Uniform buffer is bound to index 1.
        std::size_t bufferSize = 0;
        char* vertexBuffer = nullptr;
        _programState->getVertexUniformBuffer(&vertexBuffer, bufferSize);
        if(vertexBuffer)
        {
            [_mtlRenderEncoder setVertexBytes:vertexBuffer
                                       length:bufferSize 
                                       atIndex:1];
        }
        
        char* fragmentBuffer = nullptr;
        _programState->getFragmentUniformBuffer(&fragmentBuffer, bufferSize);
        if(fragmentBuffer)
        {
            [_mtlRenderEncoder setFragmentBytes:fragmentBuffer
                                         length:bufferSize
                                        atIndex:1];
        }
    }
}

void CommandBufferMTL::setLineWidth(float lineWidth)
{
}

void CommandBufferMTL::setScissorRect(bool isEnabled, float x, float y, float width, float height)
{
    MTLScissorRect scissorRect;
    if(isEnabled)
    {
        y = _renderTargetHeight - height - y;
        int minX = clamp((int)x, 0, (int)_renderTargetWidth);
        int minY = clamp((int)y, 0, (int)_renderTargetHeight);
        int maxX = clamp((int)(x + width), 0, (int)_renderTargetWidth);
        int maxY = clamp((int)(y + height), 0, (int)_renderTargetHeight);
        scissorRect.x = minX;
        scissorRect.y = minY;
        scissorRect.width = maxX - minX;
        scissorRect.height = maxY - minY;
        if (scissorRect.width == 0 || scissorRect.height == 0) {
            scissorRect.width = 0;
            scissorRect.height = 0;
        }
    }
    else
    {
        scissorRect.x = 0;
        scissorRect.y = 0;
        scissorRect.width = _renderTargetWidth;
        scissorRect.height = _renderTargetHeight;
    }
    [_mtlRenderEncoder setScissorRect:scissorRect];
}


CC_BACKEND_END
