#pragma once

#include "Types.h"
#include "base/CCRef.h"

CC_BACKEND_BEGIN

struct TextureDescriptor
{
    TextureType textureType = TextureType::TEXTURE_2D;
    TextureFormat textureFormat = TextureFormat::R8G8B8A8;
    TextureUsage textureUsage = TextureUsage::READ;
    uint32_t width = 0;
    uint32_t height = 0;
    uint32_t depth = 0;
    
    SamplerDescriptor samplerDescriptor;
};

class Texture : public cocos2d::Ref
{
public:
    virtual void updateData(uint8_t* data) = 0;
    virtual void updateSubData(uint32_t xoffset, uint32_t yoffset, uint32_t width, uint32_t height, uint8_t* data) = 0;
    
    inline TextureFormat getTextureFormat() const { return _textureFormat; }
    inline TextureUsage getTextureUsage() const { return _textureUsage; }
    inline uint32_t getWidth() const { return _width; }
    inline uint32_t getHeight() const { return _height; }
    
protected:
    Texture(const TextureDescriptor& descriptor);
    virtual ~Texture();
        
    uint32_t _width = 0;
    uint32_t _height = 0;
    // The bytes of all components.
    uint8_t _bytesPerElement = 0;
    TextureType _textureType = TextureType::TEXTURE_2D;
    TextureFormat _textureFormat = TextureFormat::R8G8B8;
    TextureUsage _textureUsage = TextureUsage::READ;
    bool _isMipmapEnabled = false;
};

CC_BACKEND_END
