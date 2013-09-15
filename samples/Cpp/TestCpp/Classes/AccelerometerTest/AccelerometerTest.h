#ifndef _ACCELEROMETER_TEST_H_
#define _ACCELEROMETER_TEST_H_

#include "../testBasic.h"

USING_NS_CC;

class AccelerometerTest: public Layer
{
protected:
    Sprite* _ball;
    double    _lastTime;

public:
    AccelerometerTest(void);
    ~AccelerometerTest(void);

    virtual void didAccelerate(Acceleration* pAccelerationValue);

    virtual std::string title();
    virtual void onEnter();
};

class AccelerometerTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
