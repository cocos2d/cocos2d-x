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

bool ButtonTestLayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode) {
    if(pTarget == this) {
        if(strcmp(pMemberVariableName->getCString(), "mCCControlEventLabel") == 0) {
            this->mCCControlEventLabel = dynamic_cast<CCLabelBMFont *>(pNode);
            CC_ASSERT(this->mCCControlEventLabel);
            this->mCCControlEventLabel->retain();
            return true;
        }
    }
    return false;
}

void ButtonTestLayer::onCCControlButtonClicked(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
    switch(pCCControlEvent) {
        case CCControlEventTouchDown:
            this->mCCControlEventLabel->setString("Touch Down.");
            break;
        case CCControlEventTouchDragInside:
            this->mCCControlEventLabel->setString("Touch Drag Inside.");
            break;
        case CCControlEventTouchDragOutside:
            this->mCCControlEventLabel->setString("Touch Drag Outside.");
            break;
        case CCControlEventTouchDragEnter:
            this->mCCControlEventLabel->setString("Touch Drag Enter.");
            break;
        case CCControlEventTouchDragExit:
            this->mCCControlEventLabel->setString("Touch Drag Exit.");
            break;
        case CCControlEventTouchUpInside:
            this->mCCControlEventLabel->setString("Touch Up Inside.");
            break;
        case CCControlEventTouchUpOutside:
            this->mCCControlEventLabel->setString("Touch Up Outside.");
            break;
        case CCControlEventTouchCancel:
            this->mCCControlEventLabel->setString("Touch Cancel.");
            break;
        case CCControlEventValueChanged:
            this->mCCControlEventLabel->setString("Value Changed.");
            break;
        default:
            assert(false); // OH SHIT!
    }
}