#ifndef __ZWOPTEX_TEST_H__
#define __ZWOPTEX_TEST_H__

#include "../testBasic.h"
#include "../BaseTest.h"

class ZwoptexTest : public BaseTest
{
public:
    virtual void onEnter();

    void restartCallback(Object* sender);
    void nextCallback(Object* sender);
    void backCallback(Object* sender);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class ZwoptexGenericTest : public ZwoptexTest
{
public:
    ~ZwoptexGenericTest();
    virtual void onEnter();
    void flipSprites(float dt);
    void startIn05Secs(float dt);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;

protected:
    Sprite * sprite1;
    Sprite * sprite2;
    int counter;
};

class ZwoptexTestScene : public TestScene
{
public:
    virtual void runThisTest();

    CREATE_FUNC(ZwoptexTestScene);
};

#endif // __ZWOPTEX_TEST_H__
