#include "ButtonTestLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

ButtonTestLayer::ButtonTestLayer()
: mControlEventLabel(NULL)
{}

ButtonTestLayer::~ButtonTestLayer()
{
    CC_SAFE_RELEASE(mControlEventLabel);
}

SEL_MenuHandler ButtonTestLayer::onResolveCCBMenuItemSelector(Object * pTarget, const char * pSelectorName) {
    return NULL;    
}

SEL_CCControlHandler ButtonTestLayer::onResolveCCBControlSelector(Object * pTarget, const char * pSelectorName) {
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onControlButtonClicked", ButtonTestLayer::onControlButtonClicked);

    return NULL;
}

bool ButtonTestLayer::onAssignCCBMemberVariable(Object * pTarget, const char * pMemberVariableName, Node * pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mControlEventLabel", LabelBMFont *, this->mControlEventLabel);

    return false;
}

void ButtonTestLayer::onControlButtonClicked(cocos2d::Object *pSender, cocos2d::extension::ControlEvent pControlEvent) {
    switch(pControlEvent) {
        case ControlEventTouchDown:
            this->mControlEventLabel->setString("Touch Down.");
            break;
        case ControlEventTouchDragInside:
            this->mControlEventLabel->setString("Touch Drag Inside.");
            break;
        case ControlEventTouchDragOutside:
            this->mControlEventLabel->setString("Touch Drag Outside.");
            break;
        case ControlEventTouchDragEnter:
            this->mControlEventLabel->setString("Touch Drag Enter.");
            break;
        case ControlEventTouchDragExit:
            this->mControlEventLabel->setString("Touch Drag Exit.");
            break;
        case ControlEventTouchUpInside:
            this->mControlEventLabel->setString("Touch Up Inside.");
            break;
        case ControlEventTouchUpOutside:
            this->mControlEventLabel->setString("Touch Up Outside.");
            break;
        case ControlEventTouchCancel:
            this->mControlEventLabel->setString("Touch Cancel.");
            break;
        case ControlEventValueChanged:
            this->mControlEventLabel->setString("Value Changed.");
            break;
        default:
            assert(false); // OH SHIT!
    }
}