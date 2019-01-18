#include "Texture.h"
#include <cassert>
CC_BACKEND_BEGIN

#define byte(n) ((n) * 8)
#define bit(n) (n)
namespace
{
    uint8_t computeBitsPerElement(TextureFormat textureFormat)
    {
        switch (textureFormat)
        {
            case TextureFormat::R8G8B8A8:
                return byte(4);
            case TextureFormat::R8G8B8:
                return byte(3);
            case TextureFormat::RGBA4444:
                return byte(2);
            case TextureFormat::A8:
                return byte(1);
            case TextureFormat::I8:
                return byte(1);
            case TextureFormat::RGB565:
                return byte(2);
            case TextureFormat::RGB5A1:
                return byte(2);
            case TextureFormat::AI88:
                return byte(2);
            case TextureFormat::ETC1:
                return bit(4);
            case TextureFormat::ATC_RGB:
                return bit(4);
            case TextureFormat::ATC_EXPLICIT_ALPHA:
                return byte(1);
            case TextureFormat::ATC_INTERPOLATED_ALPHA:
                return byte(1);
            case TextureFormat::PVRTC2:
                return bit(2);
            case TextureFormat::PVRTC2A:
                return bit(2);
            case TextureFormat::PVRTC4:
                return bit(4);
            case TextureFormat::PVRTC4A:
                return bit(4);
            case TextureFormat::S3TC_DXT1:
                return bit(4);
            case TextureFormat::S3TC_DXT3:
                return byte(1);
            case TextureFormat::S3TC_DXT5:
                return byte(1);
            case TextureFormat::MTL_BGR5A1:
                return byte(2);
            case TextureFormat::MTL_B5G6R5:
                return byte(2);
            case TextureFormat::MTL_ABGR4:
                return byte(2);
            default:
                assert(false); //"textureFormat pixel size in bytes not defined!";
                break;
        }
        return 0;
    }
}

Texture::Texture(const TextureDescriptor& descriptor)
: _width(descriptor.width)
, _height(descriptor.height)
, _textureType(descriptor.textureType)
, _textureFormat(descriptor.textureFormat)
, _bitsPerElement(computeBitsPerElement(descriptor.textureFormat))
, _isMipmapEnabled(descriptor.samplerDescriptor.mipmapEnabled)
, _textureUsage(descriptor.textureUsage)
, _isCompressed(descriptor.compressed)
{
}

Texture::~Texture()
{}

CC_BACKEND_END
