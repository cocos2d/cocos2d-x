#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

// #include "CCLayer.h"
// #include "CCMenu.h"
#include "cocos2d.h"

using namespace cocos2d;

#define ITEM_EVERYPAGE              9

class TestController : public CCLayer
{
public:
    TestController();
    ~TestController();

    void menuCallback(NSObject * pSender);
    void closeCallback(NSObject * pSender);

    void nextPageCallback(NSObject * pSender);
    void prePageCallback(NSObject * pSender);

    void updateItemsText();

private:
    CCMenuItemLabel * m_pMenuItems[ITEM_EVERYPAGE];

    unsigned int m_nUIDs[ITEM_EVERYPAGE];
};

#endif
