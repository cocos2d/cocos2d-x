#ifndef _MENUTESTLAYER_H_
#define _MENUTESTLAYER_H_

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"

class MenuTestLayer
    : public cocos2d::Layer
    , public cocosbuilder::CCBSelectorResolver
    , public cocosbuilder::CCBMemberVariableAssigner 
{
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MenuTestLayer, create);

        MenuTestLayer();
        virtual ~MenuTestLayer();

        virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char * pSelectorName);
        virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char * pSelectorName);
        virtual bool onAssignCCBMemberVariable(cocos2d::Ref * pTarget, const char * pMemberVariableName, cocos2d::Node * node);

        void onMenuItemAClicked(cocos2d::Ref * sender);
        void onMenuItemBClicked(cocos2d::Ref * sender);
        void onMenuItemCClicked(cocos2d::Ref * sender);

    private:
        cocos2d::Label * mMenuItemStatusLabelBMFont;
};

#endif
