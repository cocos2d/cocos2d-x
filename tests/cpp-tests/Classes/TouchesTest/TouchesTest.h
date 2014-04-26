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
class Paddle;
class PongLayer : public Layer
{
private:
    Ball*       _ball;
    Vector<Paddle*>    _paddles;
    Vector2     _ballStartingVelocity; 
public:
    PongLayer();
    ~PongLayer();

    void resetAndScoreBallForPlayer(int player);
    void doStep(float delta);
};

#endif
