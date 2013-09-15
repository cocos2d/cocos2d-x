#ifndef _TOUCHES_TEST__H_
#define _TOUCHES_TEST__H_

////----#include "cocos2d.h"
#include "../testBasic.h"

USING_NS_CC;

class PongScene : public TestScene
{
public:
    PongScene();

    virtual void runThisTest();
};

class Ball;
class PongLayer : public Layer
{
private:
    Ball*       _ball;
    Array*    _paddles;
    Point     _ballStartingVelocity; 
public:
    PongLayer();
    ~PongLayer();

    void resetAndScoreBallForPlayer(int player);
    void doStep(float delta);
};

#endif
