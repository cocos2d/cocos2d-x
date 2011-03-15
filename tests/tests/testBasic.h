#ifndef _TEST_BASIC_H_
#define _TEST_BASIC_H_

#include "cocos2d.h"

using namespace cocos2d;

class BackToMainMenuLayer : public CCLayer
{
public:
    BackToMainMenuLayer();

    // The CallBack for back to the main menu scene
    virtual void MainMenuCallback(CCObject* pSender);
};

class TestScene : public CCScene
{
public:
    TestScene();

    virtual void runThisTest() = 0;
};

#endif
