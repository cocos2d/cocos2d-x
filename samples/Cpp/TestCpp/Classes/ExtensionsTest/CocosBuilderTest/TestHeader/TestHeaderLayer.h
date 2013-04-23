#ifndef _TESTHEADERLAYER_H_
#define _TESTHEADERLAYER_H_

#include "cocos2d.h"
#include "cocos-ext.h"

class TestHeaderLayer
    : public cocos2d::CCLayer
    , public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCNodeLoaderListener
{
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(TestHeaderLayer, create);

        virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
        virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
        virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
        void onBackClicked(cocos2d::CCObject * pSender);
};

#endif