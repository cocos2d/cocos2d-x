#ifndef _TESTHEADERLAYER_H_
#define _TESTHEADERLAYER_H_

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"

class TestHeaderLayer
    : public cocos2d::Layer
    , public cocosbuilder::CCBSelectorResolver
, public cocosbuilder::NodeLoaderListener
{
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(TestHeaderLayer, create);

        virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Object * pTarget, const char * pSelectorName);
        virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Object * pTarget, const char * pSelectorName);
        virtual void onNodeLoaded(cocos2d::Node * node, cocosbuilder::NodeLoader * nodeLoader);
    
        void onBackClicked(cocos2d::Object * sender);
};

#endif