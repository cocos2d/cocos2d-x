#include "platform/CCDevice.h"
#include "jni/DPIJni.h"

NS_CC_BEGIN

float CCDevice::getDPI()
{
    return getDPIJNI();
}

NS_CC_END
