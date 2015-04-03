#ifndef _USERDEFAULT_TEST_H_
#define _USERDEFAULT_TEST_H_

#include "cocos2d.h"
#include "../BaseTest.h"

DEFINE_TEST_SUITE(UserDefaultTests);

class UserDefaultTest : public TestCase
{
public:
    CREATE_FUNC(UserDefaultTest);
    UserDefaultTest();
    ~UserDefaultTest();

private:
    void doTest();
};

#endif // _USERDEFAULT_TEST_H_
