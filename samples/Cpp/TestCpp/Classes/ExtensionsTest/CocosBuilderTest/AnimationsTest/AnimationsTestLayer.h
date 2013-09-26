#ifndef _ANIMATIONSTESTLAYER_H_
#define _ANIMATIONSTESTLAYER_H_

#include "cocos2d.h"
#include "cocos-ext.h"

class AnimationsTestLayer
: public cocos2d::Layer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner 
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AnimationsTestLayer, create);
    
    AnimationsTestLayer();
    virtual ~AnimationsTestLayer();
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(Object * pTarget, const char * pSelectorName);
    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Object * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::Object * pTarget, const char * pMemberVariableName, cocos2d::Node * node);
    
    void onControlButtonIdleClicked(cocos2d::Object * sender, cocos2d::extension::Control::EventType pControlEvent);
    void onControlButtonWaveClicked(cocos2d::Object * sender, cocos2d::extension::Control::EventType pControlEvent);
    void onControlButtonJumpClicked(cocos2d::Object * sender, cocos2d::extension::Control::EventType pControlEvent);
    void onControlButtonFunkyClicked(cocos2d::Object * sender, cocos2d::extension::Control::EventType pControlEvent);
    
    void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);
    
    void changeSpeed(int buttonId);

    bool init() override;
private:
    cocos2d::extension::CCBAnimationManager *mAnimationManager;
};

#endif