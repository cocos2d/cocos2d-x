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
 
#include "Utils.h"
#include "DeviceMTL.h"
#include "base/CCConfiguration.h"

#define COLOR_ATTAHCMENT_PIXEL_FORMAT MTLPixelFormatBGRA8Unorm

CC_BACKEND_BEGIN

id<MTLTexture> Utils::_defaultColorAttachmentTexture = nil;
id<MTLTexture> Utils::_defaultDepthStencilAttachmentTexture = nil;

namespace {
#define byte(n) ((n) * 8)
#define bit(n) (n)
    
    uint8_t getBitsPerElement(MTLPixelFormat pixleFormat)
    {
        switch (pixleFormat)
        {
            case MTLPixelFormatDepth32Float_Stencil8:
                return byte(8);
            case MTLPixelFormatBGRA8Unorm:
            case MTLPixelFormatRGBA8Unorm:
            case MTLPixelFormatDepth32Float:
                return byte(4);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
            case MTLPixelFormatDepth24Unorm_Stencil8:
                return byte(4);
#else
            case MTLPixelFormatABGR4Unorm:
            case MTLPixelFormatBGR5A1Unorm:
            case MTLPixelFormatB5G6R5Unorm:
            case MTLPixelFormatA1BGR5Unorm:
                return byte(2);
#endif
            case MTLPixelFormatA8Unorm:
            case MTLPixelFormatR8Unorm:
                return byte(1);
            default:
                assert(false);
                break;
        }
        return 0;
    }
    
    MTLPixelFormat getSupportedDepthStencilFormat()
    {
        MTLPixelFormat pixelFormat = MTLPixelFormatDepth32Float_Stencil8;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        bool isDepth24Stencil8PixelFormatSupported = Configuration::getInstance()->supportsOESPackedDepthStencil();
        if(isDepth24Stencil8PixelFormatSupported)
            pixelFormat = MTLPixelFormatDepth24Unorm_Stencil8;
#endif
        return pixelFormat;
    }
}

MTLPixelFormat Utils::getDefaultDepthStencilAttachmentPixelFormat()
{
    return getSupportedDepthStencilFormat();
}

MTLPixelFormat Utils::getDefaultColorAttachmentPixelFormat()
{
    return COLOR_ATTAHCMENT_PIXEL_FORMAT;
}

id<MTLTexture> Utils::getDefaultDepthStencilTexture()
{
    if (! _defaultDepthStencilAttachmentTexture)
        _defaultDepthStencilAttachmentTexture = Utils::createDepthStencilAttachmentTexture();
    
    return _defaultDepthStencilAttachmentTexture;
}

void Utils::updateDefaultColorAttachmentTexture(id<MTLTexture> texture)
{
    Utils::_defaultColorAttachmentTexture = texture;
}

MTLPixelFormat Utils::toMTLPixelFormat(PixelFormat textureFormat)
{
    switch (textureFormat)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        case PixelFormat::MTL_ABGR4:
            return MTLPixelFormatABGR4Unorm;
        case PixelFormat::MTL_BGR5A1:
            return MTLPixelFormatBGR5A1Unorm;
        case PixelFormat::MTL_B5G6R5:
            return MTLPixelFormatB5G6R5Unorm;
        case PixelFormat::PVRTC4A:
            return MTLPixelFormatPVRTC_RGBA_4BPP;
        case PixelFormat::PVRTC4:
            return MTLPixelFormatPVRTC_RGB_4BPP;
        case PixelFormat::PVRTC2A:
            return MTLPixelFormatPVRTC_RGBA_2BPP;
        case PixelFormat::PVRTC2:
            return MTLPixelFormatPVRTC_RGB_2BPP;
        case PixelFormat::ETC:
            return MTLPixelFormatETC2_RGB8;
#else
        case PixelFormat::S3TC_DXT1:
            return MTLPixelFormatBC1_RGBA;
        case PixelFormat::S3TC_DXT3:
            return MTLPixelFormatBC2_RGBA;
        case PixelFormat::S3TC_DXT5:
            return MTLPixelFormatBC3_RGBA;
#endif
        case PixelFormat::RGBA8888:
            return MTLPixelFormatRGBA8Unorm;
            // Should transfer the data to match pixel format when updating data.
        case PixelFormat::RGB888:
            return MTLPixelFormatRGBA8Unorm;
        case PixelFormat::A8:
            return MTLPixelFormatA8Unorm;
        case PixelFormat::BGRA8888:
            return MTLPixelFormatBGRA8Unorm;
           
        //on mac, D24S8 means MTLPixelFormatDepth24Unorm_Stencil8, while on ios it means MTLPixelFormatDepth32Float_Stencil8
        case PixelFormat::D24S8:
            return getSupportedDepthStencilFormat();
        case PixelFormat::DEFAULT:
            return COLOR_ATTAHCMENT_PIXEL_FORMAT;
        case PixelFormat::NONE:
        default:
            return MTLPixelFormatInvalid;
    }
}

void Utils::resizeDefaultAttachmentTexture(std::size_t width, std::size_t height)
{
    [backend::DeviceMTL::getCAMetalLayer() setDrawableSize:CGSizeMake(width, height)];
    [_defaultDepthStencilAttachmentTexture release];
    _defaultDepthStencilAttachmentTexture = Utils::createDepthStencilAttachmentTexture();
}

id<MTLTexture> Utils::createDepthStencilAttachmentTexture()
{
    auto CAMetalLayer = DeviceMTL::getCAMetalLayer();
    MTLTextureDescriptor* textureDescriptor = [[MTLTextureDescriptor alloc] init];
    textureDescriptor.width = CAMetalLayer.drawableSize.width;
    textureDescriptor.height = CAMetalLayer.drawableSize.height;
    textureDescriptor.pixelFormat = getSupportedDepthStencilFormat();
    textureDescriptor.resourceOptions = MTLResourceStorageModePrivate;
    textureDescriptor.usage = MTLTextureUsageRenderTarget;
    auto ret = [CAMetalLayer.device newTextureWithDescriptor:textureDescriptor];
    [textureDescriptor release];
    
    return ret;
}

void Utils::generateMipmaps(id<MTLTexture> texture)
{
    auto commandQueue = static_cast<DeviceMTL*>(DeviceMTL::getInstance())->getMTLCommandQueue();
    auto commandBuffer = [commandQueue commandBuffer];
    id<MTLBlitCommandEncoder> commandEncoder = [commandBuffer blitCommandEncoder];
    [commandEncoder generateMipmapsForTexture:texture];
    [commandEncoder endEncoding];
    [commandBuffer commit];
}

void Utils::swizzleImage(unsigned char *image, std::size_t width, std::size_t height, MTLPixelFormat format)
{
    if(!image)
        return;
    
    auto len = width * height;
    switch (format) {
        //convert to RGBA
        case MTLPixelFormatBGRA8Unorm:
            for(int i=0; i<len; i++)
            {
                unsigned char temp = image[i*4];
                image[i*4] = image[i*4+2];
                image[i*4+2] = temp;
            }
            break;
            
        default:
            break;
    }
}

void Utils::getTextureBytes(std::size_t origX, std::size_t origY, std::size_t rectWidth, std::size_t rectHeight, id<MTLTexture> texture, std::function<void(const unsigned char*, std::size_t, std::size_t)> callback)
{
    NSUInteger texWidth = texture.width;
    NSUInteger texHeight = texture.height;
    MTLRegion region = MTLRegionMake2D(0, 0, texWidth, texHeight);
    MTLRegion imageRegion = MTLRegionMake2D(origX, origY, rectWidth, rectHeight);
    
    MTLTextureDescriptor* textureDescriptor =
    [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:[texture pixelFormat]
                                                       width:texWidth
                                                      height:texHeight
                                                   mipmapped:NO];
    id<MTLDevice> device = static_cast<DeviceMTL*>(DeviceMTL::getInstance())->getMTLDevice();
    id<MTLTexture> copiedTexture = [device newTextureWithDescriptor:textureDescriptor];
    
    id<MTLCommandQueue> commandQueue = static_cast<DeviceMTL*>(DeviceMTL::getInstance())->getMTLCommandQueue();
    auto commandBuffer = [commandQueue commandBuffer];
    [commandBuffer enqueue];
    
    id<MTLBlitCommandEncoder> blitCommandEncoder = [commandBuffer blitCommandEncoder];
    [blitCommandEncoder copyFromTexture:texture sourceSlice:0 sourceLevel:0 sourceOrigin:region.origin sourceSize:region.size toTexture:copiedTexture destinationSlice:0 destinationLevel:0 destinationOrigin:region.origin];
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    [blitCommandEncoder synchronizeResource:copiedTexture];
#endif
    [blitCommandEncoder endEncoding];
   
    [commandBuffer addCompletedHandler:^(id<MTLCommandBuffer> commandBufferMTL) {
        auto bytePerRow = rectWidth * getBitsPerElement(texture.pixelFormat) / 8;
        unsigned char* image = new (std::nothrow) unsigned char[bytePerRow * rectHeight];
        if(image != nullptr)
        {
            [copiedTexture getBytes:image bytesPerRow:bytePerRow fromRegion:imageRegion mipmapLevel:0];
            swizzleImage(image, rectWidth, rectHeight, texture.pixelFormat);
        }
        callback(image, rectWidth, rectHeight);
        CC_SAFE_DELETE_ARRAY(image);
        [copiedTexture release];
    }];
    [commandBuffer commit];
}

CC_BACKEND_END
