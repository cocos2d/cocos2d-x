#ifndef _CLICK_AND_MOVE_TEST_H_
#define _CLICK_AND_MOVE_TEST_H_

#include "../BaseTest.h"

DEFINE_TEST_SUITE(ClickAndMoveTest);

class ClickAndMoveTestCase : public TestCase
{
public:
    CREATE_FUNC(ClickAndMoveTestCase);

    ClickAndMoveTestCase();
    bool onTouchBegan(Touch* touch, Event  *event);
    void onTouchEnded(Touch* touch, Event  *event);
};

#endif
