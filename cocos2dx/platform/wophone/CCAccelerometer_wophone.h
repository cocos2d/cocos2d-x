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

#ifndef __PLATFORM_WOPHONE_UIACCELEROMETER_H__
#define __PLATFORM_WOPHONE_UIACCELEROMETER_H__

#include "CCAccelerometerDelegate.h"
#include "TG3.h"
#include "CCMutableArray.h"
#include "CCCommon.h"
#include "TCOM_Sensors_Interface.h"

namespace   cocos2d {

/**
@brief
CCAccelerometerHandler
Object than contains the CCAccelerometerDelegate.
*/
class CC_DLL CCAccelerometerHandler : public CCObject
{
public:
    virtual ~CCAccelerometerHandler(void);

    /** delegate */
    CCAccelerometerDelegate* getDelegate();
    void setDelegate(CCAccelerometerDelegate *pDelegate);

    /** initializes a CCAccelerometerHandler with a delegate */
    virtual bool initWithDelegate(CCAccelerometerDelegate *pDelegate);

public:
    /** allocates a AccelerometerHandler with a delegate */
    static CCAccelerometerHandler* handlerWithDelegate(CCAccelerometerDelegate *pDelegate);

protected:
    CCAccelerometerDelegate* m_pDelegate;
};

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

    /**
    @brief add delegate to concern accelerometer sensor
    */
    void addDelegate(CCAccelerometerDelegate* pDelegate);

    /**
    @brief remove the delegate from the delegates who concern Accelerometer Sensor
    */
    void removeDelegate(CCAccelerometerDelegate* pDelegate);

    /**
    @brief call delegates' didAccelerate function
    */
    void didAccelerate(CCAcceleration* pAccelerationValue);

protected:
    typedef CCMutableArray<CCAccelerometerHandler*> AccDelegateArray;

    AccDelegateArray*               m_pDelegates;
    TCOM_Sensors_DataType_Client*   m_pSensor;
};

}//namespace   cocos2d 

#endif
