#pragma once

#include "../Texture.h"
#include "DeviceMTL.h"
#import <Metal/Metal.h>

CC_BACKEND_BEGIN

class TextureMTL : public Texture
{
public:
    TextureMTL(id<MTLDevice> mtlDevice, const TextureDescriptor& descriptor);
    ~TextureMTL();
    
    virtual void updateData(uint8_t* data) override;
    virtual void updateSubData(uint32_t xoffset, uint32_t yoffset, uint32_t width, uint32_t height, uint8_t* data) override;
    
    inline id<MTLTexture> getMTLTexture() const { return _mtlTexture; }
    inline id<MTLSamplerState> getMTLSamplerState() const { return _mtlSamplerState; }
    
private:
    void createTexture(id<MTLDevice> mtlDevice, const TextureDescriptor& descriptor);
    void createSampler(id<MTLDevice> mtlDevice, const TextureDescriptor& descriptor);
    
    id<MTLTexture> _mtlTexture = nil;
    id<MTLSamplerState> _mtlSamplerState = nil;
    uint32_t _bytesPerRow = 0;
};

CC_BACKEND_END
