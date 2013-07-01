#ifndef _MOTION_STREAK_TEST_H_
#define _MOTION_STREAK_TEST_H_

////----#include "cocos2d.h"
#include "../testBasic.h"
#include "../BaseTest.h"

//USING_NS_CC;

class MotionStreakTest : public BaseTest
{
public:
    MotionStreakTest(void);
    ~MotionStreakTest(void);

    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();

    void restartCallback(Object* pSender);
    void nextCallback(Object* pSender);
    void backCallback(Object* pSender);
    void modeCallback(Object* pSender);
protected:
    MotionStreak *streak;
};

class MotionStreakTest1 : public MotionStreakTest
{
protected:
    Node*        _root;
    Node*        _target;

public:
    virtual void onEnter();
    void onUpdate(float delta);
    virtual std::string title();
};

class MotionStreakTest2 : public MotionStreakTest
{
protected:
    Node*        _root;
    Node*        _target;

public:
    virtual void onEnter();
    void ccTouchesMoved(Set* touches, Event* event);
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
    Point _center;
    float _radius;
    float _angle;
};

class MotionStreakTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

//CCLayer* nextAction();

#endif
