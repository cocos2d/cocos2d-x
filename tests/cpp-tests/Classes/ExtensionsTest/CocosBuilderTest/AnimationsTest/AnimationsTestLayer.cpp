#include "AnimationsTestLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

AnimationsTestLayer::AnimationsTestLayer()
: mAnimationManager(nullptr)
{}

AnimationsTestLayer::~AnimationsTestLayer()
{
    CC_SAFE_RELEASE_NULL(mAnimationManager);
}

SEL_MenuHandler AnimationsTestLayer::onResolveCCBCCMenuItemSelector(Ref * pTarget, const char * pSelectorName)
{
    return NULL;
}

Control::Handler AnimationsTestLayer::onResolveCCBCCControlSelector(Ref *pTarget, const char*pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCCControlButtonIdleClicked", AnimationsTestLayer::onControlButtonIdleClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCCControlButtonWaveClicked", AnimationsTestLayer::onControlButtonWaveClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCCControlButtonJumpClicked", AnimationsTestLayer::onControlButtonJumpClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCCControlButtonFunkyClicked", AnimationsTestLayer::onControlButtonFunkyClicked);

    return NULL;
}

bool AnimationsTestLayer::onAssignCCBMemberVariable(Ref * pTarget, const char * pMemberVariableName, Node * pNode) {
     CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);
    
    return false;
}

void AnimationsTestLayer::setAnimationManager(cocosbuilder::CCBAnimationManager *pAnimationManager)
{
    CC_SAFE_RELEASE_NULL(mAnimationManager);
    mAnimationManager = pAnimationManager;
    CC_SAFE_RETAIN(mAnimationManager);
}

void AnimationsTestLayer::onControlButtonIdleClicked(Ref *pSender, Control::EventType pControlEvent) {
    mAnimationManager->runAnimationsForSequenceNamedTweenDuration("Idle", 0.3f);
}

void AnimationsTestLayer::onControlButtonWaveClicked(Ref *pSender, Control::EventType pControlEvent) {
    mAnimationManager->runAnimationsForSequenceNamedTweenDuration("Wave", 0.3f);
}

void AnimationsTestLayer::onControlButtonJumpClicked(Ref *pSender, Control::EventType pControlEvent) {
    mAnimationManager->runAnimationsForSequenceNamedTweenDuration("Jump", 0.3f);
}

void AnimationsTestLayer::onControlButtonFunkyClicked(Ref *pSender, Control::EventType pControlEvent) {
    mAnimationManager->runAnimationsForSequenceNamedTweenDuration("Funky", 0.3f);
}
