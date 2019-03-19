#include "DeviceInfoMTL.h"
#include "base/ccMacros.h"

CC_BACKEND_BEGIN

DeviceInfoMTL::DeviceInfoMTL(id<MTLDevice> device)
{
}

bool DeviceInfoMTL::init()
{
    _maxAttributes = 31;
    
    getTextureSizeInfo();
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

CC_BACKEND_END
