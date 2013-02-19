#ifndef _EFFECT_ADVANCED_TEST_H_
#define _EFFECT_ADVANCED_TEST_H_

#include "cocos2d.h"
#include "../testBasic.h"

class EffectAdvanceTextLayer: public CCLayer
{
protected:
    CCTextureAtlas* m_atlas;

    std::string    m_strTitle;

public:
    virtual void onEnter();
    ~EffectAdvanceTextLayer(void);

    virtual std::string title();
    virtual std::string subtitle();

    void restartCallback(CCObject* pSender);
    void nextCallback(CCObject* pSender);
    void backCallback(CCObject* pSender);
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
