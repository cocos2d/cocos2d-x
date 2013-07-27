#include "TimelineCallbackTestLayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
USING_NS_CC_EXT;

TimelineCallbackTestLayer::TimelineCallbackTestLayer()
: _helloLabel(NULL)
{}

TimelineCallbackTestLayer::~TimelineCallbackTestLayer()
{
    CC_SAFE_RELEASE(_helloLabel);
    CocosDenshion::SimpleAudioEngine::end();
}

SEL_MenuHandler TimelineCallbackTestLayer::onResolveCCBCCMenuItemSelector(Object * pTarget, const char * pSelectorName) {
    return NULL;
}

Control::Handler TimelineCallbackTestLayer::onResolveCCBCCControlSelector(Object * pTarget, const char * pSelectorName) {
    return NULL;
}

SEL_CallFuncN TimelineCallbackTestLayer::onResolveCCBCCCallFuncSelector(Object * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "onCallback1", TimelineCallbackTestLayer::onCallback1);
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "onCallback2", TimelineCallbackTestLayer::onCallback2);
    return NULL;
}

bool TimelineCallbackTestLayer::onAssignCCBMemberVariable(Object * pTarget, const char * pMemberVariableName, Node * pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "helloLabel", LabelTTF *, this->_helloLabel);
    
    return false;
}

void TimelineCallbackTestLayer::onCallback1(Node* sender)
{
    // Rotate the label when the button is pressed
    this->_helloLabel->runAction(RotateBy::create(1,360));
    this->_helloLabel->setString("Callback 1");
}

void TimelineCallbackTestLayer::onCallback2(Node* sender)
{
    // Rotate the label when the button is pressed
    this->_helloLabel->runAction(RotateBy::create(1,-360));
    this->_helloLabel->setString("Callback 2");
}
