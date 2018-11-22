#include "TextureGL.h"
#include "ccMacros.h"

CC_BACKEND_BEGIN

#define ISPOW2(n) (((n)&(n-1)) == 0)

namespace
{
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
    
    GLint toGLMinFilter(SamplerFilter minFilter, SamplerFilter mipmapFilter, bool mipmapEnabled, bool bPow2)
    {
        if (mipmapEnabled)
        {
            if(!bPow2)
            {
                cocos2d::log("Disable mipmap since non-power-of-two texture occur in %s %s %d", __FILE__, __FUNCTION__, __LINE__);
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
    
    GLint toGLAddressMode(SamplerAddressMode addressMode, bool bPow2)
    {
        GLint ret = GL_CLAMP_TO_EDGE;
        if(!bPow2)
            return ret;
        
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
    bool bPow2 = ISPOW2(_width) && ISPOW2(_height);
    _magFilterGL = toGLMagFilter(descriptor.samplerDescriptor.magFilter);
    _minFilterGL = toGLMinFilter(descriptor.samplerDescriptor.minFilter,
                                 descriptor.samplerDescriptor.mipmapFilter, _isMipmapEnabled, bPow2);
    
    _sAddressModeGL = toGLAddressMode(descriptor.samplerDescriptor.sAddressMode, bPow2);
    _tAddressModeGL = toGLAddressMode(descriptor.samplerDescriptor.tAddressMode, bPow2);
    
    // Update data here because `updateData()` may not be invoked later.
    // For example, a texture used as depth buffer will not invoke updateData().
    uint8_t* data = (uint8_t*)malloc(_width * _height * _bytesPerElement);
    updateData(data);
    free(data);
}

TextureGL::~TextureGL()
{
    if (_texture)
        glDeleteTextures(1, &_texture);
}

void TextureGL::updateData(uint8_t* data)
{
    // TODO: support texture cube, and compressed data.
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _magFilterGL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _minFilterGL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _sAddressModeGL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _tAddressModeGL);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 _internalFormat,
                 _width,
                 _height,
                 0,
                 _format,
                 _type,
                 data);
    CHECK_GL_ERROR_DEBUG();
    
    generateMipmpas();
    CHECK_GL_ERROR_DEBUG();
}

void TextureGL::updateSubData(uint32_t xoffset, uint32_t yoffset, uint32_t width, uint32_t height, uint8_t* data)
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
        case TextureFormat::A8:
            _internalFormat = GL_ALPHA;
            _format = GL_ALPHA;
            _type = GL_UNSIGNED_BYTE;
            break;
//        case TextureFormat::D16:
//            _format = GL_DEPTH_COMPONENT;
//            _internalFormat = GL_DEPTH_COMPONENT;
//            _type = GL_UNSIGNED_INT;
//        case TextureFormat::D24S8:
//            _format = GL_DEPTH_STENCIL_OES;
//            _internalFormat = GL_DEPTH_STENCIL_OES;
//            _type = GL_UNSIGNED_INT_24_8_OES;
//            break;
        default:
            break;
    }
}

/// halx99 spec, ANDROID ETC1 ALPHA supports.
void TextureGL::setAlphaTexture(Texture* alphaTexture)
{
    if (alphaTexture != nullptr) {
        this->_alphaTexture = alphaTexture;
        this->_alphaTexture->retain();
        this->_hasPremultipliedAlpha = true; // PremultipliedAlpha should be true.
    }
}


CC_BACKEND_END
