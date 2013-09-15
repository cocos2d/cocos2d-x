#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "cocos2d.h"

USING_NS_CC;

class TestController : public Layer
{
public:
    TestController();
    ~TestController();

    void menuCallback(Object * sender);
    void closeCallback(Object * sender);

    virtual void ccTouchesBegan(Set  *touches, Event  *event);
    virtual void ccTouchesMoved(Set  *touches, Event  *event);

private:
    Point _beginPos;
    Menu* _itemMenu;
};

#endif
