#ifndef _TOUCHES_TEST__H_
#define _TOUCHES_TEST__H_

#include "../BaseTest.h"


DEFINE_TEST_SUITE(TouchesTests);

class PongScene : public TestCase
{
public:
    CREATE_FUNC(PongScene);
    
    virtual bool init() override;
};

class Ball;
class Paddle;
class PongLayer : public cocos2d::Layer
{
private:
    Ball*       _ball;
    cocos2d::Vector<Paddle*>    _paddles;
    cocos2d::Vec2     _ballStartingVelocity; 
public:
    CREATE_FUNC(PongLayer);
    PongLayer();
    ~PongLayer();

    void resetAndScoreBallForPlayer(int player);
    void doStep(float delta);
};

#endif
