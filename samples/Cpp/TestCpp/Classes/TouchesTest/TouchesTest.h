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
class PongLayer : public CCLayer
{
private:
    Ball*       _ball;
    CCArray*    _paddles;
    CCPoint     _ballStartingVelocity; 
public:
    PongLayer();
    ~PongLayer();

    void resetAndScoreBallForPlayer(int player);
    void doStep(float delta);
};

#endif
