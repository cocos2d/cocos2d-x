#ifndef _MOTION_STREAK_TEST_H_
#define _MOTION_STREAK_TEST_H_

////----#include "cocos2d.h"
#include "../testBasic.h"

//using namespace cocos2d;

class MotionStreakTest : public CCLayer
{
public:
	MotionStreakTest(void);
	~MotionStreakTest(void);

	virtual std::string title();
	virtual void onEnter();

	void restartCallback(CCObject* pSender);
	void nextCallback(CCObject* pSender);
	void backCallback(CCObject* pSender);
};

class MotionStreakTest1 : public MotionStreakTest
{
protected:
	CCNode*		m_root;
	CCNode*		m_target;
	CCMotionStreak*		m_streak;

public:
	virtual void onEnter();
	void onUpdate(ccTime delta);
	virtual std::string title();
};

class MotionStreakTest2 : public MotionStreakTest
{
protected:
	CCNode*		m_root;
	CCNode*		m_target;
	CCMotionStreak*		m_streak;

public:
	virtual void onEnter();
	void ccTouchesMoved(CCSet* touches, CCEvent* event);
	virtual std::string title();
};

class MotionStreakTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

//CCLayer* nextAction();

#endif
