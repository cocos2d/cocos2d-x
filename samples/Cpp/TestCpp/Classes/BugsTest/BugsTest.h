#ifndef __BUGS_TEST_H__
#define __BUGS_TEST_H__

#include "../testBasic.h"

class BugsTestMainLayer : public Layer
{
public:
    virtual void onEnter();

    virtual void ccTouchesBegan(Set  *touches, Event  *event);
    virtual void ccTouchesMoved(Set  *touches, Event  *event);

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
