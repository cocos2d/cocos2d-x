#ifndef _ACCELEROMETER_TEST_H_
#define _ACCELEROMETER_TEST_H_

#include "../testScene.h"

USING_NS_CC;

class AccelerometerTest: public Layer
{
protected:
    Sprite* _ball;
    double    _lastTime;

public:
    AccelerometerTest(void);
    ~AccelerometerTest(void);

    void onAcceleration(Acceleration* acc, Event* event);

    virtual std::string title() const;
    virtual void onEnter() override;
};

class AccelerometerTestScene : public TestScene
{
public:
	AccelerometerTestScene();
    virtual void runThisTest();
};

#endif
