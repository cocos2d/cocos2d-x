/****************************************************************************
 Copyright (c) 2018-2019 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
 
#include "TextureGL.h"
#include "base/ccMacros.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventType.h"
#include "base/CCDirector.h"
#include "platform/CCPlatformConfig.h"
#include "renderer/backend/opengl/UtilsGL.h"

CC_BACKEND_BEGIN

#define ISPOW2(n) (((n) & (n-1)) == 0)

namespace {
    bool isMipmapEnabled(GLint filter)
    {
        switch(filter)
        {
            case GL_LINEAR_MIPMAP_LINEAR:
            case GL_LINEAR_MIPMAP_NEAREST:
            case GL_NEAREST_MIPMAP_NEAREST:
            case GL_NEAREST_MIPMAP_LINEAR:
                return true;
            default:
                break;
        }
        return false;
    }
}

void TextureInfoGL::applySamplerDescriptor(const SamplerDescriptor& descriptor, bool isPow2, bool hasMipmaps)
{
    if (descriptor.magFilter != SamplerFilter::DONT_CARE)
    {
        magFilterGL = UtilsGL::toGLMagFilter(descriptor.magFilter);
    }

    if (descriptor.minFilter != SamplerFilter::DONT_CARE)
    {
        minFilterGL = UtilsGL::toGLMinFilter(descriptor.minFilter, hasMipmaps, isPow2);
    }

    if (descriptor.sAddressMode != SamplerAddressMode::DONT_CARE)
    {
        sAddressModeGL = UtilsGL::toGLAddressMode(descriptor.sAddressMode, isPow2);
    }

    if (descriptor.tAddressMode != SamplerAddressMode::DONT_CARE)
    {
        tAddressModeGL = UtilsGL::toGLAddressMode(descriptor.tAddressMode, isPow2);
    }
}

Texture2DGL::Texture2DGL(const TextureDescriptor& descriptor) : Texture2DBackend(descriptor)
{
    glGenTextures(1, &_textureInfo.texture);

    updateTextureDescriptor(descriptor);

#if CC_ENABLE_CACHE_TEXTURE_DATA
    // Listen this event to restored texture id after coming to foreground on Android.
    _backToForegroundListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom*){
        glGenTextures(1, &(this->_textureInfo.texture));
        this->initWithZeros();
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backToForegroundListener, -1);
#endif
}

void Texture2DGL::initWithZeros()
{
    auto size = _width * _height * _bitsPerElement / 8;
    uint8_t* data = (uint8_t*)malloc(size);
    memset(data, 0, size);
    updateData(data, _width, _height, 0);
    free(data);
}

void Texture2DGL::updateTextureDescriptor(const cocos2d::backend::TextureDescriptor &descriptor)
{
    TextureBackend::updateTextureDescriptor(descriptor);
    UtilsGL::toGLTypes(descriptor.textureFormat, _textureInfo.internalFormat, _textureInfo.format, _textureInfo.type, _isCompressed);

    bool isPow2 = ISPOW2(_width) && ISPOW2(_height);
    _textureInfo.magFilterGL = UtilsGL::toGLMagFilter(descriptor.samplerDescriptor.magFilter);
    _textureInfo.minFilterGL = UtilsGL::toGLMinFilter(descriptor.samplerDescriptor.minFilter, _hasMipmaps, isPow2);

    _textureInfo.sAddressModeGL = UtilsGL::toGLAddressMode(descriptor.samplerDescriptor.sAddressMode, isPow2);
    _textureInfo.tAddressModeGL = UtilsGL::toGLAddressMode(descriptor.samplerDescriptor.tAddressMode, isPow2);

    updateSamplerDescriptor(descriptor.samplerDescriptor);

    // Update data here because `updateData()` may not be invoked later.
    // For example, a texture used as depth buffer will not invoke updateData().
    initWithZeros();
}

Texture2DGL::~Texture2DGL()
{
    if (_textureInfo.texture)
        glDeleteTextures(1, &_textureInfo.texture);
    _textureInfo.texture = 0;
#if CC_ENABLE_CACHE_TEXTURE_DATA
    Director::getInstance()->getEventDispatcher()->removeEventListener(_backToForegroundListener);
#endif
}

void Texture2DGL::updateSamplerDescriptor(const SamplerDescriptor &sampler) {
    bool isPow2 = ISPOW2(_width) && ISPOW2(_height);
    _textureInfo.applySamplerDescriptor(sampler, isPow2, _hasMipmaps);

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
}

void Texture2DGL::updateData(uint8_t* data, std::size_t width , std::size_t height, std::size_t level)
{
    //Set the row align only when mipmapsNum == 1 and the data is uncompressed
    auto mipmapEnalbed = isMipmapEnabled(_textureInfo.minFilterGL) || isMipmapEnabled(_textureInfo.magFilterGL);
    if(!mipmapEnalbed)
    {
        unsigned int bytesPerRow = width * _bitsPerElement / 8;

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


    glTexImage2D(GL_TEXTURE_2D,
                level,
                _textureInfo.internalFormat,
                width,
                height,
                0,
                _textureInfo.format,
                _textureInfo.type,
                data);
    CHECK_GL_ERROR_DEBUG();

    if(!_hasMipmaps && level > 0)
        _hasMipmaps = true;
}

void Texture2DGL::updateCompressedData(uint8_t *data, std::size_t width, std::size_t height,
                                       std::size_t dataLen, std::size_t level)
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _textureInfo.texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _textureInfo.magFilterGL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _textureInfo.minFilterGL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _textureInfo.sAddressModeGL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _textureInfo.tAddressModeGL);


    glCompressedTexImage2D(GL_TEXTURE_2D,
                           level,
                           _textureInfo.internalFormat,
                           (GLsizei)width,
                           (GLsizei)height,
                           0,
                           dataLen,
                           data);
    CHECK_GL_ERROR_DEBUG();

    if(!_hasMipmaps && level > 0)
        _hasMipmaps = true;
}

void Texture2DGL::updateSubData(std::size_t xoffset, std::size_t yoffset, std::size_t width, std::size_t height, std::size_t level, uint8_t* data)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _textureInfo.texture);

    glTexSubImage2D(GL_TEXTURE_2D,
                    level,
                    xoffset,
                    yoffset,
                    width,
                    height,
                    _textureInfo.format,
                    _textureInfo.type,
                    data);
    CHECK_GL_ERROR_DEBUG();

    if(!_hasMipmaps && level > 0)
        _hasMipmaps = true;
}

void Texture2DGL::updateCompressedSubData(std::size_t xoffset, std::size_t yoffset, std::size_t width,
                                          std::size_t height, std::size_t dataLen, std::size_t level,
                                          uint8_t *data)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _textureInfo.texture);

    glCompressedTexSubImage2D(GL_TEXTURE_2D,
                              level,
                              xoffset,
                              yoffset,
                              width,
                              height,
                              _textureInfo.format,
                              dataLen,
                              data);
    CHECK_GL_ERROR_DEBUG();

    if(!_hasMipmaps && level > 0)
        _hasMipmaps = true;
}

void Texture2DGL::apply(int index) const
{
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, _textureInfo.texture);
}

void Texture2DGL::generateMipmaps()
{
    if (TextureUsage::RENDER_TARGET == _textureUsage)
        return;

    if(!_hasMipmaps)
    {
        _hasMipmaps = true;
        glBindTexture(GL_TEXTURE_2D, _textureInfo.texture);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
}

void Texture2DGL::getBytes(std::size_t x, std::size_t y, std::size_t width, std::size_t height, bool flipImage, std::function<void(const unsigned char*, std::size_t, std::size_t)> callback)
{
    GLint defaultFBO = 0;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &defaultFBO);

    GLuint frameBuffer = 0;
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureInfo.texture, 0);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);

    auto bytePerRow = width * _bitsPerElement / 8;
    unsigned char* image = new unsigned char[bytePerRow * height];
    glReadPixels(x,y,width, height,GL_RGBA,GL_UNSIGNED_BYTE, image);

    if(flipImage)
    {
        unsigned char* flippedImage = new unsigned char[bytePerRow * height];
        for (int i = 0; i < height; ++i)
        {
            memcpy(&flippedImage[i * bytePerRow],
                   &image[(height - i - 1) * bytePerRow],
                   bytePerRow);
        }
        callback(flippedImage, width, height);
        CC_SAFE_DELETE_ARRAY(flippedImage);
    } else
    {
        callback(image, width, height);
        CC_SAFE_DELETE_ARRAY(image);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, defaultFBO);
    glDeleteFramebuffers(1, &frameBuffer);
}

TextureCubeGL::TextureCubeGL(const TextureDescriptor& descriptor)
    :TextureCubemapBackend(descriptor)
{
    assert(_width == _height);
    _textureType = TextureType::TEXTURE_CUBE;
    UtilsGL::toGLTypes(_textureFormat, _textureInfo.internalFormat, _textureInfo.format, _textureInfo.type, _isCompressed);
    glGenTextures(1, &_textureInfo.texture);
    updateSamplerDescriptor(descriptor.samplerDescriptor);

#if CC_ENABLE_CACHE_TEXTURE_DATA
    // Listen this event to restored texture id after coming to foreground on Android.
    _backToForegroundListener = EventListenerCustom::create(EVENT_COME_TO_FOREGROUND, [this](EventCustom*){
        glGenTextures(1, &(this->_textureInfo.texture));
        this->setTexParameters();
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backToForegroundListener, -1);
#endif
    CHECK_GL_ERROR_DEBUG();
}

void TextureCubeGL::setTexParameters()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _textureInfo.texture);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, _textureInfo.minFilterGL);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, _textureInfo.magFilterGL);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, _textureInfo.sAddressModeGL);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, _textureInfo.tAddressModeGL);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void TextureCubeGL::updateTextureDescriptor(const cocos2d::backend::TextureDescriptor &descriptor)
{
    UtilsGL::toGLTypes(descriptor.textureFormat, _textureInfo.internalFormat, _textureInfo.format, _textureInfo.type, _isCompressed);
    _textureFormat = descriptor.textureFormat;
    updateSamplerDescriptor(descriptor.samplerDescriptor);
}

TextureCubeGL::~TextureCubeGL()
{
    if(_textureInfo.texture)
        glDeleteTextures(1, &_textureInfo.texture);
    _textureInfo.texture = 0;

#if CC_ENABLE_CACHE_TEXTURE_DATA
    Director::getInstance()->getEventDispatcher()->removeEventListener(_backToForegroundListener);
#endif
}

void TextureCubeGL::updateSamplerDescriptor(const SamplerDescriptor &sampler)
{
    _textureInfo.applySamplerDescriptor(sampler, true, _hasMipmaps);
    setTexParameters();
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
        _width,              // width
        _height,              // height
        0,                  // border
        _textureInfo.internalFormat,            // format
        _textureInfo.type,  // type
        data);              // pixel data

    CHECK_GL_ERROR_DEBUG();
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void TextureCubeGL::getBytes(std::size_t x, std::size_t y, std::size_t width, std::size_t height, bool flipImage, std::function<void(const unsigned char*, std::size_t, std::size_t)> callback)
{
    GLint defaultFBO = 0;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &defaultFBO);
    GLuint frameBuffer = 0;
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP, _textureInfo.texture, 0);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);

    auto bytePerRow = width * _bitsPerElement / 8;
    unsigned char* image = new unsigned char[bytePerRow * height];
    glReadPixels(x,y,width, height,GL_RGBA,GL_UNSIGNED_BYTE, image);

    if(flipImage)
    {
        unsigned char* flippedImage = new unsigned char[bytePerRow * height];
        for (int i = 0; i < height; ++i)
        {
            memcpy(&flippedImage[i * bytePerRow],
                   &image[(height - i - 1) * bytePerRow],
                   bytePerRow);
        }
        callback(flippedImage, width, height);
        CC_SAFE_DELETE_ARRAY(flippedImage);
    } else
    {
        callback(image, width, height);
        CC_SAFE_DELETE_ARRAY(image);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, defaultFBO);
    glDeleteFramebuffers(1, &frameBuffer);
}

void TextureCubeGL::generateMipmaps()
{
    if (TextureUsage::RENDER_TARGET == _textureUsage)
        return;

    if(!_hasMipmaps)
    {
        _hasMipmaps = true;
        glBindTexture(GL_TEXTURE_CUBE_MAP, _textureInfo.texture);
        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    }
}

CC_BACKEND_END
