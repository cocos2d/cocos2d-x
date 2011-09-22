#ifndef _TEST_BASIC_H_
#define _TEST_BASIC_H_

#include "cocos2d.h"

using namespace cocos2d;

class TestScene : public CCScene
{
public: 
    TestScene(bool bPortrait = false);
    virtual void onEnter();

    virtual void runThisTest() = 0;

    // The CallBack for back to the main menu scene
    virtual void MainMenuCallback(CCObject* pSender);

protected:
    bool m_bPortrait; // indicate if this test case requires portrait mode
};

#endif
