#pragma once

#include "../Texture.h"
#include "platform/CCGL.h"

CC_BACKEND_BEGIN

class TextureInfoGL
{
public:
    void toGLSamplerDescriptor(const SamplerDescriptor &desc, bool isPow2);
    GLuint getHandler() { return _texture; }
protected:
    GLint _magFilterGL = GL_LINEAR;
    GLint _minFilterGL = GL_LINEAR;
    GLint _sAddressModeGL = GL_REPEAT;
    GLint _tAddressModeGL = GL_REPEAT;

    // Used in glTexImage2D().
    GLint _internalFormat = GL_RGBA;
    GLenum _format = GL_RGBA;
    GLenum _type = GL_UNSIGNED_BYTE;

    GLuint _texture = 0;
};

class Texture2DGL : public Texture2D, public TextureInfoGL
{
public:
    Texture2DGL(const TextureDescriptor& descriptor);
    ~Texture2DGL();
    
    virtual void updateData(uint8_t* data) override;
    virtual void updateSubData(unsigned int xoffset, unsigned int yoffset, unsigned int width, unsigned int height, uint8_t* data) override;
    virtual void updateSamplerDescriptor(const SamplerDescriptor &sampler)  override;
    void apply(int index) const;

private:
    void generateMipmpas() const;
    
    SamplerDescriptor _samplerDescriptor;
    bool _isCompressed = false;
    TextureInfoGL _info;
};

class TextureCubeGL: public TextureCubemap, public TextureInfoGL
{
public:
    TextureCubeGL(const TextureDescriptor& descriptor);
    ~TextureCubeGL();
    void apply(int index) const;
    virtual void updateSamplerDescriptor(const SamplerDescriptor &sampler) override;
    virtual void updateFaceData(TextureCubeFace side, int size, void *data) override;
private:
    TextureInfoGL _info;
};

CC_BACKEND_END