#ifndef __ANIMATION_TEST_SCENE_H__
#define __ANIMATION_TEST_SCENE_H__

#include "cocos2d.h"
#include "../../VisibleRect.h"
#include "../../testBasic.h"
#include "cocostudio/CocoStudio.h"

using namespace cocostudio::timeline;


class ActionTimelineTestScene : public TestScene
{
public: 
    ActionTimelineTestScene(bool bPortrait = false);

    virtual void runThisTest();

    // The CallBack for back to the main menu scene
    virtual void MainMenuCallback(Ref* pSender);
};

enum {
    TEST_ANIMATIONELEMENT = 0,
    TEST_TIMELINE_PERFORMACE,

    TEST_ANIMATION_LAYER_COUNT
};

class ActionTimelineTestLayer : public Layer
{
public:
    virtual std::string title() const;
    virtual std::string subtitle() const;

    virtual void restartCallback(Ref* pSender);
    virtual void nextCallback(Ref* pSender);
    virtual void backCallback(Ref* pSender);

    // overrides
    virtual void onEnter() override;
    virtual void onExit() override;

protected:
    MenuItemImage *restartItem;
    MenuItemImage *nextItem;
    MenuItemImage *backItem;
};


class TestActionTimeline : public ActionTimelineTestLayer
{
public:
    virtual void onEnter();
    virtual std::string title() const override;
};

class TestTimelinePerformance : public ActionTimelineTestLayer
{
public:
    virtual void onEnter();
    virtual std::string title() const override;
};

#endif  // __ANIMATION_SCENE_H__