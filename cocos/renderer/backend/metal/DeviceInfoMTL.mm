#include "DeviceInfoMTL.h"
#include "base/ccMacros.h"

CC_BACKEND_BEGIN

DeviceInfoMTL::DeviceInfoMTL(id<MTLDevice> device)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    const NSUInteger maxKnownFeatureSet = MTLFeatureSet_iOS_GPUFamily4_v2;
    _currentFeatureSet = MTLFeatureSet_iOS_GPUFamily1_v1;
#else
    const NSUInteger maxKnownFeatureSet = MTLFeatureSet_macOS_GPUFamily2_v1;
    _currentFeatureSet = MTLFeatureSet_macOS_GPUFamily1_v1;
#endif
    
    for (int featureSet = maxKnownFeatureSet; featureSet >= 0; --featureSet)
    {
        if ([device supportsFeatureSet:MTLFeatureSet(featureSet)])
        {
            _currentFeatureSet = MTLFeatureSet(featureSet);
            break;
        }
    }
}

bool DeviceInfoMTL::init()
{
    _maxAttributes = 31;
    
    getTextureSizeInfo();
    return true;
}

void DeviceInfoMTL::getTextureSizeInfo()
{
    switch (_currentFeatureSet) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        case MTLFeatureSet_iOS_GPUFamily1_v1:
        case MTLFeatureSet_iOS_GPUFamily2_v1:
            _maxTextureSize = 4096;
            break;
        case MTLFeatureSet_iOS_GPUFamily1_v2:
        case MTLFeatureSet_iOS_GPUFamily2_v2:
        case MTLFeatureSet_iOS_GPUFamily1_v3:
        case MTLFeatureSet_iOS_GPUFamily2_v3:
        case MTLFeatureSet_iOS_GPUFamily1_v4:
        case MTLFeatureSet_iOS_GPUFamily2_v4:
        case MTLFeatureSet_iOS_GPUFamily1_v5:
        case MTLFeatureSet_iOS_GPUFamily2_v5:
            _maxTextureSize = 8192;
            break;
        case MTLFeatureSet_iOS_GPUFamily3_v1:
        case MTLFeatureSet_iOS_GPUFamily3_v2:
        case MTLFeatureSet_iOS_GPUFamily3_v3:
        case MTLFeatureSet_iOS_GPUFamily4_v1:
        case MTLFeatureSet_iOS_GPUFamily3_v4:
        case MTLFeatureSet_iOS_GPUFamily4_v2:
            _maxTextureSize = 16384;
            break;
#else
        case MTLFeatureSet_macOS_GPUFamily1_v1:
        case MTLFeatureSet_macOS_GPUFamily1_v2:
        case MTLFeatureSet_macOS_GPUFamily1_v3:
        case MTLFeatureSet_macOS_GPUFamily1_v4:
        case MTLFeatureSet_macOS_GPUFamily2_v1:
            _maxTextureSize = 16384;
            break;
#endif
        default:
            CCASSERT(false, "Current FeatureSet Not Supported!");
            break;
    }
}

CC_BACKEND_END
