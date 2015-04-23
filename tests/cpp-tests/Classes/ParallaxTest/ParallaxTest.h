#ifndef _PARALLAX_TEST_H_
#define _PARALLAX_TEST_H_

#include "../BaseTest.h"

DEFINE_TEST_SUITE(ParallaxTests);

class ParallaxDemo : public TestCase
{
protected:
    cocos2d::TextureAtlas* _atlas;
};

class Parallax1 : public ParallaxDemo
{
protected:
    cocos2d::Node*        _root;
    cocos2d::Node*        _target;
    cocos2d::MotionStreak*        _streak;

public:
    CREATE_FUNC(Parallax1);
    Parallax1();
    virtual std::string title() const override;
};

class Parallax2 : public ParallaxDemo
{
protected:
    cocos2d::Node*        _root;
    cocos2d::Node*        _target;
    cocos2d::MotionStreak*        _streak;

public:
    CREATE_FUNC(Parallax2);
    Parallax2();
    
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);

    virtual std::string title() const override;
};

class Issue2572 : public ParallaxDemo
{
protected:
    cocos2d::ParallaxNode* _paraNode;
    float _moveTimer;
    float _addTimer;
    cocos2d::Vector<cocos2d::Sprite*> _childList;
    ssize_t _preListSize;
    int _printCount;
    
    float _addChildStep;
    float _wholeMoveTime;
    cocos2d::Vec2 _wholeMoveSize;

    virtual void update(float dt) override;
    
public:
    CREATE_FUNC(Issue2572);
    Issue2572();
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

#endif
