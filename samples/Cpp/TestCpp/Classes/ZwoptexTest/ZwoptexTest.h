#ifndef __ZWOPTEX_TEST_H__
#define __ZWOPTEX_TEST_H__

#include "../testBasic.h"

class ZwoptexTest : public CCLayer
{
public:
    virtual void onEnter();

    void restartCallback(CCObject* pSender);
    void nextCallback(CCObject* pSender);
    void backCallback(CCObject* pSender);

    virtual std::string title();
    virtual std::string subtitle();
};

class ZwoptexGenericTest : public ZwoptexTest
{
public:
    ~ZwoptexGenericTest();
    virtual void onEnter();
    void flipSprites(float dt);
    void startIn05Secs(float dt);

    virtual std::string title();
    virtual std::string subtitle();

protected:
    CCSprite * sprite1;
    CCSprite * sprite2;
    int counter;
};

class ZwoptexTestScene : public TestScene
{
public:
    virtual void runThisTest();

    CREATE_FUNC(ZwoptexTestScene);
};

#endif // __ZWOPTEX_TEST_H__
