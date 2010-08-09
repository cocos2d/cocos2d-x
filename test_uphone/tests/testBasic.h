#ifndef _TEST_BASIC_H_
#define _TEST_BASIC_H_

#include "CCScene.h"
#include "CCLayer.h"

using namespace cocos2d;

class BackToMainMenuLayer : public CCLayer
{
public:
    BackToMainMenuLayer();

    // The CallBack for back to the main menu scene
    // void MainMenuCallback(UxObject* pSender);
};

class TestScene : public CCScene
{
public:
    TestScene();

    virtual void runThisTest() = 0;
};

#endif
