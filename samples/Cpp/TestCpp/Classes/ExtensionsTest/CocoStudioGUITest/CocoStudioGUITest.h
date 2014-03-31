

#ifndef __TestCpp__CocoStudioGUITest__
#define __TestCpp__CocoStudioGUITest__

#include "../../testBasic.h"

class CocoStudioGUIMainLayer : public CCLayer
{
public:
    virtual void onEnter();
    void menuCallback(CCObject* pSender);
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    
private:
    CCPoint _beginPos;
    CCMenu* _itemMenu;
};

class CocoStudioGUITestScene : public TestScene
{
public:
    virtual void onEnter();
    virtual void runThisTest();
    void BackCallback(CCObject* pSender);
};

#endif /* defined(__TestCpp__CocoStudioGUITest__) */
