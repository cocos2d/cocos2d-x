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

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void onEnter() override;

    void restartCallback(Ref* sender);
    void nextCallback(Ref* sender);
    void backCallback(Ref* sender);
    void modeCallback(Ref* sender);
protected:
    MotionStreak *streak;
};

class MotionStreakTest1 : public MotionStreakTest
{
protected:
    Node*        _root;
    Node*        _target;

public:
    CREATE_FUNC(MotionStreakTest1);
    virtual void onEnter() override;
    void onUpdate(float delta);
    virtual std::string title() const override;
};

class MotionStreakTest2 : public MotionStreakTest
{
protected:
    Node*        _root;
    Node*        _target;

public:
    CREATE_FUNC(MotionStreakTest2);
    virtual void onEnter() override;
    void onTouchesMoved(const std::vector<Touch*>& touches, Event* event);
    virtual std::string title() const override;
};

class Issue1358 : public MotionStreakTest
{
public:
    CREATE_FUNC(Issue1358);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void onEnter() override;
    virtual void update(float dt);
private:
    Vector2 _center;
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
