#include "platform/CCDevice.h"
#include "jni/DPIJni.h"
#include "nativeactivity.h"

NS_CC_BEGIN

int Device::getDPI()
{
    static int dpi = -1;
    if (dpi == -1)
    {
        dpi = (int)getDPIJNI();
    }
    return dpi;
}

void Device::setAccelerometerEnabled(bool isEnabled)
{
    if (isEnabled)
    {
        enableAccelerometer();
    }
    else
    {
        disableAccelerometer();
    }
}

void Device::setAccelerometerInterval(float interval)
{
	setAccelerometerInterval(interval);
}

NS_CC_END
