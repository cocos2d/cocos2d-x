#ifndef _CLICK_AND_MOVE_TEST_H_
#define _CLICK_AND_MOVE_TEST_H_

#include "../testBasic.h"

class ClickAndMoveTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

class MainLayer : public Layer
{
public:
    MainLayer();
    virtual bool onTouchBegan(Touch* touch, Event  *event) override;
    virtual void onTouchEnded(Touch* touch, Event  *event) override;
};

#endif
