#ifndef _USERDEFAULT_TEST_H_
#define _USERDEFAULT_TEST_H_

#include "cocos2d.h"
#include "../testBasic.h"

class UserDefaultTest : public Layer
{
public:
    UserDefaultTest();
    ~UserDefaultTest();

private:
    void doTest();
};

class UserDefaultTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif // _USERDEFAULT_TEST_H_
