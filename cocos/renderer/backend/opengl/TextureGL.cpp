#include "TextureGL.h"
#include "base/ccMacros.h"
#include "platform/CCPlatformConfig.h"
#include "renderer/backend/opengl/UtilsGL.h"
CC_BACKEND_BEGIN

#define ISPOW2(n) (((n) & (n-1)) == 0)

void TextureInfoGL::applySamplerDescriptor(const SamplerDescriptor& descriptor, bool isPow2)
{
    if (descriptor.magFilter != SamplerFilter::DONT_CARE)
    {
        magFilterGL = UtilsGL::toGLMagFilter(descriptor.magFilter);
    }

    if (descriptor.minFilter != SamplerFilter::DONT_CARE)
    {
        minFilterGL = UtilsGL::toGLMinFilter(descriptor.minFilter, descriptor.mipmapFilter, descriptor.mipmapEnabled, isPow2);
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

Texture2DGL::Texture2DGL(const TextureDescriptor& descriptor) : Texture2D(descriptor)
{
    glGenTextures(1, &_textureInfo.texture);
    UtilsGL::toGLTypes(_textureFormat, _textureInfo.internalFormat, _textureInfo.format, _textureInfo.type, _isCompressed);

    bool isPow2 = ISPOW2(_width) && ISPOW2(_height);
    _textureInfo.magFilterGL = UtilsGL::toGLMagFilter(descriptor.samplerDescriptor.magFilter);
    _textureInfo.minFilterGL = UtilsGL::toGLMinFilter(descriptor.samplerDescriptor.minFilter,
                                 descriptor.samplerDescriptor.mipmapFilter, _isMipmapEnabled, isPow2);
    
    _textureInfo.sAddressModeGL = UtilsGL::toGLAddressMode(descriptor.samplerDescriptor.sAddressMode, isPow2);
    _textureInfo.tAddressModeGL = UtilsGL::toGLAddressMode(descriptor.samplerDescriptor.tAddressMode, isPow2);
   
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

    if (needGenerateMipmap) generateMipmaps();
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

    if(_isMipmapEnabled)
    {
        _isMipmapGenerated = false;
        generateMipmaps();
    }
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

    if(_isMipmapEnabled)
    {
        _isMipmapGenerated = false;
        generateMipmaps();
    }
    CHECK_GL_ERROR_DEBUG();
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

    if(!_isMipmapGenerated)
    {
        _isMipmapGenerated = true;
        glGenerateMipmap(GL_TEXTURE_2D);
    }
}

void Texture2DGL::getBytes(int x, int y, int width, int height, bool flipImage, std::function<void(const unsigned char*)> callback)
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
        callback(flippedImage);
        CC_SAFE_DELETE_ARRAY(flippedImage);
    } else
    {
        callback(image);
        CC_SAFE_DELETE_ARRAY(image);
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
    UtilsGL::toGLTypes(_textureFormat, _textureInfo.internalFormat, _textureInfo.format, _textureInfo.type, _isCompressed);
    glGenTextures(1, &_textureInfo.texture);
    updateSamplerDescriptor(descriptor.samplerDescriptor);
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

    bool needGenerateMipmap = !_isMipmapEnabled && sampler.mipmapEnabled;
    _isMipmapEnabled = sampler.mipmapEnabled;
    if (needGenerateMipmap)
        generateMipmaps();

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
    if(_isMipmapEnabled)
    {
        _isMipmapGenerated = false;
        generateMipmaps();
    }
    CHECK_GL_ERROR_DEBUG();
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void TextureCubeGL::getBytes(int x, int y, int width, int height, bool flipImage, std::function<void(const unsigned char*)> callback)
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
        callback(flippedImage);
        CC_SAFE_DELETE_ARRAY(flippedImage);
    } else
    {
        callback(image);
        CC_SAFE_DELETE_ARRAY(image);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, defaultFBO);
    glDeleteFramebuffers(1, &frameBuffer);
}

void TextureCubeGL::generateMipmaps()
{
    if (TextureUsage::RENDER_TARGET == _textureUsage)
        return;

    if(!_isMipmapGenerated)
    {
        _isMipmapGenerated = true;
        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    }
}

CC_BACKEND_END
