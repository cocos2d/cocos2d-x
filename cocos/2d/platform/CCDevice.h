#ifndef __CCDEVICE_H__
#define __CCDEVICE_H__

#include "CCPlatformMacros.h"
#include "ccMacros.h"

NS_CC_BEGIN

class CC_DLL Device
{
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

private:
    CC_DISALLOW_IMPLICIT_CONSTRUCTORS(Device);
};


NS_CC_END

#endif /* __CCDEVICE_H__ */
