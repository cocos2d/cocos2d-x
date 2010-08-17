#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "CCLayer.h"

using namespace cocos2d;

class TestController : public CCLayer
{
public:
    TestController();

    void menuCallback(NSObject * pSender);
    void closeCallback(NSObject * pSender);
};

#endif
