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
                        case SamplerFilter::DONT_CARE:
                            return GL_LINEAR_MIPMAP_NEAREST;
                    }
                case SamplerFilter::NEAREST:
                    switch (mipmapFilter)
                    {
                        case SamplerFilter::LINEAR:
                            return GL_NEAREST_MIPMAP_LINEAR;
                        case SamplerFilter::NEAREST:
                            return GL_NEAREST_MIPMAP_NEAREST;
                        case SamplerFilter::DONT_CARE:
                            return GL_LINEAR_MIPMAP_NEAREST;
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
        return GL_NEAREST;
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


    void toGLTypes(TextureFormat textureFormat, GLint &internalFormat, GLuint &format, GLenum &type, bool &isCompressed)
    {
        switch (textureFormat)
        {
        case TextureFormat::R8G8B8A8:
            internalFormat = GL_RGBA;
            format = GL_RGBA;
            type = GL_UNSIGNED_BYTE;
            break;
        case TextureFormat::R8G8B8:
            internalFormat = GL_RGB;
            format = GL_RGB;
            type = GL_UNSIGNED_BYTE;
            break;
        case TextureFormat::RGBA4444:
            internalFormat = GL_RGBA;
            format = GL_RGBA;
            type = GL_UNSIGNED_SHORT_4_4_4_4;
            break;
        case TextureFormat::A8:
            internalFormat = GL_ALPHA;
            format = GL_ALPHA;
            type = GL_UNSIGNED_BYTE;
            break;
        case TextureFormat::I8:
            internalFormat = GL_LUMINANCE;
            format = GL_LUMINANCE;
            type = GL_UNSIGNED_BYTE;
            break;
        case TextureFormat::AI88:
            internalFormat = GL_LUMINANCE_ALPHA;
            format = GL_LUMINANCE_ALPHA;
            type = GL_UNSIGNED_BYTE;
            break;
        case TextureFormat::RGB565:
            internalFormat = GL_RGB;
            format = GL_RGB;
            type = GL_UNSIGNED_SHORT_5_6_5;
            break;
        case TextureFormat::RGB5A1:
            internalFormat = GL_RGBA;
            format = GL_RGBA;
            type = GL_UNSIGNED_SHORT_5_5_5_1;
            break;
#ifdef GL_ETC1_RGB8_OES
        case TextureFormat::ETC1:
            internalFormat = GL_ETC1_RGB8_OES;
            format = 0xFFFFFFFF;
            type = 0xFFFFFFFF;
            isCompressed = true;
            break;
#endif // GL_ETC1_RGB8_OES
#ifdef GL_ATC_RGB_AMD
        case TextureFormat::ATC_RGB:
            internalFormat = GL_ATC_RGB_AMD;
            format = 0xFFFFFFFF;
            type = 0xFFFFFFFF;
            isCompressed = true;
            break;
#endif // GL_ATC_RGB_AMD
#ifdef GL_ATC_RGBA_EXPLICIT_ALPHA_AMD
        case TextureFormat::ATC_EXPLICIT_ALPHA:
            internalFormat = GL_ATC_RGBA_EXPLICIT_ALPHA_AMD;
            format = 0xFFFFFFFF;
            type = 0xFFFFFFFF;
            isCompressed = true;
#endif // GL_ATC_RGBA_EXPLICIT_ALPHA_AMD
#ifdef GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD
        case TextureFormat::ATC_INTERPOLATED_ALPHA:
            internalFormat = GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD;
            format = 0xFFFFFFFF;
            type = 0xFFFFFFFF;
            isCompressed = true;
            break;
#endif // GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD

#ifdef GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG
        case TextureFormat::PVRTC2:
            internalFormat = GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG;
            format = 0xFFFFFFFF;
            type = 0xFFFFFFFF;
            isCompressed = true;
            break;
#endif 
#ifdef GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG
        case TextureFormat::PVRTC2A:
            internalFormat = GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;
            format = 0xFFFFFFFF;
            type = 0xFFFFFFFF;
            isCompressed = true;
            break;
#endif
#ifdef GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG
        case TextureFormat::PVRTC4:
            internalFormat = GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG;
            format = 0xFFFFFFFF;
            type = 0xFFFFFFFF;
            isCompressed = true;
            break;
#endif
#ifdef GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG
        case TextureFormat::PVRTC4A:
            internalFormat = GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
            format = 0xFFFFFFFF;
            type = 0xFFFFFFFF;
            isCompressed = true;
            break;
#endif
#ifdef GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
        case TextureFormat::S3TC_DXT1:
            internalFormat = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            format = 0xFFFFFFFF;
            type = 0xFFFFFFFF;
            isCompressed = true;
            break;
#endif 
#ifdef GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
        case TextureFormat::S3TC_DXT3:
            internalFormat = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            format = 0xFFFFFFFF;
            type = 0xFFFFFFFF;
            isCompressed = true;
            break;
#endif
#ifdef GL_COMPRESSED_RGBA_S3TC_DXT5_EXT
        case TextureFormat::S3TC_DXT5:
            internalFormat = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            format = 0xFFFFFFFF;
            type = 0xFFFFFFFF;
            isCompressed = true;
            break;
#endif
            //        case TextureFormat::D16:
            //            format = GL_DEPTH_COMPONENT;
            //            internalFormat = GL_DEPTH_COMPONENT;
            //            type = GL_UNSIGNED_INT;
        case TextureFormat::D24S8:
#ifdef CC_USE_GLES
            format = GL_DEPTH_STENCIL_OES;
            internalFormat = GL_DEPTH_STENCIL_OES;
            type = GL_UNSIGNED_INT_24_8_OES;
#else
            format = GL_DEPTH_STENCIL;
            internalFormat = GL_DEPTH32F_STENCIL8;
            type = GL_FLOAT_32_UNSIGNED_INT_24_8_REV;
#endif
            break;
        default:
            break;
        }
    }

}



void TextureInfoGL::applySamplerDescriptor(const SamplerDescriptor& descriptor, bool isPow2)
{
    if (descriptor.magFilter != SamplerFilter::DONT_CARE)
    {
        magFilterGL = toGLMagFilter(descriptor.magFilter);
    }

    if (descriptor.minFilter != SamplerFilter::DONT_CARE)
    {
        minFilterGL = toGLMinFilter(descriptor.minFilter, descriptor.mipmapFilter, descriptor.mipmapEnabled, isPow2);
    }

    if (descriptor.sAddressMode != SamplerAddressMode::DONT_CARE)
    {
        sAddressModeGL = toGLAddressMode(descriptor.sAddressMode, isPow2);
    }

    if (descriptor.tAddressMode != SamplerAddressMode::DONT_CARE)
    {
        tAddressModeGL = toGLAddressMode(descriptor.tAddressMode, isPow2);
    }
}

Texture2DGL::Texture2DGL(const TextureDescriptor& descriptor) : Texture2D(descriptor)
{
    glGenTextures(1, &_textureInfo.texture);
    toGLTypes(_textureFormat, _textureInfo.internalFormat, _textureInfo.format, _textureInfo.type, _isCompressed);

    bool isPow2 = ISPOW2(_width) && ISPOW2(_height);
    _textureInfo.magFilterGL = toGLMagFilter(descriptor.samplerDescriptor.magFilter);
    _textureInfo.minFilterGL = toGLMinFilter(descriptor.samplerDescriptor.minFilter,
                                 descriptor.samplerDescriptor.mipmapFilter, _isMipmapEnabled, isPow2);
    
    _textureInfo.sAddressModeGL = toGLAddressMode(descriptor.samplerDescriptor.sAddressMode, isPow2);
    _textureInfo.tAddressModeGL = toGLAddressMode(descriptor.samplerDescriptor.tAddressMode, isPow2);
   
    // Update data here because `updateData()` may not be invoked later.
    // For example, a texture used as depth buffer will not invoke updateData().
    uint8_t* data = (uint8_t*)malloc(_width * _height * _bitsPerElement / 8);
    updateData(data);
    free(data);
}

Texture2DGL::~Texture2DGL()
{
    if (_textureInfo.texture)
        glDeleteTextures(1, &_textureInfo.texture);
}

void Texture2DGL::updateSamplerDescriptor(const SamplerDescriptor &sampler) {
    bool isPow2 = ISPOW2(_width) && ISPOW2(_height);
    bool needGenerateMipmap = !_isMipmapEnabled && sampler.mipmapEnabled;
    _isMipmapEnabled = sampler.mipmapEnabled;

    _textureInfo.applySamplerDescriptor(sampler, isPow2);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _textureInfo.texture);

    if (sampler.magFilter != SamplerFilter::DONT_CARE)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _textureInfo.magFilterGL);
    }

    if (sampler.minFilter != SamplerFilter::DONT_CARE)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _textureInfo.minFilterGL);
    }

    if (sampler.sAddressMode != SamplerAddressMode::DONT_CARE)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _textureInfo.sAddressModeGL);
    }

    if (sampler.tAddressMode != SamplerAddressMode::DONT_CARE)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _textureInfo.tAddressModeGL);
    }

    if (needGenerateMipmap) generateMipmpas();
}

void Texture2DGL::updateData(uint8_t* data)
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
    glBindTexture(GL_TEXTURE_2D, _textureInfo.texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _textureInfo.magFilterGL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _textureInfo.minFilterGL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _textureInfo.sAddressModeGL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _textureInfo.tAddressModeGL);


    if(_isCompressed)
    {
        auto datalen = _width * _height * _bitsPerElement / 8;
        glCompressedTexImage2D(GL_TEXTURE_2D, 0, _textureInfo.internalFormat, (GLsizei)_width, (GLsizei)_height, 0, datalen, data);
    }
    else
    {
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     _textureInfo.internalFormat,
                     _width,
                     _height,
                     0,
                     _textureInfo.format,
                     _textureInfo.type,
                     data);
    }
    CHECK_GL_ERROR_DEBUG();
    
    generateMipmpas();
    CHECK_GL_ERROR_DEBUG();
}

void Texture2DGL::updateSubData(unsigned int xoffset, unsigned int yoffset, unsigned int width, unsigned int height, uint8_t* data)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _textureInfo.texture);
    glTexSubImage2D(GL_TEXTURE_2D,
                    0,
                    xoffset,
                    yoffset,
                    width,
                    height,
                    _textureInfo.format,
                    _textureInfo.type,
                    data);
    CHECK_GL_ERROR_DEBUG();
    
    generateMipmpas();
    CHECK_GL_ERROR_DEBUG();
}

void Texture2DGL::apply(int index) const
{
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, _textureInfo.texture);
}

void Texture2DGL::generateMipmpas() const
{
    if (Texture2D::_isMipmapEnabled &&
        TextureUsage::RENDER_TARGET != Texture2D:: _textureUsage)
        glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture2DGL::getBytes(int x, int y, int width, int height, TextureFormat format, bool flipImage, std::function<void(const unsigned char* imageRGBA)> callback)
{
    GLint defaultFBO = 0;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &defaultFBO);

    GLuint frameBuffer = 0;
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureInfo.texture, 0);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);

    unsigned char* imageRGBA = new unsigned char[width * height * 4];
    glReadPixels(x,y,width, height,GL_RGBA,GL_UNSIGNED_BYTE, imageRGBA);

    if(flipImage)
    {
        unsigned char* flippedImage = new unsigned char[width * height *4];
        for (int i = 0; i < height; ++i)
        {
            memcpy(&flippedImage[i * width * 4],
                   &imageRGBA[(height - i - 1) * width * 4],
                   width * 4);
        }
        callback(flippedImage);
        CC_SAFE_DELETE_ARRAY(flippedImage);
    } else
    {
        callback(imageRGBA);
        CC_SAFE_DELETE_ARRAY(imageRGBA);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, defaultFBO);
    glDeleteFramebuffers(1, &frameBuffer);
}

TextureCubeGL::TextureCubeGL(const TextureDescriptor& descriptor)
    :TextureCubemap(descriptor)
{
    assert(descriptor.width == descriptor.height);
    _size = descriptor.width;
    _textureType = TextureType::TEXTURE_CUBE;
    toGLTypes(_textureFormat, _textureInfo.internalFormat, _textureInfo.format, _textureInfo.type, _isCompressed);
    glGenTextures(1, &_textureInfo.texture);
    CHECK_GL_ERROR_DEBUG();
}

TextureCubeGL::~TextureCubeGL()
{
    if(_textureInfo.texture)
        glDeleteTextures(1, &_textureInfo.texture);
    _textureInfo.texture = 0;
}

void TextureCubeGL::updateSamplerDescriptor(const SamplerDescriptor &sampler)
{
    _textureInfo.applySamplerDescriptor(sampler, true);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _textureInfo.texture);
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, _textureInfo.minFilterGL);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, _textureInfo.magFilterGL);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, _textureInfo.sAddressModeGL);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, _textureInfo.tAddressModeGL);
    
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void TextureCubeGL::apply(int index) const
{
    glActiveTexture(GL_TEXTURE0+ index);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _textureInfo.texture);
    CHECK_GL_ERROR_DEBUG();
}

void TextureCubeGL::updateFaceData(TextureCubeFace side, void *data)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _textureInfo.texture);
    CHECK_GL_ERROR_DEBUG();
    int i = static_cast<int>(side);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
        0,                  // level
        GL_RGBA,            // internal format
        _size,              // width
        _size,              // height
        0,                  // border
        _textureInfo.internalFormat,            // format
        _textureInfo.type,  // type
        data);              // pixel data
    CHECK_GL_ERROR_DEBUG();
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void TextureCubeGL::getBytes(int x, int y, int width, int height, TextureFormat format, bool flipImage, std::function<void(const unsigned char* imageRGBA)> callback)
{
    GLint defaultFBO = 0;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &defaultFBO);
    GLuint frameBuffer = 0;
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureInfo.texture, 0);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);

    unsigned char* imageRGBA = new unsigned char[width * height * 4];
    glReadPixels(x,y,width, height,GL_RGBA,GL_UNSIGNED_BYTE, imageRGBA);

    if(flipImage)
    {
        unsigned char* flippedImage = new unsigned char[width * height *4];
        for (int i = 0; i < height; ++i)
        {
            memcpy(&flippedImage[i * width * 4],
                   &imageRGBA[(height - i - 1) * width * 4],
                   width * 4);
        }
        callback(flippedImage);
        CC_SAFE_DELETE_ARRAY(flippedImage);
    } else
    {
        callback(imageRGBA);
        CC_SAFE_DELETE_ARRAY(imageRGBA);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, defaultFBO);
    glDeleteFramebuffers(1, &frameBuffer);
}

CC_BACKEND_END
