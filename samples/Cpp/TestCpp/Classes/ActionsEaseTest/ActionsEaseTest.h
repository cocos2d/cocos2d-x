#ifndef _ACTIONS__EASE_TEST_H_
#define _ACTIONS__EASE_TEST_H_

////----#include "cocos2d.h"
#include "../testBasic.h"

USING_NS_CC;

class EaseSpriteDemo : public CCLayer
{
protected:
    CCSprite*    m_grossini;
    CCSprite*    m_tamara;
    CCSprite*    m_kathia;

    std::string    m_strTitle;

public:
    EaseSpriteDemo(void);
    ~EaseSpriteDemo(void);

    virtual std::string title();
    virtual void onEnter();

    void restartCallback(CCObject* pSender);
    void nextCallback(CCObject* pSender);
    void backCallback(CCObject* pSender);

    void positionForTwo();
};

class SpriteEase : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string title();

    void testStopAction(float dt);
};

class SpriteEaseInOut : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string title();
};

class SpriteEaseExponential : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string title();
};

class SpriteEaseExponentialInOut : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string title();
};

class SpriteEaseSine : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string title();
};

class SpriteEaseSineInOut : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string title();
};

class SpriteEaseElastic : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string title();
};

class SpriteEaseElasticInOut : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string title();
};

class SpriteEaseBounce : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string title();
};

class SpriteEaseBounceInOut : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string title();
};

class SpriteEaseBack : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string title();
};

class SpriteEaseBackInOut : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string title();
};

class SpeedTest : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string title();

    void altertime(float dt);
};

class ActionsEaseTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
