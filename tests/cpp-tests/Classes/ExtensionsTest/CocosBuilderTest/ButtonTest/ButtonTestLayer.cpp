#include "ButtonTestLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

ButtonTestLayer::ButtonTestLayer()
: mControlEventLabel(nullptr)
{}

ButtonTestLayer::~ButtonTestLayer()
{
    CC_SAFE_RELEASE(mControlEventLabel);
}

SEL_MenuHandler ButtonTestLayer::onResolveCCBCCMenuItemSelector(Ref * pTarget, const char * pSelectorName) {
    return nullptr;    
}

Control::Handler ButtonTestLayer::onResolveCCBCCControlSelector(Ref * pTarget, const char * pSelectorName) {
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCCControlButtonClicked", ButtonTestLayer::onControlButtonClicked);

    return nullptr;
}

bool ButtonTestLayer::onAssignCCBMemberVariable(Ref * pTarget, const char * pMemberVariableName, Node * pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCCControlEventLabel", Label *, this->mControlEventLabel);

    return false;
}

void ButtonTestLayer::onControlButtonClicked(cocos2d::Ref *pSender, Control::EventType pControlEvent) {
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
