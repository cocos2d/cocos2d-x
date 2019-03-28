#pragma once

#include "../Macros.h"
#include "../Types.h"
#import <Metal/Metal.h>
#include <functional>

CC_BACKEND_BEGIN

class Utils
{
public:
    static void updateDefaultColorAttachmentTexture(id<MTLTexture> texture);
    static MTLPixelFormat getDefaultDepthStencilAttachmentPixelFormat();
    static MTLPixelFormat getDefaultColorAttachmentPixelFormat();
    static id<MTLTexture> getDefaultDepthStencilTexture();

    
    static MTLPixelFormat toMTLPixelFormat(TextureFormat textureFormat);
    static void generateMipmaps(id<MTLTexture> texture);
    static void getTextureBytes(int origX, int origY, int rectWidth, int rectHeight, id<MTLTexture> texture, std::function<void(const unsigned char*, int, int)> callback);
    static void swizzleImage(unsigned char* image, int width, int height, MTLPixelFormat format);
    
private:
    static id<MTLTexture> createDepthStencilAttachmentTexture();

    
    static id<MTLTexture> _defaultColorAttachmentTexture;
    static id<MTLTexture> _defaultDepthStencilAttachmentTexture;
};

CC_BACKEND_END
