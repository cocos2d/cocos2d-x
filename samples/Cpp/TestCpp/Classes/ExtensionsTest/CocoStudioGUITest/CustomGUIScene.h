

#ifndef __TestCpp__CutomGUIScene__
#define __TestCpp__CutomGUIScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "../../testBasic.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CustomGUITestMainLayer : public CCLayer
{
public:
    virtual void onEnter();
    void menuCallback(CCObject* pSender);
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    
    void touchEvent(CCObject* pSender, cocos2d::ui::TouchEventType type);
private:
    CCPoint _beginPos;
    CCMenu* _itemMenu;
};

class CustomGUITestScene : public TestScene
{
public:
    virtual void onEnter();
    virtual void runThisTest();
    void BackCallback(CCObject* pSender);
};

#endif /* defined(__TestCpp__CutomGUIScene__) */
