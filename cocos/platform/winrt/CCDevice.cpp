/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "platform/CCPlatformConfig.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)

#include "platform/CCDevice.h"
#include "platform/CCFileUtils.h"
#include "platform/winrt/CCFreeTypeFont.h"
#include "platform/winrt/CCWinRTUtils.h"
#include "platform/CCStdC.h"
#include "platform/winrt/CCGLViewImpl-winrt.h"

using namespace Windows::Graphics::Display;
using namespace Windows::Devices::Sensors;
using namespace Windows::Foundation;
#if (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
using namespace Windows::Phone::Devices::Notification;
#endif // (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)

NS_CC_BEGIN

CCFreeTypeFont sFT;

int Device::getDPI()
{
    return cocos2d::GLViewImpl::sharedOpenGLView()->GetDPI();
}

static Accelerometer^ sAccelerometer = nullptr;


void Device::setAccelerometerEnabled(bool isEnabled)
{
    static Windows::Foundation::EventRegistrationToken sToken;
    static bool sEnabled = false;

    // we always need to reset the accelerometer
    if (sAccelerometer)
    {
        sAccelerometer->ReadingChanged -= sToken;
        sAccelerometer = nullptr;
        sEnabled = false;
    }

    if (isEnabled)
    {
        sAccelerometer = Accelerometer::GetDefault();

        if(sAccelerometer == nullptr)
        {
            // It's not a friendly experience and may cause crash.
            //MessageBox("This device does not have an accelerometer.","Alert");
            log("This device does not have an accelerometer.");
            return;
        }

        setAccelerometerInterval(0.0f);
        sEnabled = true;

        sToken = sAccelerometer->ReadingChanged += ref new TypedEventHandler
            <Accelerometer^,AccelerometerReadingChangedEventArgs^>
            ([](Accelerometer^ a, AccelerometerReadingChangedEventArgs^ e)
        {
            if (!sEnabled)
            {
                return;
            }

            AccelerometerReading^ reading = e->Reading;
            cocos2d::Acceleration acc;
            acc.x = reading->AccelerationX;
            acc.y = reading->AccelerationY;
            acc.z = reading->AccelerationZ;
            acc.timestamp = 0;

            auto orientation = GLViewImpl::sharedOpenGLView()->getDeviceOrientation();

            if (isWindowsPhone())
            {
                switch (orientation)
                {
                case DisplayOrientations::Portrait:
                    acc.x = reading->AccelerationX;
                    acc.y = reading->AccelerationY;
                    break;

                case DisplayOrientations::Landscape:
                    acc.x = -reading->AccelerationY;
                    acc.y = reading->AccelerationX;
                    break;

                case DisplayOrientations::PortraitFlipped:
                    acc.x = -reading->AccelerationX;
                    acc.y = reading->AccelerationY;
                    break;

                case DisplayOrientations::LandscapeFlipped:
                    acc.x = reading->AccelerationY;
                    acc.y = -reading->AccelerationX;
                    break;

                default:
                    acc.x = reading->AccelerationX;
                    acc.y = reading->AccelerationY;
                    break;
                }
            }
            else // Windows Store App
            {
                // from http://msdn.microsoft.com/en-us/library/windows/apps/dn440593
                switch (orientation)
                {
                case DisplayOrientations::Portrait:
                    acc.x = reading->AccelerationY;
                    acc.y = -reading->AccelerationX;
                    break;

                case DisplayOrientations::Landscape:
                    acc.x = reading->AccelerationX;
                    acc.y = reading->AccelerationY;
                    break;

                case DisplayOrientations::PortraitFlipped:
                    acc.x = -reading->AccelerationY;
                    acc.y = reading->AccelerationX;
                    break;

                case DisplayOrientations::LandscapeFlipped:
                    acc.x = -reading->AccelerationX;
                    acc.y = -reading->AccelerationY;
                    break;

                default:
                    acc.x = reading->AccelerationY;
                    acc.y = -reading->AccelerationX;
                    break;
                }
            }

            std::shared_ptr<cocos2d::InputEvent> event(new AccelerometerEvent(acc));
            cocos2d::GLViewImpl::sharedOpenGLView()->QueueEvent(event);
        });
    }
}

void Device::setAccelerometerInterval(float interval)
{
    if (sAccelerometer)
    {
        try {
            int minInterval = sAccelerometer->MinimumReportInterval;
            int reqInterval = (int) interval;
            sAccelerometer->ReportInterval = reqInterval < minInterval ? minInterval : reqInterval;
        }
        catch (Platform::COMException^)
        {
            CCLOG("Device::setAccelerometerInterval not supported on this device");
        }
    }
    else
    {
        CCLOG("Device::setAccelerometerInterval: accelerometer not enabled.");
    }
}



Data Device::getTextureDataForText(const char * text, const FontDefinition& textDefinition, TextAlign align, int &width, int &height, bool& hasPremultipliedAlpha)
{
    Data ret;
    ssize_t dataLen;

    unsigned char* data = sFT.initWithString(text, textDefinition, align, width, height, dataLen);

    if (data)
    {
        ret.fastSet(data, dataLen);
        hasPremultipliedAlpha = false;
    }

    return ret;
}

void Device::setKeepScreenOn(bool value)
{
    CC_UNUSED_PARAM(value);
}

void Device::vibrate(float duration)
{
#if (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
    Windows::Foundation::TimeSpan timespan;
    // A time period expressed in 100-nanosecond units, see https://msdn.microsoft.com/en-us/library/windows/apps/windows.foundation.timespan.aspx
    // The duration is limited to a maximum of 5 seconds, see https://msdn.microsoft.com/en-us/library/windows/apps/windows.phone.devices.notification.vibrationdevice.aspx
    timespan.Duration = std::min(static_cast<int>(duration * 10000), 50000);

    VibrationDevice^ testVibrationDevice = VibrationDevice::GetDefault();
    testVibrationDevice->Vibrate(timespan);
#else
    CC_UNUSED_PARAM(duration);
#endif // (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
}

NS_CC_END

#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
