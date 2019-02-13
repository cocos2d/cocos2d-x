#pragma once

#include "../Texture.h"
#include "platform/CCGL.h"

CC_BACKEND_BEGIN

class TextureGL : public Texture
{
public:
    TextureGL(const TextureDescriptor& descriptor) : Texture(descriptor)
    {}
    virtual void apply(int index) const = 0;
    inline GLuint getHandler() const { return _texture; }
    virtual void updateData(uint8_t* data) override 
    {
        //defaults to empty implementation
    }
    virtual void updateSubData(unsigned int xoffset, unsigned int yoffset, unsigned int width, unsigned int height, uint8_t* data) override
    {
        //defaults to empty implementation
    }
    virtual void updateSamplerDescriptor(const SamplerDescriptor &sampler)  override
    {
        //defaults to empty implementation
    }
protected:
    GLuint _texture = 0;
};

class Texture2DGL : public TextureGL
{
public:
    Texture2DGL(const TextureDescriptor& descriptor);
    virtual ~Texture2DGL();
    
    virtual void updateData(uint8_t* data) override;
    virtual void updateSubData(unsigned int xoffset, unsigned int yoffset, unsigned int width, unsigned int height, uint8_t* data) override;
    
    virtual void updateSamplerDescriptor(const SamplerDescriptor &sampler)  override;

    virtual void apply(int index) const override;
    
protected:
    void toGLTypes();
    void generateMipmpas() const;
    
    SamplerDescriptor _samplerDescriptor;
    
    GLint _magFilterGL = GL_LINEAR;
    GLint _minFilterGL = GL_LINEAR;
    GLint _sAddressModeGL = GL_REPEAT;
    GLint _tAddressModeGL = GL_REPEAT;
    
    // Used in glTexImage2D().
    GLint _internalFormat = GL_RGBA;
    GLenum _format = GL_RGBA;
    GLenum _type = GL_UNSIGNED_BYTE;

    bool _isCompressed = false;
};

class TextureCubeMapGL : public backend::TextureGL
{
public:
    TextureCubeMapGL(const TextureDescriptor& descriptor);
    virtual ~TextureCubeMapGL();
    virtual void apply(int index) const override;
    bool init(const std::string& positive_x, const std::string& negative_x,
        const std::string& positive_y, const std::string& negative_y,
        const std::string& positive_z, const std::string& negative_z);
};

CC_BACKEND_END
