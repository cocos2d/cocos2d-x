#include "AnimationsTestLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

AnimationsTestLayer::AnimationsTestLayer()
: mAnimationManager(NULL)
{}

AnimationsTestLayer::~AnimationsTestLayer()
{
    CC_SAFE_RELEASE_NULL(mAnimationManager);
}

SEL_MenuHandler AnimationsTestLayer::onResolveCCBMenuItemSelector(Object * pTarget, const char * pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler AnimationsTestLayer::onResolveCCBControlSelector(Object *pTarget, const char*pSelectorName) {
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onControlButtonIdleClicked", AnimationsTestLayer::onControlButtonIdleClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onControlButtonWaveClicked", AnimationsTestLayer::onControlButtonWaveClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onControlButtonJumpClicked", AnimationsTestLayer::onControlButtonJumpClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onControlButtonFunkyClicked", AnimationsTestLayer::onControlButtonFunkyClicked);

    return NULL;
}

bool AnimationsTestLayer::onAssignCCBMemberVariable(Object * pTarget, const char * pMemberVariableName, Node * pNode) {
     CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);
    
    return false;
}

void AnimationsTestLayer::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
    CC_SAFE_RELEASE_NULL(mAnimationManager);
    mAnimationManager = pAnimationManager;
    CC_SAFE_RETAIN(mAnimationManager);
}

void AnimationsTestLayer::onControlButtonIdleClicked(Object *pSender, ControlEvent pControlEvent) {
    mAnimationManager->runAnimationsForSequenceNamedTweenDuration("Idle", 0.3f);
}

void AnimationsTestLayer::onControlButtonWaveClicked(Object *pSender, ControlEvent pControlEvent) {
    mAnimationManager->runAnimationsForSequenceNamedTweenDuration("Wave", 0.3f);
}

void AnimationsTestLayer::onControlButtonJumpClicked(Object *pSender, ControlEvent pControlEvent) {
    mAnimationManager->runAnimationsForSequenceNamedTweenDuration("Jump", 0.3f);
}

void AnimationsTestLayer::onControlButtonFunkyClicked(Object *pSender, ControlEvent pControlEvent) {
    mAnimationManager->runAnimationsForSequenceNamedTweenDuration("Funky", 0.3f);
}