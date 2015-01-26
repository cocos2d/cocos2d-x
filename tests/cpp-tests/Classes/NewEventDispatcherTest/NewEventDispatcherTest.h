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
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void backCallback(Ref* sender);
    void nextCallback(Ref* sender);
    void restartCallback(Ref* sender);
};


class TouchableSpriteTest : public EventDispatcherTestDemo
{
public:
    CREATE_FUNC(TouchableSpriteTest);
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class FixedPriorityTest : public EventDispatcherTestDemo
{
public:
    CREATE_FUNC(FixedPriorityTest);
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class RemoveListenerWhenDispatching : public EventDispatcherTestDemo
{
public:
    CREATE_FUNC(RemoveListenerWhenDispatching);
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class CustomEventTest : public EventDispatcherTestDemo
{
public:
    CREATE_FUNC(CustomEventTest);
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
private:
    EventListenerCustom* _listener;
    EventListenerCustom* _listener2;
};

class LabelKeyboardEventTest : public EventDispatcherTestDemo
{
public:
    CREATE_FUNC(LabelKeyboardEventTest);
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteAccelerationEventTest : public EventDispatcherTestDemo
{
public:
    CREATE_FUNC(SpriteAccelerationEventTest);
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class RemoveAndRetainNodeTest : public EventDispatcherTestDemo
{
public:
    CREATE_FUNC(RemoveAndRetainNodeTest);
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
private:
    Sprite* _sprite;
    bool _spriteSaved;
};

class RemoveListenerAfterAddingTest : public EventDispatcherTestDemo
{
public:
    CREATE_FUNC(RemoveListenerAfterAddingTest);
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class DirectorEventTest : public EventDispatcherTestDemo
{
public:
    CREATE_FUNC(DirectorEventTest);
    DirectorEventTest();
    virtual void onEnter() override;
    virtual void onExit() override;

    virtual void update(float dt) override;

    void onEvent1(EventCustom *event);
    void onEvent2(EventCustom *event);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;

protected:
    int _count1, _count2, _count3, _count4;
    Label *_label1, *_label2, *_label3, *_label4;
    EventListenerCustom *_event1, *_event2, *_event3, *_event4;
};

class GlobalZTouchTest : public EventDispatcherTestDemo
{
public:
    CREATE_FUNC(GlobalZTouchTest);
    GlobalZTouchTest();
    
    virtual void update(float dt) override;
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
protected:
    Sprite* _sprite;
    float _accum;
};

class StopPropagationTest : public EventDispatcherTestDemo
{
public:
    CREATE_FUNC(StopPropagationTest);
    StopPropagationTest();
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
protected:
    bool isPointInNode(Vec2 pt, Node* node);
    bool isPointInTopHalfAreaOfScreen(Vec2 pt);
};

class PauseResumeTargetTest : public EventDispatcherTestDemo
{
public:
    CREATE_FUNC(PauseResumeTargetTest);
    PauseResumeTargetTest();
    virtual ~PauseResumeTargetTest();
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
private:
};

class Issue4129 : public EventDispatcherTestDemo
{
public:
    CREATE_FUNC(Issue4129);
    Issue4129();
    virtual ~Issue4129();
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
private:
    EventListenerCustom* _customlistener;
    bool _bugFixed;
};

class Issue4160 : public EventDispatcherTestDemo
{
public:
    CREATE_FUNC(Issue4160);
    Issue4160();
    virtual ~Issue4160();
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
private:
};

class DanglingNodePointersTest : public EventDispatcherTestDemo
{
public:
    CREATE_FUNC(DanglingNodePointersTest);
    DanglingNodePointersTest();
    virtual ~DanglingNodePointersTest();
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class RegisterAndUnregisterWhileEventHanldingTest : public EventDispatcherTestDemo
{
public:
    CREATE_FUNC(RegisterAndUnregisterWhileEventHanldingTest);
    RegisterAndUnregisterWhileEventHanldingTest();
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class Issue9898 : public EventDispatcherTestDemo
{
public:
    CREATE_FUNC(Issue9898);
    Issue9898();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;

private:
    EventListenerCustom* _listener;
};

#endif /* defined(__samples__NewEventDispatcherTest__) */
