#ifndef _TESTHEADERLAYER_H_
#define _TESTHEADERLAYER_H_

#include "cocos2d.h"
#include "cocos-ext.h"

class TestHeaderLayer
    : public cc::Layer
    , public cc::extension::CCBSelectorResolver
, public cc::extension::NodeLoaderListener
{
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(TestHeaderLayer, create);

        virtual cc::SEL_MenuHandler onResolveCCBMenuItemSelector(cc::Object * pTarget, const char * pSelectorName);
        virtual cc::extension::SEL_CCControlHandler onResolveCCBControlSelector(cc::Object * pTarget, const char * pSelectorName);
        virtual void onNodeLoaded(cc::Node * node, cc::extension::NodeLoader * nodeLoader);
    
        void onBackClicked(cc::Object * pSender);
};

#endif