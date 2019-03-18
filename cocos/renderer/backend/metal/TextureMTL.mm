#include "TextureMTL.h"
#include "Utils.h"

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
                assert(false);
                break;
        }
        return ret;
    }
    
    MTLSamplerMinMagFilter toMTLSamplerMinMagFilter(SamplerFilter mode)
    {
        switch (mode) {
            case SamplerFilter::NEAREST:
                return MTLSamplerMinMagFilterNearest;
            case SamplerFilter::LINEAR:
                return MTLSamplerMinMagFilterLinear;
            case SamplerFilter::DONT_CARE:
                return MTLSamplerMinMagFilterNearest;
        }
    }
    
    MTLSamplerMipFilter toMTLSamplerMipFilter(SamplerFilter mode) {
        switch (mode) {
            case SamplerFilter::NEAREST:
                return MTLSamplerMipFilterNearest;
            case SamplerFilter::LINEAR:
                return MTLSamplerMipFilterLinear;
            case SamplerFilter::DONT_CARE:
                return MTLSamplerMipFilterNearest;
        }
    }
    
    void convertRGB2RGBA(uint8_t* src, uint8_t* dst, uint32_t length)
    {
        for (uint32_t i = 0; i < length; ++i)
        {
            *dst++ = *src++;
            *dst++ = *src++;
            *dst++ = *src++;
            *dst++ = 255;
        }
    }

    
    bool convertData(uint8_t* src, unsigned int length, TextureFormat format, uint8_t** out)
    {
        *out = src;
        bool converted = false;
        switch (format)
        {
            case TextureFormat::R8G8B8:
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
    
    bool isColorRenderable(TextureFormat textureFormat)
    {
        switch (textureFormat)
        {
            case TextureFormat::R8G8B8A8:
            case TextureFormat::R8G8B8:
            case TextureFormat::RGBA4444:
            case TextureFormat::RGB565:
            case TextureFormat::RGB5A1:
            case TextureFormat::MTL_BGR5A1:
            case TextureFormat::MTL_B5G6R5:
            case TextureFormat::MTL_ABGR4:
                return true;
            default:
                return false;
        }
    }
}

TextureMTL::TextureMTL(id<MTLDevice> mtlDevice, const TextureDescriptor& descriptor)
: backend::Texture2D(descriptor)
{
    _mtlDevice = mtlDevice;
    createTexture(mtlDevice, descriptor);
    createSampler(mtlDevice, descriptor.samplerDescriptor);
    
    // Metal doesn't support RGB888/RGBA4444, so should convert to RGBA888;
    if (TextureFormat::R8G8B8 == _textureFormat)
    {
        _bitsPerElement = 4 * 8;
    }
    
    _bytesPerRow = descriptor.width * _bitsPerElement / 8 ;
}

TextureMTL::~TextureMTL()
{
    [_mtlTexture release];
    [_mtlSamplerState release];
}

void TextureMTL::updateSamplerDescriptor(const SamplerDescriptor &sampler)
{
    createSampler(_mtlDevice, sampler);
    bool needGenerateMipmap = !_isMipmapEnabled && sampler.mipmapEnabled;
    _isMipmapEnabled = sampler.mipmapEnabled;
    if(needGenerateMipmap)
    {
        generateMipmaps();
    }
}

void TextureMTL::updateData(uint8_t* data)
{
    updateSubData(0, 0, (unsigned int)_mtlTexture.width, (unsigned int)_mtlTexture.height, data);
}

void TextureMTL::updateSubData(unsigned int xoffset, unsigned int yoffset, unsigned int width, unsigned int height, uint8_t* data)
{
    MTLRegion region =
    {
        {xoffset, yoffset, 0},  // MTLOrigin
        {width, height, 1}      // MTLSize
    };
    
    uint8_t* convertedData = nullptr;
    bool converted = convertData(data,
                                 (uint32_t)(width * height),
                                 _textureFormat, &convertedData);
    
    //when pixel format is a compressed one, bytePerRow should be set to ZERO
    int bytesPerRow = _isCompressed ? 0 : _bytesPerRow;
    
    [_mtlTexture replaceRegion:region
                   mipmapLevel:0
                     withBytes:convertedData
                   bytesPerRow:bytesPerRow];
    
    if (converted)
        free(convertedData);
    
    // metal doesn't generate mipmaps automatically, so should generate it manually.
    if (_isMipmapEnabled)
    {
        _isMipmapGenerated = false;
        generateMipmaps();
    }
}

void TextureMTL::createTexture(id<MTLDevice> mtlDevice, const TextureDescriptor& descriptor)
{
    MTLTextureDescriptor* textureDescriptor =
           [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:Utils::toMTLPixelFormat(descriptor.textureFormat)
                                                              width:descriptor.width
                                                             height:descriptor.height
                                                          mipmapped:YES];
    
    if (TextureUsage::RENDER_TARGET == descriptor.textureUsage)
    {
        textureDescriptor.resourceOptions = MTLResourceStorageModePrivate;
        textureDescriptor.usage = MTLTextureUsageRenderTarget | MTLTextureUsageShaderRead;
    }
    _mtlTexture = [mtlDevice newTextureWithDescriptor:textureDescriptor];
}

void TextureMTL::createSampler(id<MTLDevice> mtlDevice, const SamplerDescriptor &descriptor)
{
    MTLSamplerDescriptor *mtlDescriptor = [MTLSamplerDescriptor new];
    mtlDescriptor.sAddressMode = descriptor.sAddressMode == SamplerAddressMode::DONT_CARE ? _sAddressMode : toMTLSamplerAddressMode(descriptor.sAddressMode);
    mtlDescriptor.tAddressMode = descriptor.tAddressMode == SamplerAddressMode::DONT_CARE ? _tAddressMode : toMTLSamplerAddressMode(descriptor.tAddressMode);
    
    mtlDescriptor.minFilter = descriptor.minFilter == SamplerFilter::DONT_CARE ? _minFilter : toMTLSamplerMinMagFilter(descriptor.minFilter);
    mtlDescriptor.magFilter = descriptor.magFilter == SamplerFilter::DONT_CARE ? _magFilter : toMTLSamplerMinMagFilter(descriptor.magFilter);
    if (_isMipmapEnabled)
        mtlDescriptor.mipFilter = descriptor.mipmapFilter == SamplerFilter::DONT_CARE ? _mipFilter : toMTLSamplerMipFilter(descriptor.mipmapFilter);
    
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

void TextureMTL::getBytes(int x, int y, int width, int height, bool flipImage, std::function<void(const unsigned char*)> callback)
{
    CC_ASSERT(width <= _width && height <= _height);
    
    MTLTextureDescriptor* textureDescriptor =
    [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:Utils::toMTLPixelFormat(_textureFormat)
                                                       width:_width
                                                      height:_height
                                                   mipmapped:NO];
    id<MTLDevice> device = static_cast<DeviceMTL*>(Device::getInstance())->getMTLDevice();
    id<MTLTexture> copiedTexture = [device newTextureWithDescriptor:textureDescriptor];
    
    MTLRegion region = MTLRegionMake2D(0, 0, _width, _height);
    auto commandQueue = static_cast<DeviceMTL*>(DeviceMTL::getInstance())->getMTLCommandQueue();
    auto commandBuffer = [commandQueue commandBuffer];
    [commandBuffer enqueue];
    id<MTLBlitCommandEncoder> commandEncoder = [commandBuffer blitCommandEncoder];
    [commandEncoder copyFromTexture:_mtlTexture sourceSlice:0 sourceLevel:0 sourceOrigin:region.origin sourceSize:region.size toTexture:copiedTexture destinationSlice:0 destinationLevel:0 destinationOrigin:region.origin];
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    [commandEncoder synchronizeResource:copiedTexture];
#endif
    [commandEncoder endEncoding];
    
    [commandBuffer addCompletedHandler:^(id<MTLCommandBuffer> commandBuffer) {
        MTLRegion region = MTLRegionMake2D(0, 0, width, height);
        auto bytePerRow = width * _bitsPerElement / 8;
        unsigned char* image = new unsigned char[bytePerRow * height];
        [copiedTexture getBytes:image bytesPerRow:_bytesPerRow fromRegion:region mipmapLevel:0];
        
        //consistent with opengl behavior
        if(!flipImage)
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
        }
        else
        {
            callback(image);
            CC_SAFE_DELETE_ARRAY(image);
        }
        [copiedTexture release];
    }];
    [commandBuffer commit];
}

void TextureMTL::generateMipmaps()
{
    if (TextureUsage::RENDER_TARGET == _textureUsage || isColorRenderable(_textureFormat) == false)
        return;
    
    if(!_isMipmapGenerated)
    {
        _isMipmapGenerated = true;
        Utils::generateMipmaps(_mtlTexture);
        
    }
}

TextureCubeMTL::TextureCubeMTL(id<MTLDevice> mtlDevice, const TextureDescriptor& descriptor)
: backend::TextureCubemap(descriptor)
{
    _mtlDevice = mtlDevice;
    createTexture(mtlDevice, descriptor);
    createSampler(mtlDevice, descriptor.samplerDescriptor);
    
    // Metal doesn't support RGB888/RGBA4444, so should convert to RGBA888;
    if (TextureFormat::R8G8B8 == _textureFormat)
    {
        _bitsPerElement = 4 * 8;
    }
    
    _bytesPerRow = descriptor.width * _bitsPerElement / 8 ;
    _bytesPerImage = _bytesPerRow * descriptor.width;
    _region = MTLRegionMake2D(0, 0, descriptor.width, descriptor.height);

}

TextureCubeMTL::~TextureCubeMTL()
{
    [_mtlTexture release];
    [_mtlSamplerState release];
}

void TextureCubeMTL::createTexture(id<MTLDevice> mtlDevice, const TextureDescriptor& descriptor)
{
    MTLTextureDescriptor* textureDescriptor =
    [MTLTextureDescriptor textureCubeDescriptorWithPixelFormat:Utils::toMTLPixelFormat(descriptor.textureFormat) size:descriptor.width mipmapped:YES];
    
    if (TextureUsage::RENDER_TARGET == descriptor.textureUsage)
    {
        textureDescriptor.resourceOptions = MTLResourceStorageModePrivate;
        textureDescriptor.usage = MTLTextureUsageRenderTarget | MTLTextureUsageShaderRead;
    }
    _mtlTexture = [mtlDevice newTextureWithDescriptor:textureDescriptor];
}

void TextureCubeMTL::createSampler(id<MTLDevice> mtlDevice, const SamplerDescriptor &descriptor)
{
    MTLSamplerDescriptor *mtlDescriptor = [MTLSamplerDescriptor new];
    mtlDescriptor.sAddressMode = descriptor.sAddressMode == SamplerAddressMode::DONT_CARE ? _sAddressMode : toMTLSamplerAddressMode(descriptor.sAddressMode);
    mtlDescriptor.tAddressMode = descriptor.tAddressMode == SamplerAddressMode::DONT_CARE ? _tAddressMode : toMTLSamplerAddressMode(descriptor.tAddressMode);
    
    mtlDescriptor.minFilter = descriptor.minFilter == SamplerFilter::DONT_CARE ? _minFilter : toMTLSamplerMinMagFilter(descriptor.minFilter);
    mtlDescriptor.magFilter = descriptor.magFilter == SamplerFilter::DONT_CARE ? _magFilter : toMTLSamplerMinMagFilter(descriptor.magFilter);
    if (_isMipmapEnabled)
        mtlDescriptor.mipFilter = descriptor.mipmapFilter == SamplerFilter::DONT_CARE ? _mipFilter : toMTLSamplerMipFilter(descriptor.mipmapFilter);
    
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
    bool needGenerateMipmap = !_isMipmapEnabled && sampler.mipmapEnabled;
    _isMipmapEnabled = sampler.mipmapEnabled;
    if(needGenerateMipmap)
    {
        generateMipmaps();
    }
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
    if(_isMipmapEnabled)
    {
        _isMipmapGenerated = true;
        generateMipmaps();
    }
}

void TextureCubeMTL::getBytes(int x, int y, int width, int height, bool flipImage, std::function<void(const unsigned char*)> callback)
{
    CC_ASSERT(width <= _mtlTexture.width && height <= _mtlTexture.height);
    
    MTLTextureDescriptor* textureDescriptor =
    [MTLTextureDescriptor textureCubeDescriptorWithPixelFormat:Utils::toMTLPixelFormat(_textureFormat)
                                                          size:_mtlTexture.width
                                                     mipmapped:NO];

    id<MTLDevice> device = static_cast<DeviceMTL*>(Device::getInstance())->getMTLDevice();
    id<MTLTexture> copiedTexture = [device newTextureWithDescriptor:textureDescriptor];
    
    auto commandQueue = static_cast<DeviceMTL*>(DeviceMTL::getInstance())->getMTLCommandQueue();
    auto commandBuffer = [commandQueue commandBuffer];
    [commandBuffer enqueue];
    id<MTLBlitCommandEncoder> commandEncoder = [commandBuffer blitCommandEncoder];
    for(int slice = 0; slice < 6; slice++)
    {
        [commandEncoder copyFromTexture:_mtlTexture sourceSlice:slice sourceLevel:0 sourceOrigin:_region.origin sourceSize:_region.size toTexture:copiedTexture destinationSlice:slice destinationLevel:0 destinationOrigin:_region.origin];
    }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    [commandEncoder synchronizeResource:copiedTexture];
#endif
    [commandEncoder endEncoding];
    
    [commandBuffer addCompletedHandler:^(id<MTLCommandBuffer> commandBuffer) {
        MTLRegion region = MTLRegionMake2D(0, 0, width, height);
        auto bytePerRow = width * _bitsPerElement / 8;
        unsigned char* image = new unsigned char[bytePerRow * height];
        [copiedTexture getBytes:image bytesPerRow:_bytesPerRow fromRegion:region mipmapLevel:0];
        
        //consistent with opengl behavior
        if(!flipImage)
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
        }
        else
        {
            callback(image);
            CC_SAFE_DELETE_ARRAY(image);
        }
        [copiedTexture release];
    }];
    [commandBuffer commit];
}

void TextureCubeMTL::generateMipmaps()
{
    if (TextureUsage::RENDER_TARGET == _textureUsage || isColorRenderable(_textureFormat) == false)
        return;
    
    if(!_isMipmapGenerated)
    {
        _isMipmapGenerated = true;
        Utils::generateMipmaps(_mtlTexture);
    }
}

CC_BACKEND_END
