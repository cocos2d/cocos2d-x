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

SEL_MenuHandler AnimationsTestLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler AnimationsTestLayer::onResolveCCBCCControlSelector(CCObject *pTarget, const char*pSelectorName) {
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCCControlButtonIdleClicked", AnimationsTestLayer::onCCControlButtonIdleClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCCControlButtonWaveClicked", AnimationsTestLayer::onCCControlButtonWaveClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCCControlButtonJumpClicked", AnimationsTestLayer::onCCControlButtonJumpClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCCControlButtonFunkyClicked", AnimationsTestLayer::onCCControlButtonFunkyClicked);

    return NULL;
}

bool AnimationsTestLayer::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
     CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);
    
    return false;
}

void AnimationsTestLayer::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
    CC_SAFE_RELEASE_NULL(mAnimationManager);
    mAnimationManager = pAnimationManager;
    CC_SAFE_RETAIN(mAnimationManager);
}

void AnimationsTestLayer::onCCControlButtonIdleClicked(CCObject *pSender, CCControlEvent pCCControlEvent) {
    mAnimationManager->runAnimationsForSequenceNamedTweenDuration("Idle", 0.3f);
}

void AnimationsTestLayer::onCCControlButtonWaveClicked(CCObject *pSender, CCControlEvent pCCControlEvent) {
    mAnimationManager->runAnimationsForSequenceNamedTweenDuration("Wave", 0.3f);
}

void AnimationsTestLayer::onCCControlButtonJumpClicked(CCObject *pSender, CCControlEvent pCCControlEvent) {
    mAnimationManager->runAnimationsForSequenceNamedTweenDuration("Jump", 0.3f);
}

void AnimationsTestLayer::onCCControlButtonFunkyClicked(CCObject *pSender, CCControlEvent pCCControlEvent) {
    mAnimationManager->runAnimationsForSequenceNamedTweenDuration("Funky", 0.3f);
}