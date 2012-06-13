#ifndef _TESTHEADERLAYER_H_
#define _TESTHEADERLAYER_H_

#include "cocos2d.h"
#include "CCNodeLoader.h"
#include "CCBSelectorResolver.h"

class TestHeaderLayer : public cocos2d::extension::CCBSelectorResolver, public cocos2d::CCLayer {
    public:
        static TestHeaderLayer * node();

        virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
        virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);

        virtual void onBackClicked(cocos2d::CCObject * pSender);
};

#endif