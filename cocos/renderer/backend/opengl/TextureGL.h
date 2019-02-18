#pragma once

#include "../Texture.h"
#include "platform/CCGL.h"

CC_BACKEND_BEGIN

class TextureGL : public Texture
{
public:
    inline GLuint getHandler() const { return _texture; }
    virtual void apply(int index) const = 0;

protected:
    TextureGL(const TextureDescriptor& descriptor) : Texture(descriptor)
    {}
    void toGLSamplerDescriptor(const SamplerDescriptor &desc, bool isPow2);

    GLint _magFilterGL = GL_LINEAR;
    GLint _minFilterGL = GL_LINEAR;
    GLint _sAddressModeGL = GL_REPEAT;
    GLint _tAddressModeGL = GL_REPEAT;
    GLuint _texture = 0;
};

class Texture2DGL : public TextureGL
{
public:
    Texture2DGL(const TextureDescriptor& descriptor);
    ~Texture2DGL();
    
    virtual void updateData(uint8_t* data) override;
    virtual void updateSubData(unsigned int xoffset, unsigned int yoffset, unsigned int width, unsigned int height, uint8_t* data) override;
    virtual void updateSamplerDescriptor(const SamplerDescriptor &sampler)  override;
    virtual void apply(int index) const override;

private:
    virtual void updateFaceData(TextureCubeFace side, Texture2D::PixelFormat format, int width, int height, void *data) override
    {
        CCASSERT(false, "Texture2DGL should not implement `updateFaceData`");
    }

private:
    void toGLTypes();
    void generateMipmpas() const;
    
    SamplerDescriptor _samplerDescriptor;
    
    // Used in glTexImage2D().
    GLint _internalFormat = GL_RGBA;
    GLenum _format = GL_RGBA;
    GLenum _type = GL_UNSIGNED_BYTE;

    bool _isCompressed = false;
};

class TextureCubeGL : public TextureGL
{
public:
    TextureCubeGL(const TextureDescriptor& descriptor);
    ~TextureCubeGL();
    virtual void apply(int index) const override;
    virtual void updateSamplerDescriptor(const SamplerDescriptor &sampler) override;
    virtual void updateFaceData(TextureCubeFace side, Texture2D::PixelFormat format, int width, int height, void *data) override;
private:
    virtual void updateData(uint8_t* data) override 
    {
        CCASSERT(false, "TextureCubeGL should not implement `updateData`");
    }
    virtual void updateSubData(unsigned int xoffset, unsigned int yoffset, unsigned int width, unsigned int height, uint8_t* data) override
    {
        CCASSERT(false, "TextureCubeGL should not implement `updateSubData`");
    }

};

CC_BACKEND_END