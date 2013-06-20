#ifndef __COCOS_DENSHION_TEST__
#define __COCOS_DENSHION_TEST__

#include "../testBasic.h"

class CocosDenshionTest : public Layer
{
public:
    CocosDenshionTest(void);
    ~CocosDenshionTest(void);

    void menuCallback(Object * pSender);
    virtual void ccTouchesMoved(Set *pTouches, Event *pEvent);
    virtual void ccTouchesBegan(Set *pTouches, Event *pEvent);
    virtual void onExit();

private:
    Menu* _itmeMenu;
    Point _beginPos;
    int _testCount;
    unsigned int _soundId;
};

class CocosDenshionTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif //__COCOS_DENSHION_TEST__
