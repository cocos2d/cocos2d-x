#ifndef _DRAW_PRIMITIVES_TEST_H_
#define _DRAW_PRIMITIVES_TEST_H_

////----#include "cocos2d.h"
#include "../testBasic.h"

class DrawPrimitivesTest : public CCLayer
{
public:
	DrawPrimitivesTest();
	virtual void draw();
};

class DrawPrimitivesTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
