#ifndef _TOUCHES_TEST__H_
#define _TOUCHES_TEST__H_

////----#include "cocos2d.h"
#include "../testBasic.h"

using namespace cocos2d;

class PongScene : public TestScene
{
public:
    PongScene();

	virtual void onExit();
    virtual void runThisTest();
};

class Ball;
class PongLayer : public CCLayer
{
	Ball*		m_ball;
	NSMutableArray<NSObject *> *m_paddles;
	CGPoint		m_ballStartingVelocity; 
public:
	PongLayer();
	~PongLayer();

	void resetAndScoreBallForPlayer(int player);
	void doStep(ccTime delta);
};

#endif
