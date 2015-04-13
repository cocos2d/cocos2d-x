#ifndef __ANIMATION_TEST_SCENE_H__
#define __ANIMATION_TEST_SCENE_H__

#include "cocos2d.h"
#include "../../BaseTest.h"
#include "cocostudio/CocoStudio.h"

class CocoStudioActionTimelineTests : public TestSuite
{
public:
    CocoStudioActionTimelineTests();
    ~CocoStudioActionTimelineTests();
};

class ActionTimelineBaseTest : public TestCase
{
public:
    virtual std::string title() const;

    virtual bool init() override;

    // overrides
    virtual void onExit() override;

protected:
};


class TestActionTimeline : public ActionTimelineBaseTest
{
public:
    CREATE_FUNC(TestActionTimeline);

    virtual void onEnter() override;
    virtual std::string title() const override;
};

class TestChangePlaySection : public ActionTimelineBaseTest
{
public:
    CREATE_FUNC(TestChangePlaySection);

    virtual void onEnter() override;
    virtual std::string title() const override;

	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);

protected:
    cocostudio::timeline::ActionTimeline* action;
};

class TestTimelineFrameEvent : public ActionTimelineBaseTest
{
public:
    CREATE_FUNC(TestTimelineFrameEvent);

    virtual void onEnter() override;
    virtual std::string title() const override;

    void onFrameEvent(cocostudio::timeline::Frame* frame);
};

class TestTimelinePerformance : public ActionTimelineBaseTest
{
public:
    CREATE_FUNC(TestTimelinePerformance);

    virtual void onEnter() override;
    virtual std::string title() const override;
};

class TestTimelineAnimationList : public ActionTimelineBaseTest
{
public:
    CREATE_FUNC(TestTimelineAnimationList);

    virtual void onEnter() override;
    virtual std::string title() const override;
};

class TestTimelineProjectNode : public ActionTimelineBaseTest
{
public:
    CREATE_FUNC(TestTimelineProjectNode);

    virtual void onEnter() override;
    virtual std::string title() const override;
};

class TestProjectNodeForSimulator : public ActionTimelineBaseTest
{
public:
    CREATE_FUNC(TestProjectNodeForSimulator);

    virtual void onEnter() override;
    virtual std::string title() const override;
};

class TestTimelineNodeLoadedCallback : public ActionTimelineBaseTest
{
public:
    CREATE_FUNC(TestTimelineNodeLoadedCallback);

    virtual void onEnter() override;
    virtual std::string title() const override;
    
    void nodeLoadedCallback(cocos2d::Ref* sender);

};

class TestActionTimelineEase : public ActionTimelineBaseTest
{
public:
    CREATE_FUNC(TestActionTimelineEase);
    
    virtual void onEnter() override;
    virtual std::string title() const override;
};

#endif  // __ANIMATION_SCENE_H__
