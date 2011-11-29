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

#ifndef __PLATFORM_BADA_ACCELEROMETER_H__
#define __PLATFORM_BADA_ACCELEROMETER_H__

#include "CCAccelerometerDelegate.h"
#include "CCCommon.h"

#include <FUixSensorManager.h>
#include <FUixSensorTypes.h>
#include <FUixSensorData.h>

namespace   cocos2d {

class CC_DLL CCAccelerometer :
	public Osp::Uix::ISensorEventListener
{
public:
    CCAccelerometer();
    ~CCAccelerometer();
    static CCAccelerometer* sharedAccelerometer();

    void setDelegate(CCAccelerometerDelegate* pDelegate);
    virtual void OnDataReceived(Osp::Uix::SensorType sensorType, Osp::Uix::SensorData& sensorData , result r);
private:
    void setEnable(bool bEnable);

	CCAccelerometerDelegate* m_pAccelDelegate;
	Osp::Uix::SensorManager* m_pSensor;
	bool m_bEnabled;
};

}//namespace   cocos2d 

#endif
