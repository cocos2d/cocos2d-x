#pragma once

#include "../Macros.h"
#include "../Types.h"
#import <Metal/Metal.h>

CC_BACKEND_BEGIN

class Utils
{
public:
    static void updateDefaultColorAttachmentTexture(id<MTLTexture> texture);
    static MTLPixelFormat getDefaultDepthStencilAttachmentPixelFormat();
    static MTLPixelFormat getDefaultColorAttachmentPixelFormat();
    static id<MTLTexture> getDefaultDepthStencilTexture();
    static id<MTLTexture> getDefaultColorAttachmentTexture();

    
    static MTLPixelFormat toMTLPixelFormat(TextureFormat textureFormat);
    static void generateMipmaps(id<MTLTexture> texture);
    
private:
    static id<MTLTexture> createColorAttachmentTexture();
    static id<MTLTexture> createDepthStencilAttachmentTexture();

    
    static id<MTLTexture> _defaultColorAttachmentTexture;
    static id<MTLTexture> _defaultDepthStencilAttachmentTexture;
};

CC_BACKEND_END
