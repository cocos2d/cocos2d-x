#include "CCScrollMenu.h"
USING_NS_CC;

CCScrollMenu::CCScrollMenu()
{

}

CCScrollMenu::~CCScrollMenu() {
}

void CCScrollMenu::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, false);
}

void CCScrollMenu::ccTouchMoved(CCTouch* touch, CCEvent* event) {
    CC_UNUSED_PARAM(event);
    this->ccTouchCancelled(touch, event);
}

void CCScrollMenu::ccTouchEnded(CCTouch *touch, CCEvent* event)
{
    if (m_eState != kCCMenuStateTrackingTouch) return;
    CCMenu::ccTouchEnded(touch, event);
}

void CCScrollMenu::ccTouchCancelled(CCTouch *touch, CCEvent* event)
{
    if (m_eState != kCCMenuStateTrackingTouch) return;
    CCMenu::ccTouchCancelled(touch, event);
}

