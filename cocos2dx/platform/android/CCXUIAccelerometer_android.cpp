/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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
#include "CCXUIAccelerometer_android.h"
#include <stdio.h>
#include <list>
#include <android/log.h>

#define TG3_GRAVITY_EARTH                    (9.80665f)
#define  LOG_TAG    "CCXUIAccelerometer_android"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

namespace cocos2d
{
	UIAccelerometer* UIAccelerometer::m_spUIAccelerometer = NULL;

	UIAccelerometer::UIAccelerometer() {
		m_AccelDelegates = new std::list<UIAccelerometerDelegate*>();
	}

    UIAccelerometer::~UIAccelerometer() {
    	delete m_AccelDelegates;
    }

    UIAccelerometer* UIAccelerometer::sharedAccelerometer() {

    	if (m_spUIAccelerometer == NULL)
    	{
    		m_spUIAccelerometer = new UIAccelerometer();
    	}
    	
    	return m_spUIAccelerometer;
    }

    void UIAccelerometer::removeDelegate(UIAccelerometerDelegate* pDelegate) {
    	m_AccelDelegates->remove(pDelegate);
    }

    void UIAccelerometer::addDelegate(UIAccelerometerDelegate* pDelegate) {
    	m_AccelDelegates->push_front(pDelegate);
    }

    void UIAccelerometer::update(float x, float y, float z, long sensorTimeStamp) {
    	if ( m_AccelDelegates != NULL && !m_AccelDelegates->empty() ) {
    		pAccelerationValue.x = -((double)x / TG3_GRAVITY_EARTH);
    		pAccelerationValue.y = -((double)y / TG3_GRAVITY_EARTH);
    		pAccelerationValue.z = -((double)z / TG3_GRAVITY_EARTH);
    		pAccelerationValue.timestamp = (double)sensorTimeStamp;

    		for(std::list<UIAccelerometerDelegate*>::const_iterator it = m_AccelDelegates->begin(); it != m_AccelDelegates->end(); ++it)
    		{
				(*it)->didAccelerate(&pAccelerationValue);
    		}
    	}
    }
} // end of namespace cococs2d

