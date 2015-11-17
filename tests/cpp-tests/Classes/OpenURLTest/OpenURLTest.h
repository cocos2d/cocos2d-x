#ifndef _OPEN_URL_TEST_H_
#define _OPEN_URL_TEST_H_

#include "cocos2d.h"
#include "../BaseTest.h"

DEFINE_TEST_SUITE(OpenURLTests);

class OpenURLTest : public TestCase
{
public:
    CREATE_FUNC(OpenURLTest);
    OpenURLTest();
    ~OpenURLTest();

    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
private:
    cocos2d::Label* _label;
};

#endif // _OPEN_URL_TEST_H_
