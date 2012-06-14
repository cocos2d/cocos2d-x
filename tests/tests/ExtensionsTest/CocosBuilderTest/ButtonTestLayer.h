#ifndef _BUTTONTESTLAYER_H_
#define _BUTTONTESTLAYER_H_

#include "cocos2d.h"
#include "extensions/CCBReader/CCNodeLoader.h"
#include "extensions/CCBReader/CCBSelectorResolver.h"

class ButtonTestLayer : public cocos2d::extension::CCBSelectorResolver, public cocos2d::CCLayer {
    public:
        static ButtonTestLayer * node();

        virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
        virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);

        virtual void onCCControlButtonClicked(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
};

#endif