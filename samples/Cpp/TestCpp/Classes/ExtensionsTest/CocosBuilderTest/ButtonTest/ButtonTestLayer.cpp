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

SEL_MenuHandler ButtonTestLayer::onResolveCCBCCMenuItemSelector(Object * pTarget, const char * pSelectorName) {
    return NULL;    
}

Control::Handler ButtonTestLayer::onResolveCCBCCControlSelector(Object * pTarget, const char * pSelectorName) {
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCCControlButtonClicked", ButtonTestLayer::onControlButtonClicked);

    return NULL;
}

bool ButtonTestLayer::onAssignCCBMemberVariable(Object * pTarget, const char * pMemberVariableName, Node * pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCCControlEventLabel", LabelBMFont *, this->mControlEventLabel);

    return false;
}

void ButtonTestLayer::onControlButtonClicked(cocos2d::Object *pSender, cocos2d::extension::Control::EventType pControlEvent) {
    switch(pControlEvent) {
        case Control::EventType::TOUCH_DOWN:
            this->mControlEventLabel->setString("Touch Down.");
            break;
        case Control::EventType::DRAG_INSIDE:
            this->mControlEventLabel->setString("Touch Drag Inside.");
            break;
        case Control::EventType::DRAG_OUTSIDE:
            this->mControlEventLabel->setString("Touch Drag Outside.");
            break;
        case Control::EventType::DRAG_ENTER:
            this->mControlEventLabel->setString("Touch Drag Enter.");
            break;
        case Control::EventType::DRAG_EXIT:
            this->mControlEventLabel->setString("Touch Drag Exit.");
            break;
        case Control::EventType::TOUCH_UP_INSIDE:
            this->mControlEventLabel->setString("Touch Up Inside.");
            break;
        case Control::EventType::TOUCH_UP_OUTSIDE:
            this->mControlEventLabel->setString("Touch Up Outside.");
            break;
        case Control::EventType::TOUCH_CANCEL:
            this->mControlEventLabel->setString("Touch Cancel.");
            break;
        case Control::EventType::VALUE_CHANGED:
            this->mControlEventLabel->setString("Value Changed.");
            break;
        default:
            assert(false); // OH SHIT!
    }
}