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

/**
 * @addtogroup _metal
 * @{
 */

/**
 * Create resources from MTLDevice.
 */
class DeviceMTL : public Device
{
public:
    /**
     * Set CAMetalLayer.
     * @param metalLayer A CAMetalLayer object.
     */
    static void setCAMetalLayer(CAMetalLayer* metalLayer);
    
    /**
     * Invoke by engine internally at the beginning of rendering a new frame.
     */
    static void updateDrawable();
    
    /**
     * Get a CAMetalLayer.
     * @return A CAMetalLayer object.
     */
    static CAMetalLayer* getCAMetalLayer() { return DeviceMTL::_metalLayer; }
    
    /**
     * Get available Drawable.
     * @return an available drawable.
     */
    static id<CAMetalDrawable> getCurrentDrawable();
    
    /**
     * Reset current drawable to nil.
     */
    static void resetCurrentDrawable();
    
    /// @name Constructor, Destructor and Initializers
    DeviceMTL();
    ~DeviceMTL();
    
    /// @name Setters & Getters
    /**
     * New a CommandBuffer object.
     * @return A CommandBuffer object.
     */
    virtual CommandBuffer* newCommandBuffer() override;
    
    /**
     * New a Buffer object.
     * @param size Specifies the size in bytes of the buffer object's new data store.
     * @param type Specifies the target buffer object. The symbolic constant must be BufferType::VERTEX or BufferType::INDEX.
     * @param usage Specifies the expected usage pattern of the data store. The symbolic constant must be BufferUsage::STATIC, BufferUsage::DYNAMIC.
     * @return A Buffer object.
     */
    virtual Buffer* newBuffer(std::size_t size, BufferType type, BufferUsage usage) override;
    
    /**
     * New a TextureBackend object.
     * @param descriptor Specifies texture description.
     * @return A TextureBackend object.
     */
    virtual TextureBackend* newTexture(const TextureDescriptor& descriptor) override;
    
    /**
     * Create a DepthStencilState object.
     * @param descriptor Specifies depth and stencil description.
     * @return An auto release DepthStencilState object.
     */
    virtual DepthStencilState* createDepthStencilState(const DepthStencilDescriptor& descriptor) override;
    
    /**
     * New a RenderPipeline object.
     * @param descriptor Specifies render pipeline description.
     * @return A RenderPipeline object.
     */
    virtual RenderPipeline* newRenderPipeline() override;
    
    /**
     * This property controls whether or not the drawables'
     * MTLTextures may only be used for framebuffer attachments (YES) or
     * whether they may also be used for texture sampling and pixel
     * read/write operations (NO).
     * @param frameBufferOnly A value of YES allows CAMetalLayer to allocate the MTLTexture objects in ways that are optimized for display purposes that makes them unsuitable for sampling. The recommended value for most applications is YES.
     */
    virtual void setFrameBufferOnly(bool frameBufferOnly) override;

    /**
     * New a Program, not auto release.
     * @param vertexShader Specifes this is a vertex shader source.
     * @param fragmentShader Specifes this is a fragment shader source.
     * @return A Program instance.
     */
    virtual Program* newProgram(const std::string& vertexShader, const std::string& fragmentShader) override;

    /**
     * Get a MTLDevice object.
     * @return A MTLDevice object.
     */
    inline id<MTLDevice> getMTLDevice() const { return _mtlDevice; }
    
    /**
     * Get a MTLCommandQueue object.
     * @return A MTLCommandQueue object.
     */
    inline id<MTLCommandQueue> getMTLCommandQueue() const { return _mtlCommandQueue; }
    
protected:
    /**
     * New a shaderModule.
     * @param stage Specifies whether is vertex shader or fragment shader.
     * @param source Specifies shader source.
     * @return A ShaderModule object.
     */
    virtual ShaderModule* newShaderModule(ShaderStage stage, const std::string& source) override;
    
private:
    static CAMetalLayer* _metalLayer;
    static id<CAMetalDrawable> _currentDrawable;
    
    id<MTLDevice> _mtlDevice = nil;
    id<MTLCommandQueue> _mtlCommandQueue = nil;
};

// end of _metal group
/// @}
CC_BACKEND_END
