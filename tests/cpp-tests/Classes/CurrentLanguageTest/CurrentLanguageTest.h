#ifndef _CURRENT_LANGUAGE_TEST_H_
#define _CURRENT_LANGUAGE_TEST_H_

#include "cocos2d.h"
#include "../testScene.h"

class CurrentLanguageTest : public Layer
{
public:
    CurrentLanguageTest();
};

class CurrentLanguageTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif // _CURRENT_LANGUAGE_TEST_H_
