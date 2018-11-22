#pragma once

#include "../Texture.h"
#include "platform/CCGL.h"

CC_BACKEND_BEGIN

#define ISPOW2(n) (((n)&(n-1)) == 0)

class TextureGL : public Texture
{
public:
    TextureGL(const TextureDescriptor& descriptor);
    ~TextureGL();
    
    virtual void updateData(uint8_t* data) override;
    virtual void updateSubData(uint32_t xoffset, uint32_t yoffset, uint32_t width, uint32_t height, uint8_t* data) override;
    
    void apply(int index) const;
    inline GLuint getHandler() const { return _texture; }
    void setAlphaTexture(Texture* alphaTexture);
    inline void setPreMultiplyAlpha(bool bhasPremultipliedAlpha){_hasPremultipliedAlpha = bhasPremultipliedAlpha;}
    inline bool hasPremultipliedAlpha(){return _hasPremultipliedAlpha;}
    inline void setTextureID(GLuint texID){_texture = texID;}
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
    
    Texture* _alphaTexture = nullptr;
    bool _hasPremultipliedAlpha = false;
};

CC_BACKEND_END
