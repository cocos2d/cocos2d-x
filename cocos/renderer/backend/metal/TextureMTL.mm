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
}

TextureMTL::TextureMTL(id<MTLDevice> mtlDevice, const TextureDescriptor& descriptor)
: Texture2d(descriptor)
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
        Utils::generateMipmaps(_mtlTexture);
}

void TextureMTL::createTexture(id<MTLDevice> mtlDevice, const TextureDescriptor& descriptor)
{
    MTLTextureDescriptor* textureDescriptor =
           [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:Utils::toMTLPixelFormat(descriptor.textureFormat)
                                                              width:descriptor.width
                                                             height:descriptor.height
                                                          mipmapped:TRUE];
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
        [_mtlSamplerState release];
    
    _sAddressMode = mtlDescriptor.sAddressMode;
    _tAddressMode = mtlDescriptor.tAddressMode;
    _minFilter = mtlDescriptor.minFilter;
    _magFilter = mtlDescriptor.magFilter;
    _mipFilter = mtlDescriptor.mipFilter;
    
    _mtlSamplerState = [mtlDevice newSamplerStateWithDescriptor:mtlDescriptor];
    
    [mtlDescriptor release];
}

CC_BACKEND_END
