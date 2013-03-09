/****************************************************************************
 Copyright (c) 2011      cocos2d-x.org   http://cocos2d-x.org
 Copyright (c) 2011      Максим Аксенов
 Copyright (c) 2011      Giovanni Zito, Francis Styck

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
#ifndef __PLATFORM_MARMALADE_ACCELEROMETER_H__
#define __PLATFORM_MARMALADE_ACCELEROMETER_H__

#include "CCAccelerometerDelegate.h"
//#include "CCMutableArray.h"
#include "ccCommon.h"


namespace   cocos2d {

/**
@brief 
The CCAccelerometer class lets you register to receive
acceleration-related data from the onboard hardware.
*/
class CC_DLL CCAccelerometer
{
public:
    CCAccelerometer();
    ~CCAccelerometer();

    /**
    @brief Returns the shared accelerometer object for the system.
    */
    static CCAccelerometer* sharedAccelerometer();

	void setDelegate(CCAccelerometerDelegate* pDelegate);
    void setAccelerometerInterval(float interval) {CC_UNUSED_PARAM(interval);};
	void update(float x, float y, float z, uint64 sensorTimeStamp);

private:
	static CCAccelerometer* m_spCCAccelerometer;
	CCAccelerometerDelegate* m_pAccelDelegate;
	CCAcceleration m_obAccelerationValue;
};

}//namespace   cocos2d 

#endif
