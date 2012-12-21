#ifndef _ACCELEROMETER_TEST_H_
#define _ACCELEROMETER_TEST_H_

#include "../testBasic.h"

USING_NS_CC;

class AccelerometerTest: public CCLayer
{
protected:
    CCSprite* m_pBall;
    double    m_fLastTime;

public:
    AccelerometerTest(void);
    ~AccelerometerTest(void);

    virtual void didAccelerate(CCAcceleration* pAccelerationValue);

    virtual std::string title();
    virtual void onEnter();
};

class AccelerometerTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
