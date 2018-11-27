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
        }
    }
    
    MTLSamplerMipFilter toMTLSamplerMipFilter(SamplerFilter mode) {
        switch (mode) {
            case SamplerFilter::NEAREST:
                return MTLSamplerMipFilterNearest;
            case SamplerFilter::LINEAR:
                return MTLSamplerMipFilterLinear;
        }
    }
    
    void convertRGB2RGBA(uint8_t* src, uint8_t* dst, uint32_t length)
    {
        for (uint32 i = 0; i < length; ++i)
        {
            *dst++ = *src++;
            *dst++ = *src++;
            *dst++ = *src++;
            *dst++ = 255;
        }
    }
    
    bool convertData(uint8_t* src, uint32_t length, TextureFormat format, uint8_t** out)
    {
        *out = src;
        bool converted = false;
        if (TextureFormat::R8G8B8 == format)
        {
            *out = (uint8_t*)malloc(length * 4);
            convertRGB2RGBA(src, *out, length);
            
            converted = true;
        }
        return converted;
    }
}

TextureMTL::TextureMTL(id<MTLDevice> mtlDevice, const TextureDescriptor& descriptor)
: Texture(descriptor)
{
    createTexture(mtlDevice, descriptor);
    createSampler(mtlDevice, descriptor);
    
    // Metal doesn't support RGB888, so should convert to RGBA888;
    if (TextureFormat::R8G8B8 == _textureFormat)
        _bytesPerElement = 4;
    
    _bytesPerRow = _bytesPerElement * descriptor.width;
}

TextureMTL::~TextureMTL()
{
    [_mtlTexture release];
    [_mtlSamplerState release];
}

void TextureMTL::updateData(uint8_t* data)
{
    updateSubData(0, 0, (uint32_t)_mtlTexture.width, (uint32_t)_mtlTexture.height, data);
}

void TextureMTL::updateSubData(uint32_t xoffset, uint32_t yoffset, uint32_t width, uint32_t height, uint8_t* data)
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
    
    [_mtlTexture replaceRegion:region
                   mipmapLevel:0
                     withBytes:convertedData
                   bytesPerRow:_bytesPerRow];
    
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

void TextureMTL::createSampler(id<MTLDevice> mtlDevice, const TextureDescriptor &descriptor)
{
    MTLSamplerDescriptor *mtlDescriptor = [MTLSamplerDescriptor new];
    mtlDescriptor.sAddressMode = toMTLSamplerAddressMode(descriptor.samplerDescriptor.sAddressMode);
    mtlDescriptor.tAddressMode = toMTLSamplerAddressMode(descriptor.samplerDescriptor.tAddressMode);
    
    mtlDescriptor.minFilter = toMTLSamplerMinMagFilter(descriptor.samplerDescriptor.minFilter);
    mtlDescriptor.magFilter = toMTLSamplerMinMagFilter(descriptor.samplerDescriptor.magFilter);
    if (_isMipmapEnabled)
        mtlDescriptor.mipFilter = toMTLSamplerMipFilter(descriptor.samplerDescriptor.mipmapFilter);
    
    _mtlSamplerState = [mtlDevice newSamplerStateWithDescriptor:mtlDescriptor];
    
    [mtlDescriptor release];
}

CC_BACKEND_END
