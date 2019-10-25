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
 
#pragma once

#include "../Texture.h"
#include "platform/CCGL.h"
#include "base/CCEventListenerCustom.h"

CC_BACKEND_BEGIN

/**
 * Store texture information.
 */
struct TextureInfoGL
{
    void applySamplerDescriptor(const SamplerDescriptor &desc, bool isPow2, bool hasMipmaps);

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

/**
 * @addtogroup _opengl
 * @{
 */

/**
 * A 2D texture
 */
class Texture2DGL : public backend::Texture2DBackend
{
public:
    /**
     * @param descirptor Specifies the texture description.
     */
    Texture2DGL(const TextureDescriptor& descriptor);
    ~Texture2DGL();
    
    /**
     * Update a two-dimensional texture image
     * @param data Specifies a pointer to the image data in memory.
     * @param width Specifies the width of the texture image.
     * @param height Specifies the height of the texture image.
     * @param level Specifies the level-of-detail number. Level 0 is the base image level. Level n is the nth mipmap reduction image.
     */
    virtual void updateData(uint8_t* data, std::size_t width , std::size_t height, std::size_t level) override;
    
    /**
     * Update a two-dimensional texture image in a compressed format
     * @param data Specifies a pointer to the compressed image data in memory.
     * @param width Specifies the width of the texture image.
     * @param height Specifies the height of the texture image.
     * @param dataLen Specifies the totoal size of compressed image in bytes.
     * @param level Specifies the level-of-detail number. Level 0 is the base image level. Level n is the nth mipmap reduction image.
     */
    virtual void updateCompressedData(uint8_t* data, std::size_t width , std::size_t height, std::size_t dataLen, std::size_t level) override;
    
    /**
     * Update a two-dimensional texture subimage
     * @param xoffset Specifies a texel offset in the x direction within the texture array.
     * @param yoffset Specifies a texel offset in the y direction within the texture array.
     * @param width Specifies the width of the texture subimage.
     * @param height Specifies the height of the texture subimage.
     * @param level Specifies the level-of-detail number. Level 0 is the base image level. Level n is the nth mipmap reduction image.
     * @param data Specifies a pointer to the image data in memory.
     */
    virtual void updateSubData(std::size_t xoffset, std::size_t yoffset, std::size_t width, std::size_t height, std::size_t level, uint8_t* data) override;
    
    /**
     * Update a two-dimensional texture subimage in a compressed format
     * @param xoffset Specifies a texel offset in the x direction within the texture array.
     * @param yoffset Specifies a texel offset in the y direction within the texture array.
     * @param width Specifies the width of the texture subimage.
     * @param height Specifies the height of the texture subimage.
     * @param dataLen Specifies the totoal size of compressed subimage in bytes.
     * @param level Specifies the level-of-detail number. Level 0 is the base image level. Level n is the nth mipmap reduction image.
     * @param data Specifies a pointer to the compressed image data in memory.
     */
    virtual void updateCompressedSubData(std::size_t xoffset, std::size_t yoffset, std::size_t width, std::size_t height, std::size_t dataLen, std::size_t level, uint8_t* data) override;
    
    /**
     * Update sampler
     * @param sampler Specifies the sampler descriptor.
     */
    virtual void updateSamplerDescriptor(const SamplerDescriptor &sampler)  override;
    
    /**
     * Read a block of pixels from the drawable texture
     * @param x,y Specify the window coordinates of the first pixel that is read from the drawable texture. This location is the lower left corner of a rectangular block of pixels.
     * @param width,height Specify the dimensions of the pixel rectangle. width and height of one correspond to a single pixel.
     * @param flipImage Specifies if needs to flip the image.
     * @param callback Specifies a call back function to deal with the image.
     */
    virtual void getBytes(std::size_t x, std::size_t y, std::size_t width, std::size_t height, bool flipImage, std::function<void(const unsigned char*, std::size_t, std::size_t)> callback) override;
    
    /**
     * Generate mipmaps.
     */
    virtual void generateMipmaps() override;

    /**
     * Update texture description.
     * @param descriptor Specifies texture and sampler descriptor.
     */
    virtual void updateTextureDescriptor(const TextureDescriptor& descriptor) override;

    /**
     * Get texture object.
     * @return Texture object.
     */
    inline GLuint getHandler() const { return _textureInfo.texture; }

    /**
     * Set texture to pipeline
     * @param index Specifies the texture image unit selector.
     */
    void apply(int index) const;

private:
    void initWithZeros();

    TextureInfoGL _textureInfo;
    EventListener* _backToForegroundListener = nullptr;
};

/**
 * Texture cube.
 */
class TextureCubeGL: public backend::TextureCubemapBackend
{
public:
    /**
     * @param descirptor Specifies the texture description.
     */
    TextureCubeGL(const TextureDescriptor& descriptor);
    ~TextureCubeGL();
    
    /**
     * Update sampler
     * @param sampler Specifies the sampler descriptor.
     */
    virtual void updateSamplerDescriptor(const SamplerDescriptor &sampler) override;
    
    /**
     * Update texutre cube data in give slice side.
     * @param side Specifies which slice texture of cube to be update.
     * @param data Specifies a pointer to the image data in memory.
     */
    virtual void updateFaceData(TextureCubeFace side, void *data) override;
    
    /**
     * Read a block of pixels from the drawable texture
     * @param x,y Specify the window coordinates of the first pixel that is read from the drawable texture. This location is the lower left corner of a rectangular block of pixels.
     * @param width,height Specify the dimensions of the pixel rectangle. width and height of one correspond to a single pixel.
     * @param flipImage Specifies if needs to flip the image.
     * @param callback
     */
    virtual void getBytes(std::size_t x, std::size_t y, std::size_t width, std::size_t height, bool flipImage, std::function<void(const unsigned char*, std::size_t, std::size_t)> callback) override;
    
    /// Generate mipmaps.
    virtual void generateMipmaps() override;

    /**
     * Update texture description.
     * @param descriptor Specifies texture and sampler descriptor.
     */
    virtual void updateTextureDescriptor(const TextureDescriptor& descriptor) override ;

    /**
     * Get texture object.
     * @return Texture object.
     */
    inline GLuint getHandler() const { return _textureInfo.texture; }

    /**
     * Set texture to pipeline
     * @param index Specifies the texture image unit selector.
     */
    void apply(int index) const;

private:
    void setTexParameters();

    TextureInfoGL _textureInfo;
    EventListener* _backToForegroundListener = nullptr;
};

//end of _opengl group
/// @}
CC_BACKEND_END
