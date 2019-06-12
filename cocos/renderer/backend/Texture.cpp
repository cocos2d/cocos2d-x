#include "Texture.h"
#include <cassert>
CC_BACKEND_BEGIN

#define byte(n) ((n) * 8)
#define bit(n) (n)
namespace
{
    uint8_t computeBitsPerElement(PixelFormat textureFormat)
    {
        switch (textureFormat)
        {
            case PixelFormat::RGBA8888:
            case PixelFormat::BGRA8888:
                return byte(4);
            case PixelFormat::RGB888:
                return byte(3);
            case PixelFormat::RGBA4444:
                return byte(2);
            case PixelFormat::A8:
                return byte(1);
            case PixelFormat::I8:
                return byte(1);
            case PixelFormat::RGB565:
                return byte(2);
            case PixelFormat::RGB5A1:
                return byte(2);
            case PixelFormat::AI88:
                return byte(2);
            case PixelFormat::ETC:
                return bit(4);
            case PixelFormat::ATC_RGB:
                return bit(4);
            case PixelFormat::ATC_EXPLICIT_ALPHA:
                return byte(1);
            case PixelFormat::ATC_INTERPOLATED_ALPHA:
                return byte(1);
            case PixelFormat::PVRTC2:
                return bit(2);
            case PixelFormat::PVRTC2A:
                return bit(2);
            case PixelFormat::PVRTC4:
                return bit(4);
            case PixelFormat::PVRTC4A:
                return bit(4);
            case PixelFormat::S3TC_DXT1:
                return bit(4);
            case PixelFormat::S3TC_DXT3:
                return byte(1);
            case PixelFormat::S3TC_DXT5:
                return byte(1);
            case PixelFormat::MTL_BGR5A1:
                return byte(2);
            case PixelFormat::MTL_B5G6R5:
                return byte(2);
            case PixelFormat::MTL_ABGR4:
                return byte(2);
            case PixelFormat::D24S8:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                //ios use MTLPixelFormatDepth32Float_Stencil8 as DepthStencil combined format, its 64 bits
                return byte(8);
#else
                //mac and opengl use Depth24_Stnicl8 combined format, its 32 bits
                return byte(4);
#endif
            default:
                return byte(0); //"textureFormat pixel size in bytes not defined!";
        }
        return 0;
    }
}

TextureBackend::TextureBackend(const TextureDescriptor& descriptor)
    : _bitsPerElement(computeBitsPerElement(descriptor.textureFormat))
    , _textureType(descriptor.textureType)
    , _textureFormat(descriptor.textureFormat)
    , _textureUsage(descriptor.textureUsage)
    , _width(descriptor.width)
    , _height(descriptor.height)
{
}

TextureBackend::~TextureBackend()
{}

void TextureBackend::updateTextureDescriptor(const cocos2d::backend::TextureDescriptor &descriptor)
{
    _bitsPerElement = computeBitsPerElement(descriptor.textureFormat);
    _textureType = descriptor.textureType;
    _textureFormat = descriptor.textureFormat;
    _textureUsage = descriptor.textureUsage;
    _width = descriptor.width;
    _height = descriptor.height;
}

Texture2DBackend::Texture2DBackend(const TextureDescriptor& descriptor)
    : TextureBackend(descriptor)
{
}

TextureCubemapBackend::TextureCubemapBackend(const TextureDescriptor &descriptor)
    : TextureBackend(descriptor)
{

}

CC_BACKEND_END
