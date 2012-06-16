#ifndef _MENUTESTLAYER_H_
#define _MENUTESTLAYER_H_

#include "cocos2d.h"
#include "extensions/CCBReader/CCNodeLoader.h"
#include "extensions/CCBReader/CCBSelectorResolver.h"
#include "extensions/CCBReader/CCBMemberVariableAssigner.h"

class MenuTestLayer : public cocos2d::extension::CCBSelectorResolver, public cocos2d::extension::CCBMemberVariableAssigner, public cocos2d::CCLayer {
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MenuTestLayer, node);

        virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
        virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
        virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);

        virtual void onMenuItemAClicked(cocos2d::CCObject * pSender);
        virtual void onMenuItemBClicked(cocos2d::CCObject * pSender);
        virtual void onMenuItemCClicked(cocos2d::CCObject * pSender);

    private:
        cocos2d::CCLabelBMFont * mMenuItemStatusLabelBMFont;
};

#endif