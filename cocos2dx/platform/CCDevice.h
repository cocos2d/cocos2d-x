#ifndef __CCDEVICE_H__
#define __CCDEVICE_H__

#include "CCPlatformMacros.h"

NS_CC_BEGIN

class CC_DLL Device
{
private:
    Device();
public:
    /**
     *  Gets the DPI of device
     *  @return The DPI of device.
     */
    static int getDPI();
    
    /**
     * To enable or disable accelerometer.
     */
    static void setAccelerometerEnabled(bool isEnabled);
    /**
     *  Sets the interval of accelerometer.
     */
    static void setAccelerometerInterval(float interval);
};


NS_CC_END

#endif /* __CCDEVICE_H__ */
