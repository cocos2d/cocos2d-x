#ifndef _TIMELINE_TESTLAYER_H_
#define _TIMELINE_TESTLAYER_H_

#include "cocos2d.h"
#include "audio/include/SimpleAudioEngine.h"
#include "extensions/cocos-ext.h"
#include "editor-support/cocosbuilder/CocosBuilder.h"

class TimelineCallbackTestLayer
    : public cocos2d::Layer
    , public cocosbuilder::CCBSelectorResolver
    , public cocosbuilder::CCBMemberVariableAssigner 
{
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(TimelineCallbackTestLayer, create);

        TimelineCallbackTestLayer();
        virtual ~TimelineCallbackTestLayer();

        virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char * pSelectorName);
        virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char * pSelectorName);
        virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector(cocos2d::Ref*  pTarget, const char* pSelectorName);
        virtual bool onAssignCCBMemberVariable(cocos2d::Ref * pTarget, const char * pMemberVariableName, cocos2d::Node * node);
    
        void onCallback1(Node* sender);
        void onCallback2(Node* sender);
private:
    cocos2d::Label* _helloLabel;
};

#endif /* _TIMELINE_TESTLAYER_H_ */
