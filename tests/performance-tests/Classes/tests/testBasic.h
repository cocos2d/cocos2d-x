#ifndef _TEST_BASIC_H_
#define _TEST_BASIC_H_

#include "cocos2d.h"

/**
* TestScene is retained for compatibility with older versions.
* @warning It should soon be removed.
*/
class TestScene : public cocos2d::Scene
{
public: 
    TestScene(bool bPortrait = false, bool physics = false){}
    virtual void onEnter() override {}

    virtual void runThisTest() = 0;
};

// C++ 11

#define CL(__className__) [](){ return __className__::create();}
#define CLN(__className__) [](){ auto obj = new __className__(); obj->autorelease(); return obj; }

#endif
