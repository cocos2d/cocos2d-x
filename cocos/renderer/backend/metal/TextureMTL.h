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
#include "DeviceMTL.h"
#import <Metal/Metal.h>

CC_BACKEND_BEGIN

class TextureMTL : public backend::Texture2DBackend
{
public:
    TextureMTL(id<MTLDevice> mtlDevice, const TextureDescriptor& descriptor);
    ~TextureMTL();
    
    virtual void updateData(uint8_t* data, uint32_t width , uint32_t height, uint32_t level) override;
    virtual void updateCompressedData(uint8_t* data, uint32_t width , uint32_t height, uint32_t dataLen, uint32_t level) override;
    virtual void updateSubData(uint32_t xoffset, uint32_t yoffset, uint32_t width, uint32_t height, uint32_t level, uint8_t* data) override;
    virtual void updateCompressedSubData(uint32_t xoffset, uint32_t yoffset, uint32_t width, uint32_t height, uint32_t dataLen, uint32_t level, uint8_t* data) override;
    
    virtual void updateSamplerDescriptor(const SamplerDescriptor &sampler) override;
    virtual void getBytes(int x, int y, int width, int height, bool flipImage, std::function<void(const unsigned char*, int, int)> callback) override;
    virtual void generateMipmaps() override;
    virtual void updateTextureDescriptor(const cocos2d::backend::TextureDescriptor &descriptor) override;
    
    inline id<MTLTexture> getMTLTexture() const { return _mtlTexture; }
    inline id<MTLSamplerState> getMTLSamplerState() const { return _mtlSamplerState; }
    
private:
    void createTexture(id<MTLDevice> mtlDevice, const TextureDescriptor& descriptor);
    void createSampler(id<MTLDevice> mtlDevice, const SamplerDescriptor& descriptor);
    
    MTLSamplerAddressMode _sAddressMode;
    MTLSamplerAddressMode _tAddressMode;
    MTLSamplerMinMagFilter _minFilter;
    MTLSamplerMinMagFilter _magFilter;
    MTLSamplerMipFilter _mipFilter;
    
    id<MTLDevice> _mtlDevice = nil;
    id<MTLTexture> _mtlTexture = nil;
    id<MTLSamplerState> _mtlSamplerState = nil;
    unsigned int _bytesPerRow = 0;
};

class TextureCubeMTL : public backend::TextureCubemapBackend
{
public:
    TextureCubeMTL(id<MTLDevice> mtlDevice, const TextureDescriptor& descriptor);
    ~TextureCubeMTL();
    
    virtual void updateSamplerDescriptor(const SamplerDescriptor &sampler) override;
    virtual void updateFaceData(TextureCubeFace side, void *data) override;
    virtual void getBytes(int x, int y, int width, int height, bool flipImage, std::function<void(const unsigned char*, int, int)> callback) override;
    virtual void generateMipmaps() override;
    virtual void updateTextureDescriptor(const cocos2d::backend::TextureDescriptor &descriptor) override;
    
    inline id<MTLTexture> getMTLTexture() const { return _mtlTexture; }
    inline id<MTLSamplerState> getMTLSamplerState() const { return _mtlSamplerState; }
    
private:
    void createTexture(id<MTLDevice> mtlDevice, const TextureDescriptor& descriptor);
    void createSampler(id<MTLDevice> mtlDevice, const SamplerDescriptor& descriptor);
    
    MTLSamplerAddressMode _sAddressMode;
    MTLSamplerAddressMode _tAddressMode;
    MTLSamplerMinMagFilter _minFilter;
    MTLSamplerMinMagFilter _magFilter;
    MTLSamplerMipFilter _mipFilter;
    
    id<MTLDevice> _mtlDevice = nil;
    id<MTLTexture> _mtlTexture = nil;
    id<MTLSamplerState> _mtlSamplerState = nil;
    MTLRegion _region;
    unsigned int _bytesPerImage = 0;
    unsigned int _bytesPerRow = 0;
};

CC_BACKEND_END
