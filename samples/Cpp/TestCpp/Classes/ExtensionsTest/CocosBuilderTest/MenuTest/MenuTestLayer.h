#ifndef _MENUTESTLAYER_H_
#define _MENUTESTLAYER_H_

#include "cocos2d.h"
#include "cocos-ext.h"

class MenuTestLayer
    : public cc::Layer
    , public cc::extension::CCBSelectorResolver
    , public cc::extension::CCBMemberVariableAssigner 
{
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MenuTestLayer, create);

        MenuTestLayer();
        virtual ~MenuTestLayer();

        virtual cc::SEL_MenuHandler onResolveCCBMenuItemSelector(cc::Object * pTarget, const char * pSelectorName);
        virtual cc::extension::SEL_CCControlHandler onResolveCCBControlSelector(cc::Object * pTarget, const char * pSelectorName);
        virtual bool onAssignCCBMemberVariable(cc::Object * pTarget, const char * pMemberVariableName, cc::Node * node);

        void onMenuItemAClicked(cc::Object * pSender);
        void onMenuItemBClicked(cc::Object * pSender);
        void onMenuItemCClicked(cc::Object * pSender);

    private:
        cc::LabelBMFont * mMenuItemStatusLabelBMFont;
};

#endif