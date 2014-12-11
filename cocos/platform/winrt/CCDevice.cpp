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
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) ||  (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) 

#include "cocos2d.h"
#include "platform/CCDevice.h"
#include "platform/CCFileUtils.h"
#include "platform/winrt/CCFreeTypeFont.h"
#include "platform/CCStdC.h"

using namespace Windows::Graphics::Display;
using namespace Windows::Devices::Sensors;
using namespace Windows::Foundation;

NS_CC_BEGIN

CCFreeTypeFont sFT;

int Device::getDPI()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WP8
	static const float dipsPerInch = 96.0f;
	return floor(DisplayProperties::LogicalDpi / dipsPerInch + 0.5f); // Round to nearest integer.
#elif defined WP8_SHADER_COMPILER
    return 0;
#else
    return cocos2d::GLViewImpl::sharedOpenGLView()->GetDPI();
#endif
}

static Accelerometer^ sAccelerometer = nullptr;


void Device::setAccelerometerEnabled(bool isEnabled)
{
#ifndef WP8_SHADER_COMPILER
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
	        MessageBox("This device does not have an accelerometer.","Alert");
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

#if (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
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
				acc.y = reading->AccelerationX;
                    break;
              
            default:
  				acc.x = reading->AccelerationX;
				acc.y = reading->AccelerationY;
                break;
            }
#else // Windows Store App
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
                acc.x = -reading->AccelerationY;
                acc.y = reading->AccelerationX;
                break;

            default:
                acc.x = reading->AccelerationY;
                acc.y = -reading->AccelerationX;
                break;
            }
#endif
	        std::shared_ptr<cocos2d::InputEvent> event(new AccelerometerEvent(acc));
            cocos2d::GLViewImpl::sharedOpenGLView()->QueueEvent(event);
		});
	}
#endif
}

void Device::setAccelerometerInterval(float interval)
{
    if (sAccelerometer)
    {
        int minInterval = sAccelerometer->MinimumReportInterval;
	    int reqInterval = (int) interval;
        sAccelerometer->ReportInterval = reqInterval < minInterval ? minInterval : reqInterval;
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
}

NS_CC_END

#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) ||  (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) 
