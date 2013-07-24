#ifndef _TIMELINE_TESTLAYER_H_
#define _TIMELINE_TESTLAYER_H_

#include "cocos2d.h"
#include "cocos-ext.h"

class TimelineCallbackTestLayer
    : public cc::Layer
    , public cc::extension::CCBSelectorResolver
    , public cc::extension::CCBMemberVariableAssigner 
{
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(TimelineCallbackTestLayer, create);

        TimelineCallbackTestLayer();
        virtual ~TimelineCallbackTestLayer();

        virtual cc::SEL_MenuHandler onResolveCCBMenuItemSelector(cc::Object * pTarget, const char * pSelectorName);
        virtual cc::extension::SEL_CCControlHandler onResolveCCBControlSelector(cc::Object * pTarget, const char * pSelectorName);
        virtual cc::SEL_CallFuncN onResolveCCBCallFuncSelector(Object * pTarget, const char* pSelectorName);
        virtual bool onAssignCCBMemberVariable(cc::Object * pTarget, const char * pMemberVariableName, cc::Node * node);
    
        void onCallback1(Node* sender);
        void onCallback2(Node* sender);
private:
    cc::LabelTTF* _helloLabel;
};

#endif /* _TIMELINE_TESTLAYER_H_ */
