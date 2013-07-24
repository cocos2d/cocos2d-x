#ifndef _ANIMATIONSTESTLAYER_H_
#define _ANIMATIONSTESTLAYER_H_

#include "cocos2d.h"
#include "cocos-ext.h"

class AnimationsTestLayer
: public cc::Layer
, public cc::extension::CCBSelectorResolver
, public cc::extension::CCBMemberVariableAssigner 
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AnimationsTestLayer, create);
    
    AnimationsTestLayer();
    virtual ~AnimationsTestLayer();
    
    virtual cc::SEL_MenuHandler onResolveCCBMenuItemSelector(Object * pTarget, const char * pSelectorName);
    virtual cc::extension::SEL_CCControlHandler onResolveCCBControlSelector(cc::Object * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cc::Object * pTarget, const char * pMemberVariableName, cc::Node * node);
    
    void onControlButtonIdleClicked(cc::Object * pSender, cc::extension::ControlEvent pControlEvent);
    void onControlButtonWaveClicked(cc::Object * pSender, cc::extension::ControlEvent pControlEvent);
    void onControlButtonJumpClicked(cc::Object * pSender, cc::extension::ControlEvent pControlEvent);
    void onControlButtonFunkyClicked(cc::Object * pSender, cc::extension::ControlEvent pControlEvent);
    
    void setAnimationManager(cc::extension::CCBAnimationManager *pAnimationManager);
    
private:
    cc::extension::CCBAnimationManager *mAnimationManager;
};

#endif