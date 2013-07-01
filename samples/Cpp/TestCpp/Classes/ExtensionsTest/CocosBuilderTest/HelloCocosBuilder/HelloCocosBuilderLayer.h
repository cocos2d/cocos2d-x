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

        void openTest(const char * pCCBFileName, const char * pNodeName = NULL, cocos2d::extension::NodeLoader * pNodeLoader = NULL);

        virtual cocos2d::SEL_MenuHandler onResolveCCBMenuItemSelector(cocos2d::Object * pTarget, const char * pSelectorName);
        virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBControlSelector(cocos2d::Object * pTarget, const char * pSelectorName);
        virtual bool onAssignCCBMemberVariable(cocos2d::Object * pTarget, const char * pMemberVariableName, cocos2d::Node * pNode);
        virtual bool onAssignCCBCustomProperty(Object* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
        virtual void onNodeLoaded(cocos2d::Node * pNode, cocos2d::extension::NodeLoader * pNodeLoader);

        void onMenuTestClicked(cocos2d::Object * pSender, cocos2d::extension::ControlEvent pControlEvent);
        void onSpriteTestClicked(cocos2d::Object * pSender, cocos2d::extension::ControlEvent pControlEvent);
        void onButtonTestClicked(cocos2d::Object * pSender, cocos2d::extension::ControlEvent pControlEvent);
        void onAnimationsTestClicked(cocos2d::Object * pSender, cocos2d::extension::ControlEvent pControlEvent);
        void onParticleSystemTestClicked(cocos2d::Object * pSender, cocos2d::extension::ControlEvent pControlEvent);
        void onScrollViewTestClicked(cocos2d::Object * pSender, cocos2d::extension::ControlEvent pControlEvent);
        void onTimelineCallbackSoundClicked(cocos2d::Object * pSender, cocos2d::extension::ControlEvent pControlEvent);

    private:
        cocos2d::Sprite * mBurstSprite;
        cocos2d::LabelTTF * mTestTitleLabelTTF;
    
        int mCustomPropertyInt;
        float mCustomPropertyFloat;
        bool mCustomPropertyBoolean;
        std::string mCustomPropertyString;
};

#endif
