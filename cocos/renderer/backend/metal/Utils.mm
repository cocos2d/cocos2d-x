#include "Utils.h"
#include "DeviceMTL.h"

#define COLOR_ATTAHCMENT_PIXEL_FORMAT MTLPixelFormatBGRA8Unorm
#define DEPTH_STENCIL_ATTACHMENT_PIXEL_FORMAT MTLPixelFormatDepth32Float_Stencil8

CC_BACKEND_BEGIN

id<MTLTexture> Utils::_tempColorAttachmentTexture = nil;
id<MTLTexture> Utils::_tempDepthStencilAttachmentTexture = nil;
MTLRenderPassDescriptor* Utils::_defaultRenderPassDescriptor = nil;

id<MTLTexture> Utils::getTempColorAttachmentTexture()
{
    if (!Utils::_tempColorAttachmentTexture)
        Utils::_tempColorAttachmentTexture = Utils::createColorAttachmentTexture();
    
    return Utils::_tempColorAttachmentTexture;
}

id<MTLTexture> Utils::getTempDepthStencilAttachmentTexture()
{
    if (!Utils::_tempDepthStencilAttachmentTexture)
        Utils::_tempDepthStencilAttachmentTexture = Utils::createDepthStencilAttachmentTexture();
    
    return Utils::_tempDepthStencilAttachmentTexture;
}

MTLPixelFormat Utils::getTempColorAttachmentPixelFormat()
{
    return COLOR_ATTAHCMENT_PIXEL_FORMAT;
}

MTLPixelFormat Utils::getTempDepthStencilAttachmentPixelFormat()
{
    return DEPTH_STENCIL_ATTACHMENT_PIXEL_FORMAT;
}

MTLPixelFormat Utils::getDefaultDepthStencilAttachmentPixelFormat()
{
    return DEPTH_STENCIL_ATTACHMENT_PIXEL_FORMAT;
}

MTLPixelFormat Utils::getDefaultColorAttachmentPixelFormat()
{
    return COLOR_ATTAHCMENT_PIXEL_FORMAT;
}

void Utils::createDefaultRenderPassDescriptor()
{
    if (!Utils::_defaultRenderPassDescriptor)
    {
        Utils::_defaultRenderPassDescriptor = [MTLRenderPassDescriptor renderPassDescriptor];
        Utils::_defaultRenderPassDescriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
        Utils::_defaultRenderPassDescriptor.colorAttachments[0].storeAction = MTLStoreActionStore;
        
        // Set default depth and stencil texture.
        auto defaultDepthStencilTexture = Utils::createDepthStencilAttachmentTexture();
        Utils::_defaultRenderPassDescriptor.depthAttachment.texture = defaultDepthStencilTexture;
        Utils::_defaultRenderPassDescriptor.stencilAttachment.texture = defaultDepthStencilTexture;
        
        Utils::_defaultRenderPassDescriptor.depthAttachment.loadAction = MTLLoadActionClear;
        Utils::_defaultRenderPassDescriptor.stencilAttachment.loadAction = MTLLoadActionClear;
        [Utils::_defaultRenderPassDescriptor retain];
    }
}

MTLRenderPassDescriptor* Utils::getDefaultRenderPassDescriptor()
{
    return Utils::_defaultRenderPassDescriptor;
}

void Utils::updateDefaultRenderPassDescriptor(id<MTLTexture> texture)
{
    Utils::_defaultRenderPassDescriptor.colorAttachments[0].texture = texture;
}

MTLPixelFormat Utils::toMTLPixelFormat(TextureFormat textureFormat)
{
    switch (textureFormat)
    {
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
        case TextureFormat::NONE:
            assert(false);
            break;
    }
}

id<MTLTexture> Utils::createColorAttachmentTexture()
{
    auto CAMetalLayer = DeviceMTL::getCAMetalLayer();
    MTLTextureDescriptor* textureDescriptor = [[MTLTextureDescriptor alloc] init];
    textureDescriptor.width = CAMetalLayer.drawableSize.width;
    textureDescriptor.height = CAMetalLayer.drawableSize.height;
    textureDescriptor.pixelFormat = COLOR_ATTAHCMENT_PIXEL_FORMAT;
    textureDescriptor.resourceOptions = MTLResourceStorageModePrivate;
    textureDescriptor.usage = MTLTextureUsageRenderTarget;
    auto ret = [CAMetalLayer.device newTextureWithDescriptor:textureDescriptor];
    [textureDescriptor release];
    
    return ret;
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
