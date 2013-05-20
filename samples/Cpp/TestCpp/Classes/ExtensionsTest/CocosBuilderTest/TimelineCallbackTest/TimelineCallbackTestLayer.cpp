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

SEL_MenuHandler TimelineCallbackTestLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) {
    return NULL;
}

SEL_CCControlHandler TimelineCallbackTestLayer::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
    return NULL;
}

CCCallFunc* TimelineCallbackTestLayer::onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName)
{
    if(pTarget == this && strcmp(pSelectorName, "onCallback1") == 0)
    { 
        return CCCallFuncN::create(pTarget, (SEL_CallFuncN)&TimelineCallbackTestLayer::onCallback1);
    }
    if(pTarget == this && strcmp(pSelectorName, "onCallback2") == 0)
    { 
        return CCCallFuncN::create(pTarget, (SEL_CallFuncN)&TimelineCallbackTestLayer::onCallback2);
    }
    return NULL;
}

bool TimelineCallbackTestLayer::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "helloLabel", CCLabelTTF *, this->_helloLabel);
    
    return false;
}

void TimelineCallbackTestLayer::onCallback1(CCNode* sender)
{
    // Rotate the label when the button is pressed
    this->_helloLabel->runAction(CCRotateBy::create(1,360));
    this->_helloLabel->setString("Callback 1");
}

void TimelineCallbackTestLayer::onCallback2(CCNode* sender)
{
    // Rotate the label when the button is pressed
    this->_helloLabel->runAction(CCRotateBy::create(1,-360));
    this->_helloLabel->setString("Callback 2");
}
