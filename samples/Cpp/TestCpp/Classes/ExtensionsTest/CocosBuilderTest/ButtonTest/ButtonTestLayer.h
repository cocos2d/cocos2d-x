#ifndef _BUTTONTESTLAYER_H_
#define _BUTTONTESTLAYER_H_

#include "cocos2d.h"
#include "cocos-ext.h"

class ButtonTestLayer 
    : public cocos2d::Layer
    , public cocos2d::extension::CCBMemberVariableAssigner
    , public cocos2d::extension::CCBSelectorResolver
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ButtonTestLayer, create);

    ButtonTestLayer();
    virtual ~ButtonTestLayer();

    virtual cocos2d::SEL_MenuHandler onResolveCCBMenuItemSelector(cocos2d::Object * pTarget, const char * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBControlSelector(cocos2d::Object * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::Object * pTarget, const char * pMemberVariableName, cocos2d::Node * pNode);

    void onControlButtonClicked(cocos2d::Object * pSender, cocos2d::extension::ControlEvent pControlEvent);

private:
    cocos2d::LabelBMFont * mControlEventLabel;
};

#endif