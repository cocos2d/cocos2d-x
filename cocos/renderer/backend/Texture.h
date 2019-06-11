#pragma once

#include "Types.h"
#include "base/CCRef.h"
#include <cassert>

#include <functional>

CC_BACKEND_BEGIN

struct TextureDescriptor
{
    TextureType textureType = TextureType::TEXTURE_2D;
    PixelFormat textureFormat = PixelFormat::RGBA8888;
    TextureUsage textureUsage = TextureUsage::READ;
    uint32_t width = 0;
    uint32_t height = 0;
    uint32_t depth = 0;
    SamplerDescriptor samplerDescriptor;
};

class Texture : public Ref
{
public:
    virtual void updateSamplerDescriptor(const SamplerDescriptor &sampler) = 0;
    virtual void getBytes(int x, int y, int width, int height, bool flipImage, std::function<void(const unsigned char*, int, int)> callback) = 0;
    virtual void generateMipmaps() = 0;
    virtual void updateTextureDescriptor(const TextureDescriptor& descriptor);

    inline PixelFormat getTextureFormat() const { return _textureFormat; }
    inline TextureUsage getTextureUsage() const { return _textureUsage; }
    inline TextureType getTextureType() const { return _textureType; }
    inline bool hasMipmaps() const { return _hasMipmaps; }

protected:
    Texture(const TextureDescriptor& descriptor);
    virtual ~Texture();
        
    // The bytes of all components.
    uint8_t _bitsPerElement = 0;
    bool _hasMipmaps = false;
    bool _isCompressed = false;
    uint32_t _width = 0;
    uint32_t _height = 0;

    TextureType _textureType = TextureType::TEXTURE_2D;
    PixelFormat _textureFormat = PixelFormat::RGBA8888;
    TextureUsage _textureUsage = TextureUsage::READ;
};


class TextureBackend2D : public Texture
{
public:
    virtual void updateData(uint8_t* data, uint32_t width , uint32_t height, uint32_t level) = 0;
    virtual void updateCompressedData(uint8_t* data, uint32_t width , uint32_t height, uint32_t dataLen, uint32_t level) = 0;
    virtual void updateSubData(uint32_t xoffset, uint32_t yoffset, uint32_t width, uint32_t height, uint32_t level, uint8_t* data) = 0;
    virtual void updateCompressedSubData(uint32_t xoffset, uint32_t yoffset, uint32_t width, uint32_t height, uint32_t dataLen, uint32_t level, uint8_t* data) = 0;

    inline uint32_t getWidth() const { return _width; }
    inline uint32_t getHeight() const { return _height; }

protected:
    TextureBackend2D(const TextureDescriptor& descriptor);
};

class TextureBackendCubemap : public Texture
{
public:
    virtual void updateFaceData(TextureCubeFace side, void *data) = 0;
        
protected:
    TextureBackendCubemap(const TextureDescriptor& descriptor);
};

CC_BACKEND_END
