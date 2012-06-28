#include "TestHeaderLayer.h"

#include "extensions/CCBReader/CCBReader.h"

USING_NS_CC;
USING_NS_CC_EXT;

SEL_MenuHandler TestHeaderLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, CCString * pSelectorName) {
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onBackClicked", TestHeaderLayer::onBackClicked);

    return NULL;    
}

SEL_CCControlHandler TestHeaderLayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName) {

    return NULL;
}

void TestHeaderLayer::onBackClicked(cocos2d::CCObject *pSender) {
    CCDirector::sharedDirector()->popScene();
}