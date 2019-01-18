#include "Utils.h"
#include "DeviceMTL.h"

#define COLOR_ATTAHCMENT_PIXEL_FORMAT MTLPixelFormatBGRA8Unorm
#define DEPTH_STENCIL_ATTACHMENT_PIXEL_FORMAT MTLPixelFormatDepth32Float_Stencil8

CC_BACKEND_BEGIN

id<MTLTexture> Utils::_defaultColorAttachmentTexture = nil;
id<MTLTexture> Utils::_defaultDepthStencilAttachmentTexture = nil;

MTLPixelFormat Utils::getDefaultDepthStencilAttachmentPixelFormat()
{
    return DEPTH_STENCIL_ATTACHMENT_PIXEL_FORMAT;
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

MTLPixelFormat Utils::toMTLPixelFormat(TextureFormat textureFormat)
{
    switch (textureFormat)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        case TextureFormat::MTL_ABGR4:
            return MTLPixelFormatABGR4Unorm;
        case TextureFormat::MTL_BGR5A1:
            return MTLPixelFormatBGR5A1Unorm;
        case TextureFormat::MTL_B5G6R5:
            return MTLPixelFormatB5G6R5Unorm;
        case TextureFormat::PVRTC4A:
            return MTLPixelFormatPVRTC_RGBA_4BPP;
        case TextureFormat::PVRTC4:
            return MTLPixelFormatPVRTC_RGB_4BPP;
        case TextureFormat::PVRTC2A:
            return MTLPixelFormatPVRTC_RGBA_2BPP;
        case TextureFormat::PVRTC2:
            return MTLPixelFormatPVRTC_RGB_2BPP;
#endif
        case TextureFormat::R8G8B8A8:
            return MTLPixelFormatRGBA8Unorm;
            // Should transfer the data to match pixel format when updating data.
        case TextureFormat::R8G8B8:
            return MTLPixelFormatRGBA8Unorm;
        case TextureFormat::A8:
            return MTLPixelFormatA8Unorm;
            // Not all devices supports MTLPixelFormatDepth24Unorm_Stencil8, so change to MTLPixelFormatDepth32Float_Stencil8.
        case TextureFormat::D24S8:
            return MTLPixelFormatDepth32Float_Stencil8;
        case TextureFormat::SYSTEM_DEFAULT:
            return COLOR_ATTAHCMENT_PIXEL_FORMAT;
        case TextureFormat::NONE:
        default:
            return MTLPixelFormatInvalid;
    }
}

id<MTLTexture> Utils::createDepthStencilAttachmentTexture()
{
    auto CAMetalLayer = DeviceMTL::getCAMetalLayer();
    MTLTextureDescriptor* textureDescriptor = [[MTLTextureDescriptor alloc] init];
    textureDescriptor.width = CAMetalLayer.drawableSize.width;
    textureDescriptor.height = CAMetalLayer.drawableSize.height;
    textureDescriptor.pixelFormat = DEPTH_STENCIL_ATTACHMENT_PIXEL_FORMAT;
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

CC_BACKEND_END
