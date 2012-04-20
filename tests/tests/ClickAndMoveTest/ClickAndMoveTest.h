#ifndef _CLICK_AND_MOVE_TEST_H_
#define _CLICK_AND_MOVE_TEST_H_

#include "../testBasic.h"

class ClickAndMoveTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

class MainLayer : public CCLayer
{
public:
    MainLayer();
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
};

#endif
