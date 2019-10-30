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
 
#include "TextureMTL.h"
#include "Utils.h"
#include "base/ccMacros.h"

CC_BACKEND_BEGIN

namespace
{
    MTLSamplerAddressMode toMTLSamplerAddressMode(SamplerAddressMode mode)
    {
        MTLSamplerAddressMode ret = MTLSamplerAddressModeRepeat;
        switch (mode) {
            case SamplerAddressMode::REPEAT:
                ret = MTLSamplerAddressModeRepeat;
                break;
            case SamplerAddressMode::MIRROR_REPEAT:
                ret = MTLSamplerAddressModeMirrorRepeat;
                break;
            case SamplerAddressMode::CLAMP_TO_EDGE:
                ret = MTLSamplerAddressModeClampToEdge;
                break;
            default:
                CCASSERT(false, "Not supported sampler address mode!");
                break;
        }
        return ret;
    }
    
    MTLSamplerMinMagFilter toMTLSamplerMinMagFilter(SamplerFilter mode)
    {
        switch (mode) {
            case SamplerFilter::NEAREST:
            case SamplerFilter::NEAREST_MIPMAP_LINEAR:
            case SamplerFilter::NEAREST_MIPMAP_NEAREST:
                return MTLSamplerMinMagFilterNearest;
            case SamplerFilter::LINEAR:
            case SamplerFilter::LINEAR_MIPMAP_LINEAR:
            case SamplerFilter::LINEAR_MIPMAP_NEAREST:
                return MTLSamplerMinMagFilterLinear;
            case SamplerFilter::DONT_CARE:
                return MTLSamplerMinMagFilterNearest;
        }
    }
    
    void convertRGB2RGBA(uint8_t* src, uint8_t* dst, std::size_t length)
    {
        for (std::size_t i = 0; i < length; ++i)
        {
            *dst++ = *src++;
            *dst++ = *src++;
            *dst++ = *src++;
            *dst++ = 255;
        }
    }

    
    bool convertData(uint8_t* src, std::size_t length, PixelFormat format, uint8_t** out)
    {
        *out = src;
        bool converted = false;
        switch (format)
        {
            case PixelFormat::RGB888:
                {
                    *out = (uint8_t*)malloc(length * 4);
                    convertRGB2RGBA(src, *out, length);
                    converted = true;
                }
                break;
            default:
                break;
        }
        return converted;
    }
    
    bool isColorRenderable(PixelFormat textureFormat)
    {
        switch (textureFormat)
        {
            case PixelFormat::RGBA8888:
            case PixelFormat::RGB888:
            case PixelFormat::RGBA4444:
            case PixelFormat::RGB565:
            case PixelFormat::RGB5A1:
            case PixelFormat::MTL_BGR5A1:
            case PixelFormat::MTL_B5G6R5:
            case PixelFormat::MTL_ABGR4:
                return true;
            default:
                return false;
        }
    }
    
    std::size_t getBytesPerRowETC(MTLPixelFormat pixleFormat, std::size_t width)
    {
        std::size_t bytesPerRow = 0;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        uint32_t bytesPerBlock = 0, blockWidth = 4;
        switch (pixleFormat) {
            case MTLPixelFormatETC2_RGB8:
            case MTLPixelFormatETC2_RGB8A1:
            case MTLPixelFormatEAC_R11Unorm:
                bytesPerBlock = 8;
                break;
            case MTLPixelFormatEAC_RGBA8:
            case MTLPixelFormatEAC_RG11Unorm:
                bytesPerBlock = 16;
                break;
            default:
                CCASSERT(false, "Not supported ETC format!");
                break;
        }
        auto blocksPerRow = (width + (blockWidth - 1)) / blockWidth;
        bytesPerRow = blocksPerRow * bytesPerBlock;
#endif
        return bytesPerRow;
    }
    
    std::size_t getBytesPerRowS3TC(MTLPixelFormat pixleFormat, std::size_t width)
    {
        std::size_t bytesPerRow = 0;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        uint32_t bytesPerBlock = 0, blockWidth = 4;
        switch (pixleFormat) {
            case MTLPixelFormatBC1_RGBA:
                bytesPerBlock = 8;
                break;
            case MTLPixelFormatBC2_RGBA:
            case MTLPixelFormatBC3_RGBA:
                bytesPerBlock = 16;
                break;
            default:
                break;
        }
        auto blocksPerRow = (width + (blockWidth - 1)) / blockWidth;
        bytesPerRow = blocksPerRow * bytesPerBlock;
#endif
        return bytesPerRow;
    }
    
    std::size_t getBytesPerRow(PixelFormat textureFormat, std::size_t width, std::size_t bitsPerElement)
    {
        MTLPixelFormat pixelFormat = Utils::toMTLPixelFormat(textureFormat);
        std::size_t bytesPerRow = 0;
        
        if(textureFormat >= PixelFormat::PVRTC4 &&
           textureFormat <= PixelFormat::PVRTC2A)
        {
            bytesPerRow = 0;
        }
        else if (textureFormat == PixelFormat::ETC)
        {
            bytesPerRow = getBytesPerRowETC(pixelFormat, width);
        }
        else if(textureFormat >= PixelFormat::S3TC_DXT1 &&
                textureFormat <= PixelFormat::S3TC_DXT5)
        {
            bytesPerRow = getBytesPerRowS3TC(pixelFormat, width);
        }
        else
        {
            bytesPerRow = width * bitsPerElement / 8;
        }
        return bytesPerRow;
    }
}

TextureMTL::TextureMTL(id<MTLDevice> mtlDevice, const TextureDescriptor& descriptor)
: backend::Texture2DBackend(descriptor)
{
    _mtlDevice = mtlDevice;
    updateTextureDescriptor(descriptor);
}

TextureMTL::~TextureMTL()
{
    [_mtlTexture release];
    [_mtlSamplerState release];
}

void TextureMTL::updateSamplerDescriptor(const SamplerDescriptor &sampler)
{
    createSampler(_mtlDevice, sampler);
}

void TextureMTL::updateTextureDescriptor(const cocos2d::backend::TextureDescriptor &descriptor)
{
    TextureBackend::updateTextureDescriptor(descriptor);
    createTexture(_mtlDevice, descriptor);
    updateSamplerDescriptor(descriptor.samplerDescriptor);
    if (PixelFormat::RGB888 == _textureFormat)
    {
        _bitsPerElement = 4 * 8;
    }
    
    _bytesPerRow = descriptor.width * _bitsPerElement / 8 ;
}

void TextureMTL::updateData(uint8_t* data, std::size_t width , std::size_t height, std::size_t level)
{
    updateSubData(0, 0, width, height, level, data);
}

void TextureMTL::updateSubData(std::size_t xoffset, std::size_t yoffset, std::size_t width, std::size_t height, std::size_t level, uint8_t* data)
{
    MTLRegion region =
    {
        {xoffset, yoffset, 0},  // MTLOrigin
        {width, height, 1}      // MTLSize
    };
    
    uint8_t* convertedData = nullptr;
    bool converted = convertData(data,
                                 width * height,
                                 _textureFormat, &convertedData);
    
    std::size_t bytesPerRow = getBytesPerRow(_textureFormat, width, _bitsPerElement);
    
    [_mtlTexture replaceRegion:region
                   mipmapLevel:level
                     withBytes:convertedData
                   bytesPerRow:bytesPerRow];
    
    if (converted)
        free(convertedData);
    
    if(!_hasMipmaps && level > 0)
        _hasMipmaps = true;
}

void TextureMTL::updateCompressedData(uint8_t *data, std::size_t width, std::size_t height, std::size_t dataLen, std::size_t level)
{
    updateCompressedSubData(0, 0, width, height, dataLen, level, data);
}

void TextureMTL::updateCompressedSubData(std::size_t xoffset, std::size_t yoffset, std::size_t width, std::size_t height, std::size_t dataLen, std::size_t level, uint8_t *data)
{
    updateSubData(xoffset, yoffset, width, height, level, data);
}

void TextureMTL::createTexture(id<MTLDevice> mtlDevice, const TextureDescriptor& descriptor)
{
    MTLPixelFormat pixelFormat = Utils::toMTLPixelFormat(descriptor.textureFormat);
    if(pixelFormat == MTLPixelFormatInvalid)
        return;
    
    MTLTextureDescriptor* textureDescriptor =
           [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:pixelFormat
                                                              width:descriptor.width
                                                             height:descriptor.height
                                                          mipmapped:YES];
    
    if (TextureUsage::RENDER_TARGET == descriptor.textureUsage)
    {
        //DepthStencil, and Multisample textures must be allocated with the MTLResourceStorageModePrivate resource option
        if(PixelFormat::D24S8 == descriptor.textureFormat)
            textureDescriptor.resourceOptions = MTLResourceStorageModePrivate;
        textureDescriptor.usage = MTLTextureUsageRenderTarget | MTLTextureUsageShaderRead;
    }
    
    if(_mtlTexture)
        [_mtlTexture release];
    _mtlTexture = [mtlDevice newTextureWithDescriptor:textureDescriptor];
}

void TextureMTL::createSampler(id<MTLDevice> mtlDevice, const SamplerDescriptor &descriptor)
{
    MTLSamplerDescriptor *mtlDescriptor = [MTLSamplerDescriptor new];
    mtlDescriptor.sAddressMode = descriptor.sAddressMode == SamplerAddressMode::DONT_CARE ? _sAddressMode : toMTLSamplerAddressMode(descriptor.sAddressMode);
    mtlDescriptor.tAddressMode = descriptor.tAddressMode == SamplerAddressMode::DONT_CARE ? _tAddressMode : toMTLSamplerAddressMode(descriptor.tAddressMode);
    
    mtlDescriptor.minFilter = descriptor.minFilter == SamplerFilter::DONT_CARE ? _minFilter : toMTLSamplerMinMagFilter(descriptor.minFilter);
    mtlDescriptor.magFilter = descriptor.magFilter == SamplerFilter::DONT_CARE ? _magFilter : toMTLSamplerMinMagFilter(descriptor.magFilter);
    
    if(_mtlSamplerState)
    {
        [_mtlSamplerState release];
        _mtlSamplerState = nil;
    }
    
    _sAddressMode = mtlDescriptor.sAddressMode;
    _tAddressMode = mtlDescriptor.tAddressMode;
    _minFilter = mtlDescriptor.minFilter;
    _magFilter = mtlDescriptor.magFilter;
    _mipFilter = mtlDescriptor.mipFilter;
    
    _mtlSamplerState = [mtlDevice newSamplerStateWithDescriptor:mtlDescriptor];
    
    [mtlDescriptor release];
}

void TextureMTL::getBytes(std::size_t x, std::size_t y, std::size_t width, std::size_t height, bool flipImage, std::function<void(const unsigned char*, std::size_t, std::size_t)> callback)
{
    CC_ASSERT(width <= _width && height <= _height);
    
    auto bitsPerElement = _bitsPerElement;
    auto flipImageFunc = [callback, flipImage, bitsPerElement](const unsigned char* image, int width, int height){
        //consistent with opengl behavior
        auto bytePerRow = width * bitsPerElement / 8;
        if(!flipImage)
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
        }
        else
        {
            callback(image, width, height);
        }
    };
    auto flipImageCallback = std::bind(flipImageFunc, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    Utils::getTextureBytes(x, y, width, height, _mtlTexture, flipImageCallback);
}

void TextureMTL::generateMipmaps()
{
    if (TextureUsage::RENDER_TARGET == _textureUsage || isColorRenderable(_textureFormat) == false)
        return;
    
    if(!_hasMipmaps)
    {
        _hasMipmaps = true;
        Utils::generateMipmaps(_mtlTexture);
        
    }
}

TextureCubeMTL::TextureCubeMTL(id<MTLDevice> mtlDevice, const TextureDescriptor& descriptor)
: backend::TextureCubemapBackend(descriptor)
{
    _mtlDevice = mtlDevice;
    updateTextureDescriptor(descriptor);
}

TextureCubeMTL::~TextureCubeMTL()
{
    [_mtlTexture release];
    [_mtlSamplerState release];
}

void TextureCubeMTL::updateTextureDescriptor(const cocos2d::backend::TextureDescriptor &descriptor)
{
    TextureBackend::updateTextureDescriptor(descriptor);
    createTexture(_mtlDevice, descriptor);
    updateSamplerDescriptor(descriptor.samplerDescriptor);
    
    // Metal doesn't support RGB888/RGBA4444, so should convert to RGBA888;
    if (PixelFormat::RGB888 == _textureFormat)
    {
        _bitsPerElement = 4 * 8;
    }
    
    _bytesPerRow = descriptor.width * _bitsPerElement / 8 ;
    _bytesPerImage = _bytesPerRow * descriptor.width;
    _region = MTLRegionMake2D(0, 0, descriptor.width, descriptor.height);
}

void TextureCubeMTL::createTexture(id<MTLDevice> mtlDevice, const TextureDescriptor& descriptor)
{
    MTLPixelFormat pixelFormat = Utils::toMTLPixelFormat(descriptor.textureFormat);
    if(pixelFormat == MTLPixelFormatInvalid)
        return;
    
    MTLTextureDescriptor* textureDescriptor =
    [MTLTextureDescriptor textureCubeDescriptorWithPixelFormat:pixelFormat size:descriptor.width mipmapped:YES];
    
    if (TextureUsage::RENDER_TARGET == descriptor.textureUsage)
    {
        textureDescriptor.resourceOptions = MTLResourceStorageModePrivate;
        textureDescriptor.usage = MTLTextureUsageRenderTarget | MTLTextureUsageShaderRead;
    }
    
    if(_mtlTexture)
        [_mtlTexture release];
    _mtlTexture = [mtlDevice newTextureWithDescriptor:textureDescriptor];
}

void TextureCubeMTL::createSampler(id<MTLDevice> mtlDevice, const SamplerDescriptor &descriptor)
{
    MTLSamplerDescriptor *mtlDescriptor = [MTLSamplerDescriptor new];
    mtlDescriptor.sAddressMode = descriptor.sAddressMode == SamplerAddressMode::DONT_CARE ? _sAddressMode : toMTLSamplerAddressMode(descriptor.sAddressMode);
    mtlDescriptor.tAddressMode = descriptor.tAddressMode == SamplerAddressMode::DONT_CARE ? _tAddressMode : toMTLSamplerAddressMode(descriptor.tAddressMode);
    
    mtlDescriptor.minFilter = descriptor.minFilter == SamplerFilter::DONT_CARE ? _minFilter : toMTLSamplerMinMagFilter(descriptor.minFilter);
    mtlDescriptor.magFilter = descriptor.magFilter == SamplerFilter::DONT_CARE ? _magFilter : toMTLSamplerMinMagFilter(descriptor.magFilter);
    
    if(_mtlSamplerState)
    {
        [_mtlSamplerState release];
        _mtlSamplerState = nil;
    }
    
    _sAddressMode = mtlDescriptor.sAddressMode;
    _tAddressMode = mtlDescriptor.tAddressMode;
    _minFilter = mtlDescriptor.minFilter;
    _magFilter = mtlDescriptor.magFilter;
    _mipFilter = mtlDescriptor.mipFilter;
    
    _mtlSamplerState = [mtlDevice newSamplerStateWithDescriptor:mtlDescriptor];
    
    [mtlDescriptor release];
}

void TextureCubeMTL::updateSamplerDescriptor(const SamplerDescriptor &sampler)
{
    createSampler(_mtlDevice, sampler);
}

void TextureCubeMTL::updateFaceData(TextureCubeFace side, void *data)
{
    NSUInteger slice = static_cast<int>(side);
    [_mtlTexture replaceRegion:_region
                   mipmapLevel:0
                         slice:slice
                     withBytes:data
                   bytesPerRow:_bytesPerRow
                 bytesPerImage:_bytesPerImage];
}

void TextureCubeMTL::getBytes(std::size_t x, std::size_t y, std::size_t width, std::size_t height, bool flipImage, std::function<void(const unsigned char*, std::size_t, std::size_t)> callback)
{
    CC_ASSERT(width <= _mtlTexture.width && height <= _mtlTexture.height);
    
    auto bitsPerElement = _bitsPerElement;
    auto flipImageFunc = [callback, flipImage, bitsPerElement](const unsigned char* image, int width, int height){
        //consistent with opengl behavior
        auto bytePerRow = width * bitsPerElement / 8;
        if(!flipImage)
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
        }
        else
        {
            callback(image, width, height);
        }
    };
    auto flipImageCallback = std::bind(flipImageFunc, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    Utils::getTextureBytes(x, y, width, height, _mtlTexture, flipImageCallback);
}

void TextureCubeMTL::generateMipmaps()
{
    if (TextureUsage::RENDER_TARGET == _textureUsage || isColorRenderable(_textureFormat) == false)
        return;
    
    if(!_hasMipmaps)
    {
        _hasMipmaps = true;
        Utils::generateMipmaps(_mtlTexture);
    }
}

CC_BACKEND_END
