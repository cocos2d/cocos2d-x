#include "CCScrollViewWithMenu.h"

USING_NS_CC;

NS_CC_EXT_BEGIN

void CCScrollViewWithMenu::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()
        ->getTouchDispatcher()
        ->addTargetedDelegate(this, kCCMenuHandlerPriority, false);
}

NS_CC_EXT_END