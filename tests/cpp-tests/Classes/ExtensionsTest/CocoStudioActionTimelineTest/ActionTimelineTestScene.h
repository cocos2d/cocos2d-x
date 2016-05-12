#ifndef __ANIMATION_TEST_SCENE_H__
#define __ANIMATION_TEST_SCENE_H__

#include "cocos2d.h"
#include "../../BaseTest.h"
#include "editor-support/cocostudio/CocoStudio.h"

class CocoStudioActionTimelineTests : public TestSuite
{
public:
    CocoStudioActionTimelineTests();
    ~CocoStudioActionTimelineTests();
};

class ActionTimelineBaseTest : public TestCase
{
public:
    virtual std::string title() const override;

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

class TestActionTimelineSkeleton : public ActionTimelineBaseTest
{
public:
    CREATE_FUNC(TestActionTimelineSkeleton);

    virtual void onEnter() override;
    
    virtual std::string title() const override;

private:
    bool _changedDisplay;
    bool _changedDisplays;
};

class TestTimelineExtensionData : public ActionTimelineBaseTest
{
public:
    CREATE_FUNC(TestTimelineExtensionData);
    virtual void onEnter() override;
    virtual std::string title() const override;
};

class TestActionTimelineBlendFuncFrame : public ActionTimelineBaseTest
{
public:
    CREATE_FUNC(TestActionTimelineBlendFuncFrame);
    virtual void onEnter() override;
    virtual std::string title() const override;
};

class TestAnimationClipEndCallBack : public ActionTimelineBaseTest
{
public:
    CREATE_FUNC(TestAnimationClipEndCallBack);

    virtual void onEnter() override;
    virtual std::string title() const override;
};

class TestActionTimelinePlayableFrame : public ActionTimelineBaseTest
{
public:
    CREATE_FUNC(TestActionTimelinePlayableFrame);

    virtual void onEnter() override;
    virtual std::string  title() const override;
};

class TestActionTimelineIssueWith2SameActionInOneNode : public ActionTimelineBaseTest
{
public:
    CREATE_FUNC(TestActionTimelineIssueWith2SameActionInOneNode);

    virtual void onEnter() override;
    virtual std::string  title() const override;
};

#endif  // __ANIMATION_SCENE_H__
