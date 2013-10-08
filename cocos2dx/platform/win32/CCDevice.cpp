#include "platform/CCDevice.h"
#include "CCStdC.h"

NS_CC_BEGIN

int Device::getDPI()
{
    static int dpi = -1;
    if (dpi == -1)
    {
        HDC hScreenDC = GetDC( NULL );
        int PixelsX = GetDeviceCaps( hScreenDC, HORZRES );
        int MMX = GetDeviceCaps( hScreenDC, HORZSIZE );
        ReleaseDC( NULL, hScreenDC );   
        dpi = 254.0f*PixelsX/MMX/10;
    }
    return dpi;
}

void Device::setAccelerometerEnabled(bool isEnabled)
{}

void Device::setAccelerometerInterval(float interval)
{}

NS_CC_END