#ifndef _TEST_BASIC_H_
#define _TEST_BASIC_H_

#include "cocos2d.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class TestScene : public CCScene
{
public: 
    TestScene(bool bPortrait = false);
    virtual void onEnter();

    virtual void runThisTest() = 0;

    // The CallBack for back to the main menu scene
    virtual void MainMenuCallback(CCObject* pSender);
};

#endif
