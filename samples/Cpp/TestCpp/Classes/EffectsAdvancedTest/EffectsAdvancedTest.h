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

public:
    virtual void onEnter();
    ~EffectAdvanceTextLayer(void);

    virtual std::string title();
    virtual std::string subtitle();

    void restartCallback(Object* pSender);
    void nextCallback(Object* pSender);
    void backCallback(Object* pSender);
};

class Effect1 : public EffectAdvanceTextLayer
{
public:
    virtual void onEnter();
    virtual std::string title();
};

class Effect2 : public EffectAdvanceTextLayer
{
public:
    virtual void onEnter();
    virtual std::string title();
};

class Effect3 : public EffectAdvanceTextLayer
{
public:
    virtual void onEnter();
    virtual std::string title();
};

class Effect4 : public EffectAdvanceTextLayer
{
public:
    virtual void onEnter();
    virtual std::string title();
};

class Effect5 : public EffectAdvanceTextLayer
{
public:
    virtual void onEnter();
    virtual void onExit();
    virtual std::string title();
};

class Issue631 : public EffectAdvanceTextLayer
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
};

class EffectAdvanceScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
