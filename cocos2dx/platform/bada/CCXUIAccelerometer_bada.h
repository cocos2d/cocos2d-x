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

#ifndef __PLATFORM_BADA_UIACCELEROMETER_H__
#define __PLATFORM_BADA_UIACCELEROMETER_H__

#include "CCUIAccelerometerDelegate.h"
#include "NSMutableArray.h"
#include "ccxCommon.h"

#include <FUixSensorManager.h>
#include <FUixSensorTypes.h>
#include <FUixSensorData.h>

namespace   cocos2d {

/**
@brief
UIAccelerometerHandler
Object than contains the UIAccelerometerDelegate.
*/
class CCX_DLL UIAccelerometerHandler : public NSObject
{
public:
    virtual ~UIAccelerometerHandler(void);

    /** delegate */
    UIAccelerometerDelegate* getDelegate();
    void setDelegate(UIAccelerometerDelegate *pDelegate);

    /** initializes a UIAccelerometerHandler with a delegate */
    virtual bool initWithDelegate(UIAccelerometerDelegate *pDelegate);

public:
    /** allocates a AccelerometerHandler with a delegate */
    static UIAccelerometerHandler* handlerWithDelegate(UIAccelerometerDelegate *pDelegate);

protected:
    UIAccelerometerDelegate* m_pDelegate;
};

/**
@brief 
The UIAccelerometer class lets you register to receive
acceleration-related data from the onboard hardware.
*/
class CCX_DLL UIAccelerometer :
	public Osp::Uix::ISensorEventListener
{
public:
    UIAccelerometer();
    ~UIAccelerometer();

    /**
    @brief Returns the shared accelerometer object for the system.
    */
    static UIAccelerometer* sharedAccelerometer();

    /**
    @brief add delegate to concern accelerometer sensor
    */
    void addDelegate(UIAccelerometerDelegate* pDelegate);

    /**
    @brief remove the delegate from the delegates who concern Accelerometer Sensor
    */
    void removeDelegate(UIAccelerometerDelegate* pDelegate);

    /**
    @brief call delegates' didAccelerate function
    */
    void didAccelerate(UIAcceleration* pAccelerationValue);

    virtual void OnDataReceived(Osp::Uix::SensorType sensorType, Osp::Uix::SensorData& sensorData , result r);
protected:
    typedef NSMutableArray<UIAccelerometerHandler*> AccDelegateArray;

    AccDelegateArray*               m_pDelegates;
    Osp::Uix::SensorManager*	m_pSensor;
//    TCOM_Sensors_DataType_Client*   m_pSensor;
};

}//namespace   cocos2d 

#endif
