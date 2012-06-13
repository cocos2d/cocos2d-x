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

SEL_MenuHandler ButtonTestLayer::onResolveCCBCCMenuSelector(CCObject * pTarget, const char * pSelectorName) {
    return NULL;    
}

SEL_CCControlHandler ButtonTestLayer::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
    if(pTarget == this) {
        if(strcmp(pSelectorName, "onCCControlButtonClicked") == 0) {
            return cccontrol_selector(ButtonTestLayer::onCCControlButtonClicked);
        }
    }
    return NULL;
}

void ButtonTestLayer::onCCControlButtonClicked(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
    printf("onCCControlButtonClicked\n");
}