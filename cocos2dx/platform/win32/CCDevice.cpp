#include "platform/CCDevice.h"
#include "CCStdC.h"

NS_CC_BEGIN

float CCDevice::getDPI()
{
    HDC hScreenDC = GetDC( NULL );
    int PixelsX = GetDeviceCaps( hScreenDC, HORZRES );
    int MMX = GetDeviceCaps( hScreenDC, HORZSIZE );
    ReleaseDC( NULL, hScreenDC );   
    return 254.0f*PixelsX/MMX/10;
}

NS_CC_END