#include "CCScrollViewWithMenu.h"
#include "CCDirector.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "menu_nodes/CCMenu.h"

USING_NS_CC;
USING_NS_CC_EXT;

void CCScrollViewWithMenu::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, false);
}