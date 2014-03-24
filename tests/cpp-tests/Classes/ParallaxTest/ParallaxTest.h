#ifndef _PARALLAX_TEST_H_
#define _PARALLAX_TEST_H_

#include "../testBasic.h"
#include "../BaseTest.h"

class ParallaxDemo : public BaseTest
{
protected:
    TextureAtlas* _atlas;

public:
    ParallaxDemo(void);
    ~ParallaxDemo(void);

    virtual std::string title() const override;
    virtual void onEnter() override;

    void restartCallback(Ref* sender);
    void nextCallback(Ref* sender);
    void backCallback(Ref* sender);
};

class Parallax1 : public ParallaxDemo
{
protected:
    Node*        _root;
    Node*        _target;
    MotionStreak*        _streak;

public:
    Parallax1();
    virtual std::string title() const override;
};

class Parallax2 : public ParallaxDemo
{
protected:
    Node*        _root;
    Node*        _target;
    MotionStreak*        _streak;

public:
    Parallax2();
    
    void onTouchesMoved(const std::vector<Touch*>& touches, Event  *event);

    virtual std::string title() const override;
};

class Issue2572 : public ParallaxDemo
{
protected:
    ParallaxNode* _paraNode;
    float _moveTimer;
    float _addTimer;
    Vector<Sprite*> _childList;
    ssize_t _preListSize;
    int _printCount;
    
    float _addChildStep;
    float _wholeMoveTime;
    Point _wholeMoveSize;

    virtual void update(float dt) override;
    
public:
    Issue2572();
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class ParallaxTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
