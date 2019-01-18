#include "TextureGL.h"
#include "base/ccMacros.h"
#include "platform/CCPlatformConfig.h"

CC_BACKEND_BEGIN

namespace
{
#define ISPOW2(n) (((n) & (n-1)) == 0)

    GLint toGLMagFilter(SamplerFilter magFilter)
    {
        GLint ret = GL_LINEAR;
        switch (magFilter)
        {
            case SamplerFilter::LINEAR:
                ret = GL_LINEAR;
                break;
            case SamplerFilter::NEAREST:
                ret = GL_NEAREST;
                break;
            default:
                break;
        }
        return ret;
    }
    
    GLint toGLMinFilter(SamplerFilter minFilter, SamplerFilter mipmapFilter, bool mipmapEnabled, bool isPow2)
    {
        if (mipmapEnabled)
        {
            if(!isPow2)
            {
                cocos2d::log("Change minification filter to either NEAREST or LINEAR since non-power-of-two texture occur in %s %s %d", __FILE__, __FUNCTION__, __LINE__);
                if (SamplerFilter::LINEAR == minFilter)
                    return GL_LINEAR;
                else
                    return GL_NEAREST;
            }
            
            switch (minFilter)
            {
                case SamplerFilter::LINEAR:
                    switch (mipmapFilter)
                    {
                        case SamplerFilter::LINEAR:
                            return GL_LINEAR_MIPMAP_LINEAR;
                        case SamplerFilter::NEAREST:
                            return GL_LINEAR_MIPMAP_NEAREST;
                    }
                case SamplerFilter::NEAREST:
                    switch (mipmapFilter)
                    {
                        case SamplerFilter::LINEAR:
                            return GL_NEAREST_MIPMAP_LINEAR;
                        case SamplerFilter::NEAREST:
                            return GL_NEAREST_MIPMAP_NEAREST;
                    }
            }
        }
        else
        {
            if (SamplerFilter::LINEAR == minFilter)
                return GL_LINEAR;
            else
                return GL_NEAREST;
        }
    }
    
    GLint toGLAddressMode(SamplerAddressMode addressMode, bool isPow2)
    {
        GLint ret = GL_REPEAT;
        if(!isPow2 && (addressMode != SamplerAddressMode::CLAMP_TO_EDGE))
        {
            cocos2d::log("Change texture wrap mode to CLAMP_TO_EDGE since non-power-of-two texture occur in %s %s %d", __FILE__, __FUNCTION__, __LINE__);
            return GL_CLAMP_TO_EDGE;
        }
        
        switch (addressMode)
        {
            case SamplerAddressMode::REPEAT:
                ret = GL_REPEAT;
                break;
            case SamplerAddressMode::MIRROR_REPEAT:
                ret = GL_MIRRORED_REPEAT;
                break;
            case SamplerAddressMode::CLAMP_TO_EDGE:
                ret = GL_CLAMP_TO_EDGE;
                break;
            default:
                break;
        }
        return ret;
    }
}

TextureGL::TextureGL(const TextureDescriptor& descriptor) : Texture(descriptor)
{
    glGenTextures(1, &_texture);
    toGLTypes();
    bool isPow2 = ISPOW2(_width) && ISPOW2(_height);
    _magFilterGL = toGLMagFilter(descriptor.samplerDescriptor.magFilter);
    _minFilterGL = toGLMinFilter(descriptor.samplerDescriptor.minFilter,
                                 descriptor.samplerDescriptor.mipmapFilter, _isMipmapEnabled, isPow2);
    
    _sAddressModeGL = toGLAddressMode(descriptor.samplerDescriptor.sAddressMode, isPow2);
    _tAddressModeGL = toGLAddressMode(descriptor.samplerDescriptor.tAddressMode, isPow2);
   
    // Update data here because `updateData()` may not be invoked later.
    // For example, a texture used as depth buffer will not invoke updateData().
    uint8_t* data = (uint8_t*)malloc(_width * _height * _bitsPerElement / 8);
    updateData(data);
    free(data);
}

TextureGL::~TextureGL()
{
    if (_texture)
        glDeleteTextures(1, &_texture);
}

void TextureGL::updateSamplerDescriptor(const SamplerDescriptor &sampler) {
    bool isPow2 = ISPOW2(_width) && ISPOW2(_height);
    bool needGenerateMipmap = !_isMipmapEnabled && sampler.mipmapEnabled;
    _isMipmapEnabled = sampler.mipmapEnabled;

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture);

    if (sampler.magFilter != SamplerFilter::DONT_CARE)
    {
        _magFilterGL = toGLMagFilter(sampler.magFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _magFilterGL);
    }

    if (sampler.minFilter != SamplerFilter::DONT_CARE)
    {
        _minFilterGL = toGLMinFilter(sampler.minFilter, sampler.mipmapFilter, _isMipmapEnabled, isPow2);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _minFilterGL);
    }

    if (sampler.sAddressMode != SamplerAddressMode::DONT_CARE)
    {
        _sAddressModeGL = toGLAddressMode(sampler.sAddressMode, isPow2);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _sAddressModeGL);
    }

    if (sampler.tAddressMode != SamplerAddressMode::DONT_CARE)
    {
        _tAddressModeGL = toGLAddressMode(sampler.tAddressMode, isPow2);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _tAddressModeGL);
    }

    if (needGenerateMipmap) generateMipmpas();
}

void TextureGL::updateData(uint8_t* data)
{
    // TODO: support texture cube, and compressed data.
    
    //Set the row align only when mipmapsNum == 1 and the data is uncompressed
    if(!_isMipmapEnabled && !_isCompressed)
    {
        unsigned int bytesPerRow = _width * _bitsPerElement / 8;
        
        if(bytesPerRow % 8 == 0)
        {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 8);
        }
        else if(bytesPerRow % 4 == 0)
        {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        }
        else if(bytesPerRow % 2 == 0)
        {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
        }
        else
        {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        }
    }
    else
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    }
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _magFilterGL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _minFilterGL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _sAddressModeGL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _tAddressModeGL);


    if(_isCompressed)
    {
        auto datalen = _width * _height * _bitsPerElement / 8;
        glCompressedTexImage2D(GL_TEXTURE_2D, 0, _internalFormat, (GLsizei)_width, (GLsizei)_height, 0, datalen, data);
    }
    else
    {
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     _internalFormat,
                     _width,
                     _height,
                     0,
                     _format,
                     _type,
                     data);
    }
    CHECK_GL_ERROR_DEBUG();
    
    generateMipmpas();
    CHECK_GL_ERROR_DEBUG();
}

void TextureGL::updateSubData(unsigned int xoffset, unsigned int yoffset, unsigned int width, unsigned int height, uint8_t* data)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexSubImage2D(GL_TEXTURE_2D,
                    0,
                    xoffset,
                    yoffset,
                    width,
                    height,
                    _format,
                    _type,
                    data);
    CHECK_GL_ERROR_DEBUG();
    
    generateMipmpas();
    CHECK_GL_ERROR_DEBUG();
}

void TextureGL::apply(int index) const
{
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, _texture);
}

void TextureGL::generateMipmpas() const
{
    if (_isMipmapEnabled &&
        TextureUsage::RENDER_TARGET != _textureUsage)
        glGenerateMipmap(GL_TEXTURE_2D);
}

void TextureGL::toGLTypes()
{
    switch (_textureFormat)
    {
        case TextureFormat::R8G8B8A8:
            _internalFormat = GL_RGBA;
            _format = GL_RGBA;
            _type = GL_UNSIGNED_BYTE;
            break;
        case TextureFormat::R8G8B8:
            _internalFormat = GL_RGB;
            _format = GL_RGB;
            _type = GL_UNSIGNED_BYTE;
            break;
        case TextureFormat::RGBA4444:
            _internalFormat = GL_RGBA;
            _format = GL_RGBA;
            _type = GL_UNSIGNED_SHORT_4_4_4_4;
            break;
        case TextureFormat::A8:
            _internalFormat = GL_ALPHA;
            _format = GL_ALPHA;
            _type = GL_UNSIGNED_BYTE;
            break;
        case TextureFormat::I8:
            _internalFormat = GL_LUMINANCE;
            _format = GL_LUMINANCE;
            _type = GL_UNSIGNED_BYTE;
            break;
        case TextureFormat::AI88:
            _internalFormat = GL_LUMINANCE_ALPHA;
            _format = GL_LUMINANCE_ALPHA;
            _type = GL_UNSIGNED_BYTE;
            break;
        case TextureFormat::RGB565:
            _internalFormat = GL_RGB;
            _format = GL_RGB;
            _type = GL_UNSIGNED_SHORT_5_6_5;
            break;
        case TextureFormat::RGB5A1:
            _internalFormat = GL_RGBA;
            _format = GL_RGBA;
            _type = GL_UNSIGNED_SHORT_5_5_5_1;
            break;
#ifdef GL_ETC1_RGB8_OES
        case TextureFormat::ETC1:
            _internalFormat = GL_ETC1_RGB8_OES;
            _format = 0xFFFFFFFF;
            _type = 0xFFFFFFFF;
            _isCompressed = true;
            break;
#endif // GL_ETC1_RGB8_OES
#ifdef GL_ATC_RGB_AMD
        case TextureFormat ::ATC_RGB:
            _internalFormat = GL_ATC_RGB_AMD;
            _format = 0xFFFFFFFF;
            _type = 0xFFFFFFFF;
            _isCompressed = true;
            break;
#endif // GL_ATC_RGB_AMD
#ifdef GL_ATC_RGBA_EXPLICIT_ALPHA_AMD
        case TextureFormat::ATC_EXPLICIT_ALPHA:
            _internalFormat = GL_ATC_RGBA_EXPLICIT_ALPHA_AMD;
            _format = 0xFFFFFFFF;
            _type = 0xFFFFFFFF;
            _isCompressed = true;
#endif // GL_ATC_RGBA_EXPLICIT_ALPHA_AMD
#ifdef GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD
        case TextureFormat::ATC_INTERPOLATED_ALPHA:
            _internalFormat = GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD;
            _format = 0xFFFFFFFF;
            _type = 0xFFFFFFFF;
            _isCompressed = true;
            break;
#endif // GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD

#ifdef GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG
        case TextureFormat::PVRTC2:
            _internalFormat = GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG;
            _format = 0xFFFFFFFF;
            _type = 0xFFFFFFFF;
            _isCompressed = true;
            break;
#endif 
#ifdef GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG
        case TextureFormat::PVRTC2A:
            _internalFormat = GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;
            _format = 0xFFFFFFFF;
            _type = 0xFFFFFFFF;
            _isCompressed = true;
            break;
#endif
#ifdef GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG
    case TextureFormat::PVRTC4:
            _internalFormat = GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG;
            _format = 0xFFFFFFFF;
            _type = 0xFFFFFFFF;
            _isCompressed = true;
            break;
#endif
#ifdef GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG
        case TextureFormat::PVRTC4A:
            _internalFormat = GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
            _format = 0xFFFFFFFF;
            _type = 0xFFFFFFFF;
            _isCompressed = true;
            break;
#endif
#ifdef GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
        case TextureFormat::S3TC_DXT1:
            _internalFormat = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            _format = 0xFFFFFFFF;
            _type = 0xFFFFFFFF;
            _isCompressed = true;
            break;
#endif 
#ifdef GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
        case TextureFormat::S3TC_DXT3:
            _internalFormat = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            _format = 0xFFFFFFFF;
            _type = 0xFFFFFFFF;
            _isCompressed = true;
            break;
#endif
#ifdef GL_COMPRESSED_RGBA_S3TC_DXT5_EXT
        case TextureFormat::S3TC_DXT5:
            _internalFormat = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            _format = 0xFFFFFFFF;
            _type = 0xFFFFFFFF;
            _isCompressed = true;
            break;
#endif
//        case TextureFormat::D16:
//            _format = GL_DEPTH_COMPONENT;
//            _internalFormat = GL_DEPTH_COMPONENT;
//            _type = GL_UNSIGNED_INT;
        case TextureFormat::D24S8:
#ifdef CC_USE_GLES
            _format = GL_DEPTH_STENCIL_OES;
            _internalFormat = GL_DEPTH_STENCIL_OES;
            _type = GL_UNSIGNED_INT_24_8_OES;
#else
            _format = GL_DEPTH_STENCIL;
            _internalFormat = GL_DEPTH32F_STENCIL8;
            _type = GL_FLOAT_32_UNSIGNED_INT_24_8_REV;
#endif
            break;
        default:
            break;
    }
}

CC_BACKEND_END
