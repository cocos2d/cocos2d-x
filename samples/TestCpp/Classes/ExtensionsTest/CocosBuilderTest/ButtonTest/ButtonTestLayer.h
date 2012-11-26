#ifndef _BUTTONTESTLAYER_H_
#define _BUTTONTESTLAYER_H_

#include "cocos2d.h"
#include "cocos-ext.h"

class ButtonTestLayer 
    : public cocos2d::CCLayer
    , public cocos2d::extension::CCBMemberVariableAssigner
    , public cocos2d::extension::CCBSelectorResolver
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ButtonTestLayer, create);

    ButtonTestLayer();
    virtual ~ButtonTestLayer();

    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);

    void onCCControlButtonClicked(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);

private:
    cocos2d::CCLabelBMFont * mCCControlEventLabel;
};

#endif