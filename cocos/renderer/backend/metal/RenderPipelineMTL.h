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
 
#pragma once

#include "../RenderPipeline.h"
#include "../RenderPipelineDescriptor.h"
#include <string>
#include <vector>
#include <memory>
#import <Metal/Metal.h>

CC_BACKEND_BEGIN
/**
 * @addtogroup _metal
 * @{
 */

/**
 * Create and compile a new MTLRenderPipelineState object synchronously.
 */
class RenderPipelineMTL : public RenderPipeline
{
public:
    /**
     * @param mtlDevice The device for which MTLRenderPipelineState object was created.
     * @param descriptor Specify the render pipeline description.
     */
    RenderPipelineMTL(id<MTLDevice> mtlDevice);
    ~RenderPipelineMTL();
    virtual void update(const PipelineDescriptor&, const RenderPassDescriptor&) override;
    
    /**
     * Get a MTLRenderPipelineState object.
     * @return A MTLRenderPipelineState object.
     */
    inline id<MTLRenderPipelineState> getMTLRenderPipelineState() const { return _mtlRenderPipelineState; }
   
private:
    void setVertexLayout(MTLRenderPipelineDescriptor*, const PipelineDescriptor&);
    void setBlendState(MTLRenderPipelineColorAttachmentDescriptor*, const BlendDescriptor&);
    void setShaderModules(const PipelineDescriptor&);
    void setBlendStateAndFormat(const BlendDescriptor&, const RenderPassDescriptor&);
    void getAttachmentFormat(const RenderPassDescriptor&, PixelFormat&, PixelFormat&, PixelFormat&);
    
    id<MTLRenderPipelineState> _mtlRenderPipelineState = nil;
    id<MTLDevice> _mtlDevice = nil;
   
    MTLRenderPipelineDescriptor* _mtlRenderPipelineDescriptor = nil;
    PixelFormat _colorAttachmentsFormat[MAX_COLOR_ATTCHMENT] = { PixelFormat::DEFAULT };
    PixelFormat _depthAttachmentFormat = PixelFormat::NONE;
    PixelFormat _stencilAttachmentFormat = PixelFormat::NONE;
    NSMutableDictionary* _mtlRenderPipelineStateCache = nil;
};

// end of _metal group
/// @}
CC_BACKEND_END
