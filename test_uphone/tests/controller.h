#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "CCLayer.h"

using namespace cocos2d;

class TestController : public CCLayer
{
public:
    TestController();

    virtual void onEnter();

    virtual bool ccTouchBegan(CCTouch *pTouch, UIEvent *pEvent);
    virtual void registerWithTouchDispatcher();
};

// #include "CCScene.h"
// 
// CCScene* NextTest();
// CCScene* PreTest();
// CCScene* CurrentTest();
// 
// enum
// {
//     ActionsTest = 0,
//     TestsCount,
// };

#endif
