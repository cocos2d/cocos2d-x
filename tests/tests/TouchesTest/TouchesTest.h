#ifndef _TOUCHES_TEST__H_
#define _TOUCHES_TEST__H_

////----#include "cocos2d.h"
#include "../testBasic.h"

using namespace cocos2d;

class PongScene : public TestScene
{
public:
    PongScene();

    virtual void runThisTest();

    virtual void MainMenuCallback(CCObject* pSender);
};

class Ball;
class PongLayer : public CCLayer
{
	Ball*		m_ball;
	CCMutableArray<CCObject *> *m_paddles;
	CCPoint		m_ballStartingVelocity; 
public:
	PongLayer();
	~PongLayer();

	void resetAndScoreBallForPlayer(int player);
	void doStep(ccTime delta);
};

#endif
