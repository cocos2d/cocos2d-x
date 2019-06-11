#pragma once

#include "../Texture.h"
#include "DeviceMTL.h"
#import <Metal/Metal.h>

CC_BACKEND_BEGIN

class TextureMTL : public backend::TextureBackend2D
{
public:
    TextureMTL(id<MTLDevice> mtlDevice, const TextureDescriptor& descriptor);
    ~TextureMTL();
    
    virtual void updateData(uint8_t* data, uint32_t width , uint32_t height, uint32_t level) override;
    virtual void updateCompressedData(uint8_t* data, uint32_t width , uint32_t height, uint32_t dataLen, uint32_t level) override;
    virtual void updateSubData(uint32_t xoffset, uint32_t yoffset, uint32_t width, uint32_t height, uint32_t level, uint8_t* data) override;
    virtual void updateCompressedSubData(uint32_t xoffset, uint32_t yoffset, uint32_t width, uint32_t height, uint32_t dataLen, uint32_t level, uint8_t* data) override;
    
    virtual void updateSamplerDescriptor(const SamplerDescriptor &sampler) override;
    virtual void getBytes(int x, int y, int width, int height, bool flipImage, std::function<void(const unsigned char*, int, int)> callback) override;
    virtual void generateMipmaps() override;
    virtual void updateTextureDescriptor(const cocos2d::backend::TextureDescriptor &descriptor) override;
    
    inline id<MTLTexture> getMTLTexture() const { return _mtlTexture; }
    inline id<MTLSamplerState> getMTLSamplerState() const { return _mtlSamplerState; }
    
private:
    void createTexture(id<MTLDevice> mtlDevice, const TextureDescriptor& descriptor);
    void createSampler(id<MTLDevice> mtlDevice, const SamplerDescriptor& descriptor);
    
    MTLSamplerAddressMode _sAddressMode;
    MTLSamplerAddressMode _tAddressMode;
    MTLSamplerMinMagFilter _minFilter;
    MTLSamplerMinMagFilter _magFilter;
    MTLSamplerMipFilter _mipFilter;
    
    id<MTLDevice> _mtlDevice = nil;
    id<MTLTexture> _mtlTexture = nil;
    id<MTLSamplerState> _mtlSamplerState = nil;
    unsigned int _bytesPerRow = 0;
};

class TextureCubeMTL : public backend::TextureCubemap
{
public:
    TextureCubeMTL(id<MTLDevice> mtlDevice, const TextureDescriptor& descriptor);
    ~TextureCubeMTL();
    
    virtual void updateSamplerDescriptor(const SamplerDescriptor &sampler) override;
    virtual void updateFaceData(TextureCubeFace side, void *data) override;
    virtual void getBytes(int x, int y, int width, int height, bool flipImage, std::function<void(const unsigned char*, int, int)> callback) override;
    virtual void generateMipmaps() override;
    virtual void updateTextureDescriptor(const cocos2d::backend::TextureDescriptor &descriptor) override;
    
    inline id<MTLTexture> getMTLTexture() const { return _mtlTexture; }
    inline id<MTLSamplerState> getMTLSamplerState() const { return _mtlSamplerState; }
    
private:
    void createTexture(id<MTLDevice> mtlDevice, const TextureDescriptor& descriptor);
    void createSampler(id<MTLDevice> mtlDevice, const SamplerDescriptor& descriptor);
    
    MTLSamplerAddressMode _sAddressMode;
    MTLSamplerAddressMode _tAddressMode;
    MTLSamplerMinMagFilter _minFilter;
    MTLSamplerMinMagFilter _magFilter;
    MTLSamplerMipFilter _mipFilter;
    
    id<MTLDevice> _mtlDevice = nil;
    id<MTLTexture> _mtlTexture = nil;
    id<MTLSamplerState> _mtlSamplerState = nil;
    MTLRegion _region;
    unsigned int _bytesPerImage = 0;
    unsigned int _bytesPerRow = 0;
};

CC_BACKEND_END
