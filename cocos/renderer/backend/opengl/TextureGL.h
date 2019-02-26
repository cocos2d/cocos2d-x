#pragma once

#include "../Texture.h"
#include "platform/CCGL.h"

CC_BACKEND_BEGIN

struct TextureInfoGL
{
    void applySamplerDescriptor(const SamplerDescriptor &desc, bool isPow2);

    GLint magFilterGL = GL_LINEAR;
    GLint minFilterGL = GL_LINEAR;
    GLint sAddressModeGL = GL_REPEAT;
    GLint tAddressModeGL = GL_REPEAT;

    // Used in glTexImage2D().
    GLint internalFormat = GL_RGBA;
    GLenum format = GL_RGBA;
    GLenum type = GL_UNSIGNED_BYTE;

    GLuint texture = 0;
};

class Texture2DGL : public backend::Texture2D
{
public:
    Texture2DGL(const TextureDescriptor& descriptor);
    ~Texture2DGL();
    
    virtual void updateData(uint8_t* data) override;
    virtual void updateSubData(unsigned int xoffset, unsigned int yoffset, unsigned int width, unsigned int height, uint8_t* data) override;
    virtual void updateSamplerDescriptor(const SamplerDescriptor &sampler)  override;
    virtual void getBytes(int x, int y, int width, int height, TextureFormat format, bool flipImage, std::function<void(const unsigned char* imageRGBA)> callback) override;

    void apply(int index) const;
    inline GLuint getHandler() const { return _textureInfo.texture; }

private:
    void generateMipmpas() const;
    
    SamplerDescriptor _samplerDescriptor;
    bool _isCompressed = false;
    TextureInfoGL _textureInfo;
};

class TextureCubeGL: public backend::TextureCubemap
{
public:
    TextureCubeGL(const TextureDescriptor& descriptor);
    ~TextureCubeGL();
    
    virtual void updateSamplerDescriptor(const SamplerDescriptor &sampler) override;
    virtual void updateFaceData(TextureCubeFace side, void *data) override;
    virtual void getBytes(int x, int y, int width, int height, TextureFormat format, bool flipImage, std::function<void(const unsigned char* imageRGBA)> callback) override;
    
    void apply(int index) const;
    inline GLuint getHandler() const { return _textureInfo.texture; }

private:
    TextureInfoGL _textureInfo;
};

CC_BACKEND_END
