#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "cocos2d.h"

USING_NS_CC;

class TestController : public CCLayer
{
public:
    TestController();
    ~TestController();

    void menuCallback(CCObject * pSender);
    void closeCallback(CCObject * pSender);

    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);

private:
    CCPoint m_tBeginPos;
    CCMenu* m_pItemMenu;
};

#endif
