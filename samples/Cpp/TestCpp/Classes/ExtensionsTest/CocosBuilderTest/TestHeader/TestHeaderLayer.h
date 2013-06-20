#ifndef _TESTHEADERLAYER_H_
#define _TESTHEADERLAYER_H_

#include "cocos2d.h"
#include "cocos-ext.h"

class TestHeaderLayer
    : public cocos2d::Layer
    , public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::NodeLoaderListener
{
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(TestHeaderLayer, create);

        virtual cocos2d::SEL_MenuHandler onResolveCCBMenuItemSelector(cocos2d::Object * pTarget, const char * pSelectorName);
        virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBControlSelector(cocos2d::Object * pTarget, const char * pSelectorName);
        virtual void onNodeLoaded(cocos2d::Node * pNode, cocos2d::extension::NodeLoader * pNodeLoader);
    
        void onBackClicked(cocos2d::Object * pSender);
};

#endif