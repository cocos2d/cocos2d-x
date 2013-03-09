#ifndef _MOTION_STREAK_TEST_H_
#define _MOTION_STREAK_TEST_H_

////----#include "cocos2d.h"
#include "../testBasic.h"

//USING_NS_CC;

class MotionStreakTest : public CCLayer
{
public:
    MotionStreakTest(void);
    ~MotionStreakTest(void);

    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();

    void restartCallback(CCObject* pSender);
    void nextCallback(CCObject* pSender);
    void backCallback(CCObject* pSender);
    void modeCallback(CCObject* pSender);
protected:
    CCMotionStreak *streak;
};

class MotionStreakTest1 : public MotionStreakTest
{
protected:
    CCNode*        m_root;
    CCNode*        m_target;

public:
    virtual void onEnter();
    void onUpdate(float delta);
    virtual std::string title();
};

class MotionStreakTest2 : public MotionStreakTest
{
protected:
    CCNode*        m_root;
    CCNode*        m_target;

public:
    virtual void onEnter();
    void ccTouchesMoved(CCSet* touches, CCEvent* event);
    virtual std::string title();
};

class Issue1358 : public MotionStreakTest
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();
    virtual void update(float dt);
private:
    CCPoint m_center;
    float m_fRadius;
    float m_fAngle;
};

class MotionStreakTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

//CCLayer* nextAction();

#endif
