//
//  StringUtils.hpp
//  Test
//
//  Created by Cocos on 2018/11/2.
//  Copyright © 2018 cocos. All rights reserved.
//

#ifndef StringUtils_hpp
#define StringUtils_hpp

#include <string>
#include "Types.h"
CC_BACKEND_BEGIN

class StringUtils
{
public:
    enum class PixelFormat
    {
        //! auto detect the type
        AUTO,
        //! 32-bit texture: BGRA8888
        BGRA8888,
        //! 32-bit texture: RGBA8888
        RGBA8888,
        //! 24-bit texture: RGBA888
        RGB888,
        //! 16-bit texture without Alpha channel
        RGB565,
        //! 8-bit textures used as masks
        A8,
        //! 8-bit intensity texture
        I8,
        //! 16-bit textures used as masks
        AI88,
        //! 16-bit textures: RGBA4444
        RGBA4444,
        //! 16-bit textures: RGB5A1
        RGB5A1,
        //! 4-bit PVRTC-compressed texture: PVRTC4
        PVRTC4,
        //! 4-bit PVRTC-compressed texture: PVRTC4 (has alpha channel)
        PVRTC4A,
        //! 2-bit PVRTC-compressed texture: PVRTC2
        PVRTC2,
        //! 2-bit PVRTC-compressed texture: PVRTC2 (has alpha channel)
        PVRTC2A,
        //! ETC-compressed texture: ETC
        ETC,
        //! S3TC-compressed texture: S3TC_Dxt1
        S3TC_DXT1,
        //! S3TC-compressed texture: S3TC_Dxt3
        S3TC_DXT3,
        //! S3TC-compressed texture: S3TC_Dxt5
        S3TC_DXT5,
        //! ATITC-compressed texture: ATC_RGB
        ATC_RGB,
        //! ATITC-compressed texture: ATC_EXPLICIT_ALPHA
        ATC_EXPLICIT_ALPHA,
        //! ATITC-compressed texture: ATC_INTERPOLATED_ALPHA
        ATC_INTERPOLATED_ALPHA,
        //! Default texture format: AUTO
        
        //metal 16-bits packed pixel formats
        MTL_B5G6R5,
        //MTL_A1BGR5,
        MTL_BGR5A1,
        MTL_ABGR4,
        
        DEFAULT = AUTO,
        
        NONE = -1
    };
    
    static std::string TextureFormat2String(const TextureFormat& textureFormat);
    static std::string TextureType2String(const TextureType& textureType);
    static std::string TextureUsage2String(const TextureUsage& textureUsage);
    static std::string SamplerFilterType2String(const SamplerFilter& filterType);
    static std::string SamplerAddressMode2String(const SamplerAddressMode& addressMode);
    static std::string SamplerDescriptor2String(const SamplerDescriptor& descriptor);
    static std::string StencilOperation2String(const StencilOperation& operation);
    static std::string CompareFunction2String(const CompareFunction& compareFunction);
    static std::string ColorWriteMask2String(const ColorWriteMask& colorWriteMask);
    static std::string BlendOperation2String(const BlendOperation& blendOperation);
    static std::string BlendFactor2String(const BlendFactor& blendFactor);
    static TextureFormat PixelFormat2TextureFormat(const PixelFormat& pixleFormat);
};

CC_BACKEND_END
#endif /* StringUtils_hpp */
