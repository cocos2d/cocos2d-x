#ifndef __BUGS_TEST_H__
#define __BUGS_TEST_H__

#include "../testBasic.h"

class BugsTestMainLayer : public Layer
{
public:
    virtual void onEnter() override;

    void onTouchesBegan(const std::vector<Touch*>& touches, Event  *event);
    void onTouchesMoved(const std::vector<Touch*>&touches, Event  *event);

protected:
    Vec2 _beginPos;
    Menu* _itmeMenu;
};

class BugsTestBaseLayer : public Layer
{
public:
    virtual void onEnter() override;
    void backCallback(Ref* sender);
};

class BugsTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
