#ifndef __COCOS_DENSHION_TEST__
#define __COCOS_DENSHION_TEST__

#include "../testBasic.h"

class CocosDenshionTest : public CCLayer
{
public:
    CocosDenshionTest(void);
    ~CocosDenshionTest(void);

    void menuCallback(CCObject * pSender);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void onExit();

private:
    CCMenu* m_pItmeMenu;
    CCPoint m_tBeginPos;
    int m_nTestCount;
    unsigned int m_nSoundId;
};

class CocosDenshionTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif //__COCOS_DENSHION_TEST__
