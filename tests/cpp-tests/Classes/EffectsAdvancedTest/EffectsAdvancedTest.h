#ifndef _EFFECT_ADVANCED_TEST_H_
#define _EFFECT_ADVANCED_TEST_H_

#include "cocos2d.h"
#include "../testBasic.h"
#include "../BaseTest.h"

class EffectAdvanceTextLayer: public BaseTest
{
protected:
    TextureAtlas* _atlas;

    std::string    _title;

    Node* _bgNode;
    Node* _target1;
    Node* _target2;

public:
    virtual void onEnter() override;
    ~EffectAdvanceTextLayer(void);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void restartCallback(Ref* sender);
    void nextCallback(Ref* sender);
    void backCallback(Ref* sender);
};

class Effect1 : public EffectAdvanceTextLayer
{
public:
    virtual void onEnter() override;
    virtual std::string title() const override;
};

class Effect2 : public EffectAdvanceTextLayer
{
public:
    virtual void onEnter() override;
    virtual std::string title() const override;
};

class Effect3 : public EffectAdvanceTextLayer
{
public:
    virtual void onEnter() override;
    virtual std::string title() const override;
};

class Effect4 : public EffectAdvanceTextLayer
{
public:
    virtual void onEnter() override;
    virtual std::string title() const override;
};

class Effect5 : public EffectAdvanceTextLayer
{
public:
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
};

class Issue631 : public EffectAdvanceTextLayer
{
public:
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class EffectAdvanceScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
