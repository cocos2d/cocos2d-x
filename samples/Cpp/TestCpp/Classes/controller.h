#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "cocos2d.h"

USING_NS_CC;

class TestController : public Layer
{
public:
    TestController();
    ~TestController();

    void menuCallback(Object * pSender);
    void closeCallback(Object * pSender);

    virtual void ccTouchesBegan(Set *pTouches, Event *pEvent);
    virtual void ccTouchesMoved(Set *pTouches, Event *pEvent);

private:
    Point _beginPos;
    Menu* _itemMenu;
};

#endif
