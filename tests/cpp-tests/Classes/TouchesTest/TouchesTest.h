#ifndef _TOUCHES_TEST__H_
#define _TOUCHES_TEST__H_

#include "../BaseTest.h"

USING_NS_CC;

DEFINE_TEST_SUITE(TouchesTests);

class PongScene : public TestCase
{
public:
    CREATE_FUNC(PongScene);
    
    virtual bool init() override;
};

class Ball;
class Paddle;
class PongLayer : public Layer
{
private:
    Ball*       _ball;
    Vector<Paddle*>    _paddles;
    Vec2     _ballStartingVelocity; 
public:
    CREATE_FUNC(PongLayer);
    PongLayer();
    ~PongLayer();

    void resetAndScoreBallForPlayer(int player);
    void doStep(float delta);
};

#endif
