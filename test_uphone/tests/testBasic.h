#ifndef _TEST_BASIC_H_
#define _TEST_BASIC_H_

#include "CCScene.h"
#include "CCLayer.h"

using namespace cocos2d;

class TestLayer : public CCLayer
{
public:
    TestLayer();
};

class TestScene : public CCScene
{
public:
    TestScene();

    virtual void runThisTest() = 0;
};

#endif
