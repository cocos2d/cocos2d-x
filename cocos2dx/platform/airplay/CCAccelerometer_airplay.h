#ifndef __PLATFORM_AIRPLAY_ACCELEROMETER_H__
#define __PLATFORM_AIRPLAY_ACCELEROMETER_H__

#include "CCAccelerometerDelegate.h"
#include "CCMutableArray.h"
#include "ccCommon.h"


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
    /** allocates a CCAccelerometerHandler with a delegate */
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

};

}//namespace   cocos2d 

#endif
