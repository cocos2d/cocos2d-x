#ifndef __EXTENSIONS_TEST_H__
#define __EXTENSIONS_TEST_H__

#include "../testBasic.h"

class ExtensionsMainLayer : public CCLayer
{
public:
    virtual void onEnter();
    void menuCallback(CCObject* pSender);
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
private:
    CCPoint m_tBeginPos;
    CCMenu* m_pItemMenu;
};

class ExtensionsTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif /* __EXTENSIONS_TEST_H__ */
