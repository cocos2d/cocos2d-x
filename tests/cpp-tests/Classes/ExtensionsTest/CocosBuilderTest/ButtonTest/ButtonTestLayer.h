#ifndef _BUTTONTESTLAYER_H_
#define _BUTTONTESTLAYER_H_

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "editor-support/cocosbuilder/CocosBuilder.h"

class ButtonTestLayer 
    : public cocos2d::Layer
    , public cocosbuilder::CCBMemberVariableAssigner
    , public cocosbuilder::CCBSelectorResolver
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ButtonTestLayer, create);

    ButtonTestLayer();
    virtual ~ButtonTestLayer();

    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char * pSelectorName);
    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::Ref * pTarget, const char * pMemberVariableName, cocos2d::Node * node);

    void onControlButtonClicked(cocos2d::Ref * sender, cocos2d::extension::Control::EventType pControlEvent);

private:
    cocos2d::Label * mControlEventLabel;
};

#endif
