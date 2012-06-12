#ifndef _CCBIREADER_LAYER_H_
#define _CCBIREADER_LAYER_H_

#include "cocos2d.h"
#include "CCBMemberVariableAssigner.h"
#include "CCBSelectorResolver.h"

class CCBIReaderLayer : public cocos2d::CCLayer, public cocos2d::extension::CCBMemberVariableAssigner, public cocos2d::extension::CCBSelectorResolver {
    public:
        static CCBIReaderLayer * node();

        virtual bool init();  

        virtual void menuCloseCallback(CCObject * pSender);

        virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
        virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuSelector(CCObject * pTarget, const char * pSelectorName);
        virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);

        virtual void onCCControlButtonClicked(CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
        virtual void onCCMenuItemImageClicked(CCObject * pSender);
    private:
        cocos2d::extension::CCControlButton * mCCControlButton;
        cocos2d::CCMenuItemImage * mCCMenuItemImage;
};

#endif
