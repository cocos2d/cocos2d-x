#ifndef _ANIMATIONSTESTLAYER_H_
#define _ANIMATIONSTESTLAYER_H_

#include "cocos2d.h"
#include "cocos-ext.h"

class AnimationsTestLayer
: public cocos2d::CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner 
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AnimationsTestLayer, create);
    
    AnimationsTestLayer();
    virtual ~AnimationsTestLayer();
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    
    void onCCControlButtonIdleClicked(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    void onCCControlButtonWaveClicked(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    void onCCControlButtonJumpClicked(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    void onCCControlButtonFunkyClicked(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    
    void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);
    
private:
    cocos2d::extension::CCBAnimationManager *mAnimationManager;
};

#endif