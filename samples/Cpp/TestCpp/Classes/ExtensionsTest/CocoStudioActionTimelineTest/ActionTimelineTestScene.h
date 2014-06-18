#ifndef __ACTION_TIMELINE_SCENE_H__
#define __ACTION_TIMELINE_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "../../VisibleRect.h"
#include "../../testBasic.h"

using namespace cocostudio::timeline;

class TimelineTestScene : public TestScene
{
public: 
    TimelineTestScene(bool bPortrait = false);

    virtual void runThisTest();

    // The CallBack for back to the main menu scene
    virtual void MainMenuCallback(CCObject* pSender);
};

enum {
    TEST_ACTION_TIMELINE = 0,
    TEST_CHANGE_PLAY_SECTION,
    TEST_TIMELINE_FRAME_EVENT,
    TEST_TIMELINE_PERFORMACE,

    TEST_ACTION_LAYER_COUNT
};

class ActionTimelineTestLayer : public CCLayer
{
public:
    virtual void onEnter();
    virtual void onExit();

    virtual std::string title();
    virtual std::string subtitle();

    virtual void restartCallback(CCObject* pSender);
    virtual void nextCallback(CCObject* pSender);
    virtual void backCallback(CCObject* pSender);

    virtual void draw();

protected:
    CCMenuItemImage *restartItem;
    CCMenuItemImage *nextItem;
    CCMenuItemImage *backItem;
};


class TestActionTimeline : public ActionTimelineTestLayer
{
public:
    virtual void onEnter();
    virtual std::string title();
};


class TestChangePlaySection : public ActionTimelineTestLayer
{
public:
    virtual void onEnter();
    virtual void onExit();
    virtual std::string title();

    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher();
protected:
    ActionTimeline* action;
};

class TestTimelineFrameEvent : public ActionTimelineTestLayer
{
public:
    virtual void onEnter();
    virtual std::string title();

    void onFrameEvent(Frame* frame);
};

class TestTimelinePerformance : public ActionTimelineTestLayer
{
public:
    virtual void onEnter();
    virtual std::string title();
};

#endif  // __ACTION_TIMELINE_SCENE_H__