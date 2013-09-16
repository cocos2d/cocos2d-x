//
//  NewEventDispatcherTest.h
//  samples
//
//  Created by James Chen on 9/13/13.
//
//

#ifndef __samples__NewEventDispatcherTest__
#define __samples__NewEventDispatcherTest__

#include "cocos2d.h"
#include "../testBasic.h"
#include "../BaseTest.h"

class EventDispatcherTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

class EventDispatcherTestDemo : public BaseTest
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
    void backCallback(Object* sender);
    void nextCallback(Object* sender);
    void restartCallback(Object* sender);
};


class TouchableSpriteTest : public EventDispatcherTestDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
};

class FixedPriorityTest : public EventDispatcherTestDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
};


#endif /* defined(__samples__NewEventDispatcherTest__) */
