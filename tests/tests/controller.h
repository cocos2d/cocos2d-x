#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "cocos2d.h"
#include "tests.h"

using namespace cocos2d;

class TestController : public CCLayer
{
public:
    TestController();
    ~TestController();

    void menuCallback(NSObject * pSender);
    void closeCallback(NSObject * pSender);

    virtual void ccTouchesBegan(NSSet *pTouches, UIEvent *pEvent);
    virtual void ccTouchesMoved(NSSet *pTouches, UIEvent *pEvent);

private:

    CGPoint m_tBeginPos;
    CCMenuItemLabel * m_pMenuItems[TESTS_COUNT];
    CCMenu* m_pItmeMenu;
};

#endif
