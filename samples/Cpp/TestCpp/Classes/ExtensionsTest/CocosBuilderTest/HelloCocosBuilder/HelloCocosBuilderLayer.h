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
: public cocos2d::Layer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::NodeLoaderListener
{
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(HelloCocosBuilderLayer, create);

        HelloCocosBuilderLayer();
        virtual ~HelloCocosBuilderLayer();

        void openTest(const char * pCCBFileName, const char * nodeName = NULL, cocos2d::extension::NodeLoader * nodeLoader = NULL);

        virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Object * pTarget, const char * pSelectorName);
        virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Object * pTarget, const char * pSelectorName);
        virtual bool onAssignCCBMemberVariable(cocos2d::Object * pTarget, const char * pMemberVariableName, cocos2d::Node * node);
        virtual bool onAssignCCBCustomProperty(Object* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
        virtual void onNodeLoaded(cocos2d::Node * node, cocos2d::extension::NodeLoader * nodeLoader);

        void onMenuTestClicked(cocos2d::Object * sender, cocos2d::extension::Control::EventType pControlEvent);
        void onSpriteTestClicked(cocos2d::Object * sender, cocos2d::extension::Control::EventType pControlEvent);
        void onButtonTestClicked(cocos2d::Object * sender, cocos2d::extension::Control::EventType pControlEvent);
        void onAnimationsTestClicked(cocos2d::Object * sender, cocos2d::extension::Control::EventType pControlEvent);
        void onParticleSystemTestClicked(cocos2d::Object * sender, cocos2d::extension::Control::EventType pControlEvent);
        void onScrollViewTestClicked(cocos2d::Object * sender, cocos2d::extension::Control::EventType pControlEvent);
        void onTimelineCallbackSoundClicked(cocos2d::Object * sender, cocos2d::extension::Control::EventType pControlEvent);

    private:
        cocos2d::Sprite * mBurstSprite;
        cocos2d::LabelTTF * mTestTitleLabelTTF;
    
        int mCustomPropertyInt;
        float mCustomPropertyFloat;
        bool mCustomPropertyBoolean;
        std::string mCustomPropertyString;
};

#endif
