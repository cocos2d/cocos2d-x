#ifndef _PARALLAX_TEST_H_
#define _PARALLAX_TEST_H_

#include "../BaseTest.h"

DEFINE_TEST_SUITE(ParallaxTests);

class ParallaxDemo : public TestCase
{
protected:
    TextureAtlas* _atlas;
};

class Parallax1 : public ParallaxDemo
{
protected:
    Node*        _root;
    Node*        _target;
    MotionStreak*        _streak;

public:
    CREATE_FUNC(Parallax1);
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
    CREATE_FUNC(Parallax2);
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
    Vec2 _wholeMoveSize;

    virtual void update(float dt) override;
    
public:
    CREATE_FUNC(Issue2572);
    Issue2572();
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

#endif
