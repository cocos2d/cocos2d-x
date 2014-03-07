

#ifndef __TestCpp__GUIEditorTest__
#define __TestCpp__GUIEditorTest__

#include "../../testBasic.h"

class GUIEditorMainLayer : public CCLayer
{
public:
    virtual void onEnter();
    void menuCallback(CCObject* pSender);
    virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* pEvent);
    virtual void ccTouchesMoved(CCSet* pTouches, CCEvent* pEvent);
private:
    CCPoint _beginPos;
    CCMenu* _itemMenu;
};

class GUIEditorTestScene : public TestScene
{
public:
    virtual void onEnter();
    virtual void runThisTest();
    void BackCallback(CCObject* pSender);
};

#endif /* defined(__TestCpp__GUIEditorTest__) */
