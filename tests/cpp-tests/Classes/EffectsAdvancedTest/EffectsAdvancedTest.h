#ifndef _EFFECT_ADVANCED_TEST_H_
#define _EFFECT_ADVANCED_TEST_H_

#include "cocos2d.h"
#include "../BaseTest.h"

DEFINE_TEST_SUITE(EffectAdvanceTests);

class EffectAdvanceBaseTest: public TestCase
{
protected:
    cocos2d::TextureAtlas* _atlas;

    std::string    _title;

    cocos2d::Node* _bgNode;
    cocos2d::Node* _target1;
    cocos2d::Node* _target2;

public:
    virtual void onEnter() override;
    ~EffectAdvanceBaseTest(void);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class Effect1 : public EffectAdvanceBaseTest
{
public:
    CREATE_FUNC(Effect1);
    virtual void onEnter() override;
    virtual std::string title() const override;
};

class Effect2 : public EffectAdvanceBaseTest
{
public:
    CREATE_FUNC(Effect2);
    virtual void onEnter() override;
    virtual std::string title() const override;
};

class Effect3 : public EffectAdvanceBaseTest
{
public:
    CREATE_FUNC(Effect3);
    virtual void onEnter() override;
    virtual std::string title() const override;
};

class Effect4 : public EffectAdvanceBaseTest
{
public:
    CREATE_FUNC(Effect4);
    virtual void onEnter() override;
    virtual std::string title() const override;
};

class Effect5 : public EffectAdvanceBaseTest
{
public:
    CREATE_FUNC(Effect5);
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
};

class Issue631 : public EffectAdvanceBaseTest
{
public:
    CREATE_FUNC(Issue631);
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

#endif
