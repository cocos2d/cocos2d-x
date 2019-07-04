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

#include "../Device.h"
#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>

CC_BACKEND_BEGIN

class DeviceMTL : public Device
{
public:
    // TODO: temple solution to get default renderpass descriptor.
    static void setCAMetalLayer(CAMetalLayer* metalLayer);
    // Invoke by engine internally at the beginning of rendering a new frame.
    static void updateDrawable();
    static CAMetalLayer* getCAMetalLayer() { return DeviceMTL::_metalLayer; }
    static id<CAMetalDrawable> getCurrentDrawable();
    static void resetCurrentDrawable();
    
    DeviceMTL();
    ~DeviceMTL();
    
    virtual CommandBuffer* newCommandBuffer() override;
    virtual Buffer* newBuffer(unsigned int size, BufferType type, BufferUsage usage) override;
    virtual TextureBackend* newTexture(const TextureDescriptor& descriptor) override;
    virtual DepthStencilState* createDepthStencilState(const DepthStencilDescriptor& descriptor) override;
    virtual BlendState* createBlendState(const BlendDescriptor& descriptor) override;
    virtual RenderPipeline* newRenderPipeline(const RenderPipelineDescriptor& descriptor) override;
    virtual void setFrameBufferOnly(bool frameBufferOnly) override;

    inline id<MTLDevice> getMTLDevice() const { return _mtlDevice; }
    inline id<MTLCommandQueue> getMTLCommandQueue() const { return _mtlCommandQueue; }
    
protected:
    virtual ShaderModule* newShaderModule(ShaderStage stage, const std::string& source) override;
    virtual Program* newProgram(const std::string& vertexShader, const std::string& fragmentShader) override;
    
private:
    static CAMetalLayer* _metalLayer;
    static id<CAMetalDrawable> _currentDrawable;
    
    id<MTLDevice> _mtlDevice = nil;
    id<MTLCommandQueue> _mtlCommandQueue = nil;
};

CC_BACKEND_END
