#ifndef _ACTIONS__EASE_TEST_H_
#define _ACTIONS__EASE_TEST_H_

////----#include "cocos2d.h"
#include "../testBasic.h"
#include "../BaseTest.h"

USING_NS_CC;

class EaseSpriteDemo : public BaseTest
{
protected:
    Sprite*    _grossini;
    Sprite*    _tamara;
    Sprite*    _kathia;

    std::string    _title;

public:
    EaseSpriteDemo(void);
    ~EaseSpriteDemo(void);

    virtual std::string title() const override;
    virtual void onEnter();

    void restartCallback(Object* sender);
    void nextCallback(Object* sender);
    void backCallback(Object* sender);

    void positionForTwo();
};

class SpriteEase : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string title() const override;

    void testStopAction(float dt);
};

class SpriteEaseInOut : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string title() const override;
};

class SpriteEaseExponential : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string title() const override;
};

class SpriteEaseExponentialInOut : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string title() const override;
};

class SpriteEaseSine : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string title() const override;
};

class SpriteEaseSineInOut : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string title() const override;
};

class SpriteEaseElastic : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string title() const override;
};

class SpriteEaseElasticInOut : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string title() const override;
};

class SpriteEaseBounce : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string title() const override;
};

class SpriteEaseBounceInOut : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string title() const override;
};

class SpriteEaseBack : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string title() const override;
};

class SpriteEaseBackInOut : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string title() const override;
};

class SpeedTest : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string title() const override;

    void altertime(float dt);
};

class ActionsEaseTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
