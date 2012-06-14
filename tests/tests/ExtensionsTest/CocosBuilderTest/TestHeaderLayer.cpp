#include "TestHeaderLayer.h"

#include "extensions/CCBReader/CCBReader.h"

USING_NS_CC;
USING_NS_CC_EXT;

TestHeaderLayer * TestHeaderLayer::node() { 
    TestHeaderLayer * ptr = new TestHeaderLayer();
    if(ptr && ptr->init()) { 
        ptr->autorelease();   
        return ptr;
    } 
    CC_SAFE_DELETE(ptr);
    return NULL;
}

SEL_MenuHandler TestHeaderLayer::onResolveCCBCCMenuSelector(CCObject * pTarget, CCString * pSelectorName) {
    if(pTarget == this) {
        if(pSelectorName->compare("onBackClicked") == 0) {
            return menu_selector(TestHeaderLayer::onBackClicked);
        }
    }
    return NULL;    
}

SEL_CCControlHandler TestHeaderLayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName) {

    return NULL;
}

void TestHeaderLayer::onBackClicked(cocos2d::CCObject *pSender) {
    CCDirector::sharedDirector()->popScene();
}