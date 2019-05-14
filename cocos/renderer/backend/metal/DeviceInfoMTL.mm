
#include "DeviceInfoMTL.h"
#include "base/ccMacros.h"
CC_BACKEND_BEGIN

DeviceInfoMTL::DeviceInfoMTL(id<MTLDevice> device)
{
   _deviceName = [device.name UTF8String];
}

bool DeviceInfoMTL::init()
{
    _maxAttributes = 31;
    _maxSamplesAllowed = 16;
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    _maxTextureUnits = 31;
     _maxTextureSize = 4096;
#else
    _maxTextureUnits = 128;
    _maxTextureSize = 16384;
#endif
    
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
    return "";
}

const char* DeviceInfoMTL::getExtension() const
{
    return "";
}

bool DeviceInfoMTL::checkForFeatureSupported(const FeaturesInfo& feature)
{
    bool featureSupported = false;
    switch (feature)
    {
    case FeaturesInfo::PVRTC:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        featureSupported = true;
#endif
        break;
    case FeaturesInfo::IMG_FORMAT_BGRA8888:
        featureSupported = true;
        break;
    case FeaturesInfo::PACKED_DEPTH_STENCIL:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        featureSupported = true;
#endif
        break;
    default:
        break;
    }
    return featureSupported;
}

CC_BACKEND_END
