/****************************************************************************
 Copyright (c) 2011      cocos2d-x.org   http://cocos2d-x.org
 Copyright (c) 2012      Rocco Loscalzo (Wartortle)
 Copyright (c) Microsoft Open Technologies, Inc.

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

#include "cocos2d.h"
#include "CCAccelerometer.h"
using namespace Windows::Foundation;
using namespace Windows::Devices::Sensors;
using namespace Windows::Graphics::Display;


NS_CC_BEGIN

CCAccelerometer::CCAccelerometer() : m_pAccelDelegate(NULL)
{
	m_accelerometer = nullptr;
}

CCAccelerometer::~CCAccelerometer() 
{

}

void CCAccelerometer::setAccelerometerInterval(float interval)
{
	auto a =  Accelerometer::GetDefault();
    if(a)
    {
	    int minInterval = a->MinimumReportInterval;
	    int reqInterval = (int) interval;
	    a->ReportInterval = reqInterval < minInterval ? minInterval : reqInterval;
    }
}

void CCAccelerometer::setDelegate(CCAccelerometerDelegate* pDelegate) 
{
	m_pAccelDelegate = pDelegate;

	if (pDelegate)
	{
		m_accelerometer = Accelerometer::GetDefault();
		setAccelerometerInterval(0.0f);
		if(m_accelerometer != nullptr){

			m_accelerometer->ReadingChanged += ref new TypedEventHandler
				<Accelerometer^,AccelerometerReadingChangedEventArgs^>
				([=](Accelerometer^, AccelerometerReadingChangedEventArgs^)
			{
				AccelerometerReading^ reading = m_accelerometer->GetCurrentReading();
				m_obAccelerationValue.x = reading->AccelerationX;
				m_obAccelerationValue.y = reading->AccelerationY;
				m_obAccelerationValue.z = reading->AccelerationZ;

 #if CC_TARGET_PLATFORM == CC_PLATFORM_WP8
                auto orientation = CCEGLView::sharedOpenGLView()->getDeviceOrientation();

                switch (orientation)
                {
                case DisplayOrientations::Portrait:
 				    m_obAccelerationValue.x = reading->AccelerationX;
				    m_obAccelerationValue.y = reading->AccelerationY;
                    break;
                
                case DisplayOrientations::Landscape:
				    m_obAccelerationValue.x = -reading->AccelerationY;
				    m_obAccelerationValue.y = reading->AccelerationX;
                    break;
                
                case DisplayOrientations::PortraitFlipped:
				    m_obAccelerationValue.x = -reading->AccelerationX;
				    m_obAccelerationValue.y = reading->AccelerationY;
                    break;
                
                case DisplayOrientations::LandscapeFlipped:
 				    m_obAccelerationValue.x = reading->AccelerationY;
				    m_obAccelerationValue.y = reading->AccelerationX;
                      break;
              
                default:
  				    m_obAccelerationValue.x = reading->AccelerationX;
				    m_obAccelerationValue.y = reading->AccelerationY;
                    break;
               }
#endif

                m_pAccelDelegate->didAccelerate(&m_obAccelerationValue);

			});
		}
	}
	else
	{
		m_accelerometer = nullptr;
	}
}

NS_CC_END

