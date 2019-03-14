#include "DeviceInfoGL.h"
#include "platform/CCGL.h"

CC_BACKEND_BEGIN

DeviceInfo* DeviceInfo::getInstance()
{
    if (!DeviceInfo::s_sharedDeviceInfo)
    {
        DeviceInfo::s_sharedDeviceInfo = new (std::nothrow) DeviceInfoGL();
        if(!DeviceInfo::s_sharedDeviceInfo->init())
        {
            CC_SAFE_DELETE(DeviceInfo::s_sharedDeviceInfo);
        }
    }
    return DeviceInfo::s_sharedDeviceInfo;
}

bool DeviceInfoGL::init()
{
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &_maxAttributes);
    _valueDict["max_vertex_attributes"] = Value((int)_maxAttributes);
    
    return true;
}
CC_BACKEND_END
