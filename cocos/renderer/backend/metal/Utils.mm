#include "Utils.h"
#include "DeviceMTL.h"

#define COLOR_ATTAHCMENT_PIXEL_FORMAT MTLPixelFormatBGRA8Unorm

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define DEPTH_STENCIL_ATTACHMENT_PIXEL_FORMAT MTLPixelFormatDepth32Float_Stencil8
#else
#define DEPTH_STENCIL_ATTACHMENT_PIXEL_FORMAT MTLPixelFormatDepth24Unorm_Stencil8
#endif

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
}

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
           
        //on mac, D24S8 means MTLPixelFormatDepth24Unorm_Stencil8, while on ios it means MTLPixelFormatDepth32Float_Stencil8
        case TextureFormat::D24S8:
            return DEPTH_STENCIL_ATTACHMENT_PIXEL_FORMAT;
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

void Utils::swizzleImage(unsigned char *image, int width, int height, MTLPixelFormat format)
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

void Utils::getTextureBytes(int origX, int origY, int rectWidth, int rectHeight, id<MTLTexture> texture, std::function<void(const unsigned char*, int, int)> callback)
{
    NSUInteger texWidth = texture.width;
    NSUInteger texHeight = texture.height;
    MTLRegion region = MTLRegionMake2D(0, 0, texWidth, texHeight);
    MTLRegion imageRegion = MTLRegionMake2D(origX, origY, rectWidth, rectHeight);
    
    //Default storage mode on mac is managed, need blit it.
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
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
    
    [blitCommandEncoder synchronizeResource:copiedTexture];
    [blitCommandEncoder endEncoding];
   
    [commandBuffer addCompletedHandler:^(id<MTLCommandBuffer> commandBufferMTL) {
        auto bytePerRow = rectWidth * getBitsPerElement(texture.pixelFormat) / 8;
        unsigned char* image = new (std::nothrow) unsigned char[bytePerRow * rectHeight];
        [copiedTexture getBytes:image bytesPerRow:bytePerRow fromRegion:imageRegion mipmapLevel:0];
        
        swizzleImage(image, rectWidth, rectHeight, texture.pixelFormat);
        
        callback(image, rectWidth, rectHeight);
        CC_SAFE_DELETE_ARRAY(image);
        [copiedTexture release];
    }];
    [commandBuffer commit];
#else
    auto bytePerRow = rectWidth * getBitsPerElement(texture.pixelFormat) / 8;
    unsigned char* image = new (std::nothrow) unsigned char[bytePerRow * rectHeight];
    [texture getBytes:image bytesPerRow:bytePerRow fromRegion:imageRegion mipmapLevel:0];
    swizzleImage(image, rectWidth, rectHeight, texture.pixelFormat);
    callback(image, rectWidth, rectHeight);
    CC_SAFE_DELETE_ARRAY(image);
#endif
}

CC_BACKEND_END
