#ifndef _ActionsTest_H_
#define _ActionsTest_H_

#include "../testBasic.h"
#include "CCDirector.h"
#include "CCScene.h"
#include "CCLayer.h"
#include "CCSprite.h"
#include "platform/platform.h"

using namespace cocos2d;

CCLayer* CreateLayer(Int32 nIndex);
CCLayer* NextAction();
CCLayer* BackAction();
CCLayer* RestartAction();

enum
{
    ACTION_DEMO_LAYER = 0,
    ACTION_ROTATE_LAYER,
    ACTION_LAYER_COUNT,
};

class ActionsDemo : public CCLayer
{
protected:
    CCSprite*	m_grossini;
    CCSprite*	m_tamara;
    CCSprite*	m_kathia;public:
    virtual void onEnter();

    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch *pTouch, UIEvent *pEvent);

    void centerSprites(unsigned int numberOfSprites);
//     virtual UxString title();
//     virtual UxString subtitle();
//     void alignSpritesLeft(unsigned int numberOfSprites);

//     void restartCallback(UxObject* pSender);
//     void nextCallback(UxObject* pSender);
//     void backCallback(UxObject* pSender);
};

class ActionRotate : public ActionsDemo
{
public:
    virtual void onEnter();
};

class ActionsTestScene : public TestScene
{
public:
    virtual void runThisTest()
    {
        addChild(NextAction());

        CCDirector::getSharedDirector()->replaceScene(this);
    }
};

#endif
