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
    //glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &_maxTextureUnits);
    
        //ifdef ios
    //glGetIntegerv(GL_MAX_SAMPLES_APPLE, &_maxSamplesAllowed);
    getTextureSizeInfo();

//support PVRTC/EAC/ETC2/ASTC/BC/YUV
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    _features += "GL_IMG_texture_compression_pvrtc";
#else
    _features += "GL_OES_packed_depth_stencil";
#endif
    return true;
}

//todo coulsonwang
void DeviceInfoMTL::getTextureSizeInfo()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    _maxTextureSize = 4096;
        
#else
    _maxTextureSize = 16384;
#endif
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
    return _features.c_str();
}

bool DeviceInfoMTL::checkForFeatureSupported(const FeaturesInfo& feature)
{
    bool featureSupported = false;
    switch (feature)
    {
    case FeaturesInfo::PVRTC:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        featureSupported = true;
#else
        featureSupported = false;
#endif
        break;
    case FeaturesInfo::IMG_FORMAT_BGRA8888:
        featureSupported = true;
        break;
    case FeaturesInfo::PACKED_DEPTH_STENCIL:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        featureSupported = false;
#else
        featureSupported = true;
#endif
        break;
    default:
        break;
    }
    return featureSupported;
}

CC_BACKEND_END
