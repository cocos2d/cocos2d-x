#include "DeviceInfoMTL.h"

CC_BACKEND_BEGIN

DeviceInfo* DeviceInfo::getInstance()
{
    if (!DeviceInfo::s_sharedDeviceInfo)
    {
        DeviceInfo::s_sharedDeviceInfo = new (std::nothrow) DeviceInfoMTL();
        if(!DeviceInfo::s_sharedDeviceInfo->init())
        {
            CC_SAFE_DELETE(DeviceInfo::s_sharedDeviceInfo);
        }
    }
    return DeviceInfo::s_sharedDeviceInfo;
}

bool DeviceInfoMTL::init()
{
    _maxAttributes = 31;
    _valueDict["max_vertex_attributes"] = Value((int)_maxAttributes);
    
    return true;
}

CC_BACKEND_END
