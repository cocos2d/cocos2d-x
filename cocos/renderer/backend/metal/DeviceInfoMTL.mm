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
 

#include "DeviceInfoMTL.h"
#include "base/ccMacros.h"
CC_BACKEND_BEGIN

namespace {
    int getMaxVertexAttributes(FeatureSet featureSet)
    {
        int maxAttributes = 0;
        switch (featureSet)
        {
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v1:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v1:
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v2:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v2:
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v1:
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v3:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v3:
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v2:
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v4:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v4:
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v3:
            case FeatureSet::FeatureSet_iOS_GPUFamily4_v1:
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v5:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v5:
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v4:
            case FeatureSet::FeatureSet_iOS_GPUFamily4_v2:
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v1:
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v2:
            case FeatureSet::FeatureSet_macOS_ReadWriteTextureTier2:
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v3:
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v4:
            case FeatureSet::FeatureSet_macOS_GPUFamily2_v1:
                maxAttributes = 31;
                break;
            default:
                break;
        }
        return maxAttributes;
    }
    
    int getMaxTextureEntries(FeatureSet featureSet)
    {
        int maxTextureEntries = 0;
        switch (featureSet)
        {
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v1:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v1:
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v2:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v2:
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v1:
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v3:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v3:
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v2:
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v4:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v4:
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v3:
            case FeatureSet::FeatureSet_iOS_GPUFamily4_v1:
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v5:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v5:
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v4:
            case FeatureSet::FeatureSet_iOS_GPUFamily4_v2:
                maxTextureEntries = 31;
                break;
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v1:
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v2:
            case FeatureSet::FeatureSet_macOS_ReadWriteTextureTier2:
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v3:
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v4:
            case FeatureSet::FeatureSet_macOS_GPUFamily2_v1:
                maxTextureEntries = 128;
                break;
            default:
                break;
        }
        return maxTextureEntries;
    }
    
    int getMaxSamplerEntries(FeatureSet featureSet)
    {
        int maxSamplerEntries = 0;
        switch (featureSet)
        {
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v1:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v1:
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v2:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v2:
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v1:
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v3:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v3:
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v2:
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v4:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v4:
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v3:
            case FeatureSet::FeatureSet_iOS_GPUFamily4_v1:
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v5:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v5:
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v4:
            case FeatureSet::FeatureSet_iOS_GPUFamily4_v2:
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v1:
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v2:
            case FeatureSet::FeatureSet_macOS_ReadWriteTextureTier2:
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v3:
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v4:
            case FeatureSet::FeatureSet_macOS_GPUFamily2_v1:
                maxSamplerEntries = 16;
                break;
            default:
                break;
        }
        return maxSamplerEntries;
    }
    
    int getMaxTextureWidthHeight(FeatureSet featureSet)
    {
        int maxTextureSize = 0;
        switch (featureSet)
        {
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v1:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v1:
                maxTextureSize = 4096;
                break;
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v2:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v2:
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v3:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v3:
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v4:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v4:
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v5:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v5:
                maxTextureSize = 8192;
                break;
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v1:
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v2:
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v3:
            case FeatureSet::FeatureSet_iOS_GPUFamily4_v1:
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v4:
            case FeatureSet::FeatureSet_iOS_GPUFamily4_v2:
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v1:
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v2:
            case FeatureSet::FeatureSet_macOS_ReadWriteTextureTier2:
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v3:
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v4:
            case FeatureSet::FeatureSet_macOS_GPUFamily2_v1:
                maxTextureSize = 16384;
                break;
            default:
                break;
        }
        return maxTextureSize;
    }
    
    const char* featureSetToString(FeatureSet featureSet)
    {
        switch (featureSet)
        {
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v1:
                return "iOS_GPUFamily1_v1";
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v1:
                return "iOS_GPUFamily2_v1";
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v2:
                return "iOS_GPUFamily1_v2";
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v2:
                return "iOS_GPUFamily2_v2";
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v3:
                return "iOS_GPUFamily1_v3";
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v3:
                return "iOS_GPUFamily2_v3";
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v4:
                return "iOS_GPUFamily1_v4";
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v4:
                return "iOS_GPUFamily2_v4";
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v5:
                return "iOS_GPUFamily1_v5";
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v5:
                return "iOS_GPUFamily2_v5";
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v1:
                return "iOS_GPUFamily3_v1";
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v2:
                return "iOS_GPUFamily3_v2";
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v3:
                return "iOS_GPUFamily3_v3";
            case FeatureSet::FeatureSet_iOS_GPUFamily4_v1:
                return "iOS_GPUFamily4_v1";
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v4:
                return "iOS_GPUFamily3_v4";
            case FeatureSet::FeatureSet_iOS_GPUFamily4_v2:
                return "iOS_GPUFamily4_v2";
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v1:
                return "macOS_GPUFamily1_v1";
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v2:
                return "macOS_GPUFamily1_v2";
            case FeatureSet::FeatureSet_macOS_ReadWriteTextureTier2:
                return "macOS_ReadWriteTextureTier2";
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v3:
                return "macOS_GPUFamily1_v3";
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v4:
                return "macOS_GPUFamily1_v4";
            case FeatureSet::FeatureSet_macOS_GPUFamily2_v1:
                return "macOS_GPUFamily2_v1";
            default:
                break;
        }
        return "";
    }
    
    bool supportPVRTC(FeatureSet featureSet)
    {
        switch (featureSet)
        {
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v1:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v1:
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v2:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v2:
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v3:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v3:
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v4:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v4:
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v5:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v5:
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v1:
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v2:
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v3:
            case FeatureSet::FeatureSet_iOS_GPUFamily4_v1:
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v4:
            case FeatureSet::FeatureSet_iOS_GPUFamily4_v2:
                return true;
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v1:
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v2:
            case FeatureSet::FeatureSet_macOS_ReadWriteTextureTier2:
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v3:
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v4:
            case FeatureSet::FeatureSet_macOS_GPUFamily2_v1:
                return false;
            default:
                break;
        }
        return false;
    }
    
    bool supportEACETC(FeatureSet featureSet)
    {
        switch (featureSet)
        {
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v1:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v1:
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v2:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v2:
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v3:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v3:
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v4:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v4:
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v5:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v5:
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v1:
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v2:
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v3:
            case FeatureSet::FeatureSet_iOS_GPUFamily4_v1:
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v4:
            case FeatureSet::FeatureSet_iOS_GPUFamily4_v2:
                return true;
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v1:
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v2:
            case FeatureSet::FeatureSet_macOS_ReadWriteTextureTier2:
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v3:
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v4:
            case FeatureSet::FeatureSet_macOS_GPUFamily2_v1:
                return false;
            default:
                break;
        }
        return false;
    }
    
    bool supportASTC(FeatureSet featureSet)
    {
        switch (featureSet)
        {
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v1:
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v2:
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v3:
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v4:
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v5:
                return false;
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v1:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v2:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v3:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v4:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v5:
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v1:
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v2:
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v3:
            case FeatureSet::FeatureSet_iOS_GPUFamily4_v1:
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v4:
            case FeatureSet::FeatureSet_iOS_GPUFamily4_v2:
                return true;
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v1:
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v2:
            case FeatureSet::FeatureSet_macOS_ReadWriteTextureTier2:
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v3:
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v4:
            case FeatureSet::FeatureSet_macOS_GPUFamily2_v1:
                return false;
            default:
                break;
        }
        return false;
    }
    
    bool supportS3TC(FeatureSet featureSet)
    {
        switch (featureSet)
        {
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v1:
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v2:
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v3:
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v4:
            case FeatureSet::FeatureSet_iOS_GPUFamily1_v5:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v1:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v2:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v3:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v4:
            case FeatureSet::FeatureSet_iOS_GPUFamily2_v5:
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v1:
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v2:
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v3:
            case FeatureSet::FeatureSet_iOS_GPUFamily4_v1:
            case FeatureSet::FeatureSet_iOS_GPUFamily3_v4:
            case FeatureSet::FeatureSet_iOS_GPUFamily4_v2:
                return false;
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v1:
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v2:
            case FeatureSet::FeatureSet_macOS_ReadWriteTextureTier2:
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v3:
            case FeatureSet::FeatureSet_macOS_GPUFamily1_v4:
            case FeatureSet::FeatureSet_macOS_GPUFamily2_v1:
                return true;
            default:
                break;
        }
        return false;
    }
}

DeviceInfoMTL::DeviceInfoMTL(id<MTLDevice> device)
{
   _deviceName = [device.name UTF8String];
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    const FeatureSet minRequiredFeatureSet = FeatureSet::FeatureSet_iOS_GPUFamily1_v1;
    const FeatureSet maxKnownFeatureSet = FeatureSet::FeatureSet_iOS_GPUFamily4_v2;
#else
    const FeatureSet minRequiredFeatureSet = FeatureSet::FeatureSet_macOS_GPUFamily1_v1;
    const FeatureSet maxKnownFeatureSet = FeatureSet::FeatureSet_macOS_GPUFamily2_v1;
    _isDepth24Stencil8PixelFormatSupported = [device isDepth24Stencil8PixelFormatSupported];
#endif
    
    for (auto featureSet = maxKnownFeatureSet; featureSet >= minRequiredFeatureSet; --featureSet)
    {
        if ([device supportsFeatureSet:MTLFeatureSet(featureSet)])
        {
            _featureSet = featureSet;
            break;
        }
    }
}

bool DeviceInfoMTL::init()
{
    _maxAttributes = getMaxVertexAttributes(_featureSet);
    _maxSamplesAllowed = getMaxSamplerEntries(_featureSet);
    _maxTextureUnits = getMaxTextureEntries(_featureSet);
    _maxTextureSize = getMaxTextureWidthHeight(_featureSet);
    
    return true;
}

const char* DeviceInfoMTL::getVendor() const
{
    return "";
}

const char* DeviceInfoMTL::getRenderer() const
{
    return _deviceName.c_str();
}

const char* DeviceInfoMTL::getVersion() const
{
    return featureSetToString(_featureSet);
}

const char* DeviceInfoMTL::getExtension() const
{
    return "";
}

bool DeviceInfoMTL::checkForFeatureSupported(FeatureType feature)
{
    bool featureSupported = false;
    switch (feature)
    {
    case FeatureType::PVRTC:
        featureSupported = supportPVRTC(_featureSet);
        break;
    case FeatureType::ETC1:
        featureSupported = supportEACETC(_featureSet);
        break;
    case FeatureType::S3TC:
        featureSupported = supportS3TC(_featureSet);
        break;
    case FeatureType::IMG_FORMAT_BGRA8888:
        featureSupported = true;
        break;
    case FeatureType::PACKED_DEPTH_STENCIL:
        featureSupported = _isDepth24Stencil8PixelFormatSupported;
        break;
    case FeatureType::ASTC:
        featureSupported = supportASTC(_featureSet);
        break;
    default:
        break;
    }
    return featureSupported;
}

CC_BACKEND_END
