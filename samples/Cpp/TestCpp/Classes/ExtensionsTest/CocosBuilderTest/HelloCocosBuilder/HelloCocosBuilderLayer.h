#ifndef _HELLOCOCOSBUILDERLAYER_H_
#define _HELLOCOCOSBUILDERLAYER_H_

#include "cocos2d.h"
#include "cocos-ext.h"

/*
 * Note: for some pretty hard fucked up reason, the order of inheritance is important!
 * When Layer is the 'first' inherited object:
 * During runtime the method call to the (pure virtual) 'interfaces' fails jumping into a bogus method or just doing nothing: 
 *  #0    0x000cf840 in non-virtual thunk to HelloCocos....
 *  #1    ....
 *
 * This thread describes the problem:
 * http://www.cocoabuilder.com/archive/xcode/265549-crash-in-virtual-method-call.html
 */
class HelloCocosBuilderLayer
: public cc::Layer
, public cc::extension::CCBSelectorResolver
, public cc::extension::CCBMemberVariableAssigner
, public cc::extension::NodeLoaderListener
{
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(HelloCocosBuilderLayer, create);

        HelloCocosBuilderLayer();
        virtual ~HelloCocosBuilderLayer();

        void openTest(const char * pCCBFileName, const char * nodeName = NULL, cc::extension::NodeLoader * nodeLoader = NULL);

        virtual cc::SEL_MenuHandler onResolveCCBMenuItemSelector(cc::Object * pTarget, const char * pSelectorName);
        virtual cc::extension::SEL_CCControlHandler onResolveCCBControlSelector(cc::Object * pTarget, const char * pSelectorName);
        virtual bool onAssignCCBMemberVariable(cc::Object * pTarget, const char * pMemberVariableName, cc::Node * node);
        virtual bool onAssignCCBCustomProperty(Object* pTarget, const char* pMemberVariableName, cc::extension::CCBValue* pCCBValue);
        virtual void onNodeLoaded(cc::Node * node, cc::extension::NodeLoader * nodeLoader);

        void onMenuTestClicked(cc::Object * pSender, cc::extension::ControlEvent pControlEvent);
        void onSpriteTestClicked(cc::Object * pSender, cc::extension::ControlEvent pControlEvent);
        void onButtonTestClicked(cc::Object * pSender, cc::extension::ControlEvent pControlEvent);
        void onAnimationsTestClicked(cc::Object * pSender, cc::extension::ControlEvent pControlEvent);
        void onParticleSystemTestClicked(cc::Object * pSender, cc::extension::ControlEvent pControlEvent);
        void onScrollViewTestClicked(cc::Object * pSender, cc::extension::ControlEvent pControlEvent);
        void onTimelineCallbackSoundClicked(cc::Object * pSender, cc::extension::ControlEvent pControlEvent);

    private:
        cc::Sprite * mBurstSprite;
        cc::LabelTTF * mTestTitleLabelTTF;
    
        int mCustomPropertyInt;
        float mCustomPropertyFloat;
        bool mCustomPropertyBoolean;
        std::string mCustomPropertyString;
};

#endif
