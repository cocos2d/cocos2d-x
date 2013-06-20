#include "TestHeaderLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

SEL_MenuHandler TestHeaderLayer::onResolveCCBMenuItemSelector(Object * pTarget, const char * pSelectorName) {
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onBackClicked", TestHeaderLayer::onBackClicked);

    return NULL;    
}

SEL_CCControlHandler TestHeaderLayer::onResolveCCBControlSelector(Object * pTarget, const char * pSelectorName) {

    return NULL;
}

void TestHeaderLayer::onNodeLoaded(cocos2d::Node * pNode, cocos2d::extension::NodeLoader * pNodeLoader)
{
    CCLOG("TestHeaderLayer::onNodeLoaded");
}

void TestHeaderLayer::onBackClicked(cocos2d::Object *pSender) {
    Director::sharedDirector()->popScene();
}