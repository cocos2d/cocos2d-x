#ifndef _CLICK_AND_MOVE_TEST_H_
#define _CLICK_AND_MOVE_TEST_H_

#include "../BaseTest.h"

DEFINE_TEST_SUITE(ClickAndMoveTest);

class ClickAndMoveTestCase : public TestCase
{
public:
    CREATE_FUNC(ClickAndMoveTestCase);

    ClickAndMoveTestCase();
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
};

#endif
