#ifndef _DRAW_PRIMITIVES_TEST_H_
#define _DRAW_PRIMITIVES_TEST_H_

#include "cocos2d.h"
#include "../testBasic.h"
#include "../BaseTest.h"

#include <string>

class BaseLayer : public BaseTest
{
public:
    BaseLayer();
    
    void restartCallback(Object* pSender);
    void nextCallback(Object* pSender);
    void backCallback(Object* pSender);
    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();
};

class DrawPrimitivesTest : public BaseLayer
{
public:
    DrawPrimitivesTest();
    
    virtual std::string title();
    virtual std::string subtitle();
    virtual void draw();
};

class DrawNodeTest : public BaseLayer
{
public:
    DrawNodeTest();
    
    virtual std::string title();
    virtual std::string subtitle();
};

class DrawPrimitivesTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
