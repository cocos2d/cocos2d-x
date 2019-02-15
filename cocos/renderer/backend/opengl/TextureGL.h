#pragma once

#include "../Texture.h"
#include "platform/CCGL.h"

CC_BACKEND_BEGIN

class TextureGL : public Texture
{
public:
    TextureGL(const TextureDescriptor& descriptor);
    ~TextureGL();
    
    virtual void updateData(uint8_t* data) override;
    virtual void updateSubData(unsigned int xoffset, unsigned int yoffset, unsigned int width, unsigned int height, uint8_t* data) override;
    
    virtual void updateSamplerDescriptor(const SamplerDescriptor &sampler)  override;

    void apply(int index) const;
    inline GLuint getHandler() const { return _texture; }
    
private:
    void toGLTypes();
    void generateMipmpas() const;
    
    GLuint _texture = 0;
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

CC_BACKEND_END
