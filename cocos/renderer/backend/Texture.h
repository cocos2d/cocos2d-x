#pragma once

#include "Types.h"
#include "base/CCRef.h"
#include <cassert>

CC_BACKEND_BEGIN

struct TextureDescriptor
{
    TextureType textureType = TextureType::TEXTURE_2D;
    TextureFormat textureFormat = TextureFormat::R8G8B8A8;
    TextureUsage textureUsage = TextureUsage::READ;;
    uint32_t depth = 0;
    bool compressed = false;
    SamplerDescriptor samplerDescriptor;    
    
    uint32_t width = 0;
    uint32_t height = 0;
};

class Texture : public Ref
{
public:
    virtual void updateData(uint8_t* data) = 0;
    virtual void updateSubData(uint32_t xoffset, uint32_t yoffset, uint32_t width, uint32_t height, uint8_t* data) = 0;
    
    virtual void updateSamplerDescriptor(const SamplerDescriptor &sampler) = 0;
    virtual void updateImageData(TextureCubeSide side, Texture2D::PixelFormat format, int width, int height, void *data) = 0;

    inline uint32_t getWidth() const { return _width; }
    inline uint32_t getHeight() const { return _height; }

    inline TextureFormat getTextureFormat() const { return _textureFormat; }
    inline TextureUsage getTextureUsage() const { return _textureUsage; }
    inline TextureType getTextureType() const { return _textureType; }

protected:
    Texture(const TextureDescriptor& descriptor);
    virtual ~Texture();
        
    uint32_t _width = 0;
    uint32_t _height = 0;
    // The bytes of all components.
    uint8_t _bitsPerElement = 0;
    bool _isMipmapEnabled = false;
    bool _isCompressed = false;

    TextureType _textureType = TextureType::TEXTURE_2D;
    TextureFormat _textureFormat = TextureFormat::R8G8B8;
    TextureUsage _textureUsage = TextureUsage::READ;
};

CC_BACKEND_END
