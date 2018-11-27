#pragma once

#include "../Macros.h"
#include "../Types.h"
#import <Metal/Metal.h>

CC_BACKEND_BEGIN

class Utils
{
public:
    static id<MTLTexture> getTempColorAttachmentTexture();
    static id<MTLTexture> getTempDepthStencilAttachmentTexture();
    
    static void createDefaultRenderPassDescriptor();
    static MTLRenderPassDescriptor* getDefaultRenderPassDescriptor();
    static void updateDefaultRenderPassDescriptor(id<MTLTexture> texture);
    static MTLPixelFormat getDefaultDepthStencilAttachmentPixelFormat();
    static MTLPixelFormat getDefaultColorAttachmentPixelFormat();
    
    static MTLPixelFormat getTempColorAttachmentPixelFormat();
    static MTLPixelFormat getTempDepthStencilAttachmentPixelFormat();
    
    static MTLPixelFormat toMTLPixelFormat(TextureFormat textureFormat);
    
    static void generateMipmaps(id<MTLTexture> texture);
    
private:
    static id<MTLTexture> createColorAttachmentTexture();
    static id<MTLTexture> createDepthStencilAttachmentTexture();
    
    // Temple textures for render pass that just make metal work.
    static id<MTLTexture> _tempColorAttachmentTexture;
    static id<MTLTexture> _tempDepthStencilAttachmentTexture;
    
    static MTLRenderPassDescriptor* _defaultRenderPassDescriptor;
};

CC_BACKEND_END
