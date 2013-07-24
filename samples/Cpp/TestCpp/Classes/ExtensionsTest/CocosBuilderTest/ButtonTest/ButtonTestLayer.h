#ifndef _BUTTONTESTLAYER_H_
#define _BUTTONTESTLAYER_H_

#include "cocos2d.h"
#include "cocos-ext.h"

class ButtonTestLayer 
    : public cc::Layer
    , public cc::extension::CCBMemberVariableAssigner
    , public cc::extension::CCBSelectorResolver
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ButtonTestLayer, create);

    ButtonTestLayer();
    virtual ~ButtonTestLayer();

    virtual cc::SEL_MenuHandler onResolveCCBMenuItemSelector(cc::Object * pTarget, const char * pSelectorName);
    virtual cc::extension::SEL_CCControlHandler onResolveCCBControlSelector(cc::Object * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cc::Object * pTarget, const char * pMemberVariableName, cc::Node * node);

    void onControlButtonClicked(cc::Object * pSender, cc::extension::ControlEvent pControlEvent);

private:
    cc::LabelBMFont * mControlEventLabel;
};

#endif