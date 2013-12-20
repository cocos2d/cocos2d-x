#ifndef __BUGS_TEST_H__
#define __BUGS_TEST_H__

#include "../testBasic.h"

class BugsTestMainLayer : public Layer
{
public:
    virtual void onEnter();

    void onTouchesBegan(const std::vector<Touch*>& touches, Event  *event);
    void onTouchesMoved(const std::vector<Touch*>&touches, Event  *event);

protected:
    Point _beginPos;
    Menu* _itmeMenu;
};

class BugsTestBaseLayer : public Layer
{
public:
    virtual void onEnter();
    void backCallback(Object* sender);
};

class BugsTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
