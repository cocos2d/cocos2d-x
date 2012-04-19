#ifndef __BUGS_TEST_H__
#define __BUGS_TEST_H__

#include "../testBasic.h"

class BugsTestMainLayer : public CCLayer
{
public:
    virtual void onEnter();
    void menuCallback(CCObject* pSender);

    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);

protected:
    CCPoint m_tBeginPos;
    CCMenu* m_pItmeMenu;
};

class BugsTestBaseLayer : public CCLayer
{
public:
    virtual void onEnter();
    void backCallback(CCObject* pSender);
};

class BugsTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
