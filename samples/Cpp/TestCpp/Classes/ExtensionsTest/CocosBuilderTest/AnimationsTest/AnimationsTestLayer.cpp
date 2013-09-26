#include "AnimationsTestLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

const int kTagSpeedLabel = 1;

AnimationsTestLayer::AnimationsTestLayer()
: mAnimationManager(NULL)
{}

AnimationsTestLayer::~AnimationsTestLayer()
{
    CC_SAFE_RELEASE_NULL(mAnimationManager);
}

bool AnimationsTestLayer::init() {
    Layer::init();
    
    //todo: move to ccbi
    LabelTTF *speedLabel = LabelTTF::create("speed: 1.00", "", 20);
    if( speedLabel ) {
        speedLabel->setAnchorPoint(Point(0.0f,0.5f));
        speedLabel->setPosition(Point(10, getContentSize().height/2));
        addChild(speedLabel, 1, kTagSpeedLabel);
    }
    LabelTTF *hintLabel = LabelTTF::create("press a button again to change speed", "", 14);
    if( hintLabel ) {
        hintLabel->setAnchorPoint(Point(0.0f, 0.5f));
        hintLabel->setPosition(Point(10, getContentSize().height/2 - 20));
        addChild(hintLabel, 1);
    }

    //todo: add a "change speed" button to ccbi

    return true;
}

SEL_MenuHandler AnimationsTestLayer::onResolveCCBCCMenuItemSelector(Object * pTarget, const char * pSelectorName)
{
    return NULL;
}

Control::Handler AnimationsTestLayer::onResolveCCBCCControlSelector(Object *pTarget, const char*pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCCControlButtonIdleClicked", AnimationsTestLayer::onControlButtonIdleClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCCControlButtonWaveClicked", AnimationsTestLayer::onControlButtonWaveClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCCControlButtonJumpClicked", AnimationsTestLayer::onControlButtonJumpClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCCControlButtonFunkyClicked", AnimationsTestLayer::onControlButtonFunkyClicked);

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

void AnimationsTestLayer::changeSpeed(int buttonId) {
    // only change speed if a button was pressed repeatly
    static int lastButtonId = -1;    
    if( lastButtonId != buttonId ) {
        lastButtonId = buttonId;
        return;
    }
    lastButtonId = buttonId;

    float speed = mAnimationManager->getSpeed();
    if( (speed *= 2.0f) >= 4.1f ) {
        speed = 0.25f;
    }
    mAnimationManager->setSpeed(speed);

    LabelTTF *speedLabel = dynamic_cast<LabelTTF *>(getChildByTag(kTagSpeedLabel));
    if( speedLabel ) {        
        speedLabel->setString(  String::createWithFormat("speed: %.2f", speed)->getCString() );
    }
}

void AnimationsTestLayer::onControlButtonIdleClicked(Object *pSender, Control::EventType pControlEvent) {    
    changeSpeed(0);
    mAnimationManager->runAnimationsForSequenceNamedTweenDuration("Idle", 0.3f);
}

void AnimationsTestLayer::onControlButtonWaveClicked(Object *pSender, Control::EventType pControlEvent) {
    changeSpeed(1);
    mAnimationManager->runAnimationsForSequenceNamedTweenDuration("Wave", 0.3f);
}

void AnimationsTestLayer::onControlButtonJumpClicked(Object *pSender, Control::EventType pControlEvent) {
    changeSpeed(2);
    mAnimationManager->runAnimationsForSequenceNamedTweenDuration("Jump", 0.3f);
}

void AnimationsTestLayer::onControlButtonFunkyClicked(Object *pSender, Control::EventType pControlEvent) {
    changeSpeed(3);
    mAnimationManager->runAnimationsForSequenceNamedTweenDuration("Funky", 0.3f);
}