#ifndef _TEST_BASIC_H_
#define _TEST_BASIC_H_

#include "cocos2d.h"
#include "VisibleRect.h"

USING_NS_CC;
using namespace std;

class TestScene : public Scene
{
public: 
    TestScene(bool bPortrait = false);
    virtual void onEnter();

    virtual void runThisTest() = 0;
};

typedef Layer* (*NEWTESTFUNC)();
#define TESTLAYER_CREATE_FUNC(className) \
static Layer* create##className() \
{ return new className(); }

#define CF(className) create##className

// C++ 11

#define CL(__className__) [](){ return new __className__();}

#endif
