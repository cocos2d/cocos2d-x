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
#include "CCAccelerometer.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <stdio.h>
#include <android/log.h>

#define TG3_GRAVITY_EARTH                    (9.80665f)
#define  LOG_TAG    "CCAccelerometer_android"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

namespace cocos2d
{
    CCAccelerometer::CCAccelerometer() : _accelDelegate(NULL)
    {
    }

    CCAccelerometer::~CCAccelerometer() 
    {

    }

    void CCAccelerometer::setDelegate(CCAccelerometerDelegate* pDelegate) 
    {
        _accelDelegate = pDelegate;

        if (pDelegate)
        {        
            enableAccelerometerJNI();
        }
        else
        {
            disableAccelerometerJNI();
        }
    }

    void CCAccelerometer::setAccelerometerInterval(float interval) 
    {
        setAccelerometerIntervalJNI(interval);
    }


    void CCAccelerometer::update(float x, float y, float z, long sensorTimeStamp) 
    {
        if (_accelDelegate)
        {
            _accelerationValue.x = -((double)x / TG3_GRAVITY_EARTH);
            _accelerationValue.y = -((double)y / TG3_GRAVITY_EARTH);
            _accelerationValue.z = -((double)z / TG3_GRAVITY_EARTH);
            _accelerationValue.timestamp = (double)sensorTimeStamp;

            _accelDelegate->didAccelerate(&_accelerationValue);
        }    
    }
} // end of namespace cococs2d

