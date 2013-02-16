#ifndef __CCDEVICE_H__
#define __CCDEVICE_H__

#include "CCPlatformMacros.h"

NS_CC_BEGIN

class CCDevice
{
private:
    CCDevice();
public:
    static float getDPI();
};


NS_CC_END

#endif /* __CCDEVICE_H__ */
