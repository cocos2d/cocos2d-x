#include "ButtonTestLayer.h"

#include "extensions/CCBReader/CCBReader.h"

USING_NS_CC;
USING_NS_CC_EXT;

ButtonTestLayer * ButtonTestLayer::node() { 
    ButtonTestLayer * ptr = new ButtonTestLayer();
    if(ptr && ptr->init()) { 
        ptr->autorelease();   
        return ptr;
    } 
    CC_SAFE_DELETE(ptr);
    return NULL;
}

SEL_MenuHandler ButtonTestLayer::onResolveCCBCCMenuSelector(CCObject * pTarget, CCString * pSelectorName) {
    return NULL;    
}

SEL_CCControlHandler ButtonTestLayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName) {
    if(pTarget == this) {
        if(pSelectorName->compare("onCCControlButtonClicked") == 0) {
            return cccontrol_selector(ButtonTestLayer::onCCControlButtonClicked);
        }
    }
    return NULL;
}

void ButtonTestLayer::onCCControlButtonClicked(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
    CCLOG("onCCControlButtonClicked\n");
}