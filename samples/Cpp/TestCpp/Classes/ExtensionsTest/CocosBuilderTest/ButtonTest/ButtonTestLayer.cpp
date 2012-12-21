#include "ButtonTestLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

ButtonTestLayer::ButtonTestLayer()
: mCCControlEventLabel(NULL)
{}

ButtonTestLayer::~ButtonTestLayer()
{
    CC_SAFE_RELEASE(mCCControlEventLabel);
}

SEL_MenuHandler ButtonTestLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) {
    return NULL;    
}

SEL_CCControlHandler ButtonTestLayer::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCCControlButtonClicked", ButtonTestLayer::onCCControlButtonClicked);

    return NULL;
}

bool ButtonTestLayer::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCCControlEventLabel", CCLabelBMFont *, this->mCCControlEventLabel);

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