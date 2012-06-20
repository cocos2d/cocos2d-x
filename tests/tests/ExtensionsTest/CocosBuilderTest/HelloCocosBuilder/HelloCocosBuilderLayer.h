#ifndef _HELLOCOCOSBUILDERLAYER_H_
#define _HELLOCOCOSBUILDERLAYER_H_

#include "cocos2d.h"
#include "extensions/CCBReader/CCNodeLoader.h"
#include "extensions/CCBReader/CCNodeLoaderListener.h"
#include "extensions/CCBReader/CCBSelectorResolver.h"
#include "extensions/CCBReader/CCBMemberVariableAssigner.h"

/*
 * Note: for some pretty hard fucked up reason, the order of inheritance is important!
 * When CCLayer is the 'first' inherited object:
 * During runtime the method call to the (pure virtual) 'interfaces' fails jumping into a bogus method or just doing nothing: 
 *  #0    0x000cf840 in non-virtual thunk to HelloCocos....
 *  #1    ....
 *
 * This thread describes the problem:
 * http://www.cocoabuilder.com/archive/xcode/265549-crash-in-virtual-method-call.html
 */
class HelloCocosBuilderLayer
    : public cocos2d::CCLayer
    , public cocos2d::extension::CCBSelectorResolver
    , public cocos2d::extension::CCBMemberVariableAssigner
    , public cocos2d::extension::CCNodeLoaderListener
{
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(HelloCocosBuilderLayer, create);

        HelloCocosBuilderLayer();
        virtual ~HelloCocosBuilderLayer();

        void openTest(const char * pCCBFileName, const char * pCCNodeName = NULL, cocos2d::extension::CCNodeLoader * pCCNodeLoader = NULL);

        virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
        virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
        virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
        virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

        void onMenuTestClicked(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
        void onSpriteTestClicked(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
        void onButtonTestClicked(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
        void onLabelTestClicked(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
        void onParticleSystemTestClicked(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
        void onScrollViewTestClicked(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);

    private:
        cocos2d::CCSprite * mBurstSprite;
        cocos2d::CCLabelTTF * mTestTitleLabelTTF;
};

#endif
