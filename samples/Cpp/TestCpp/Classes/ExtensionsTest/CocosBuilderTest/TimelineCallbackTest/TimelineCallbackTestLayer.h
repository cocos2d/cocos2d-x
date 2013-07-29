#ifndef _TIMELINE_TESTLAYER_H_
#define _TIMELINE_TESTLAYER_H_

#include "cocos2d.h"
#include "cocos-ext.h"

class TimelineCallbackTestLayer
    : public cocos2d::Layer
    , public cocos2d::extension::CCBSelectorResolver
    , public cocos2d::extension::CCBMemberVariableAssigner 
{
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(TimelineCallbackTestLayer, create);

        TimelineCallbackTestLayer();
        virtual ~TimelineCallbackTestLayer();

        virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Object * pTarget, const char * pSelectorName);
        virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Object * pTarget, const char * pSelectorName);
        virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector(Object * pTarget, const char* pSelectorName);
        virtual bool onAssignCCBMemberVariable(cocos2d::Object * pTarget, const char * pMemberVariableName, cocos2d::Node * node);
    
        void onCallback1(Node* sender);
        void onCallback2(Node* sender);
private:
    cocos2d::LabelTTF* _helloLabel;
};

#endif /* _TIMELINE_TESTLAYER_H_ */
