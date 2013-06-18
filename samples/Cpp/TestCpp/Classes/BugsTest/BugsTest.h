#ifndef __BUGS_TEST_H__
#define __BUGS_TEST_H__

#include "../testBasic.h"

class BugsTestMainLayer : public CCLayer
{
public:
    virtual void onEnter();

    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);

protected:
    CCPoint _beginPos;
    CCMenu* _itmeMenu;
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
