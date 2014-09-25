#ifndef _OPEN_URL_TEST_H_
#define _OPEN_URL_TEST_H_

#include "cocos2d.h"
#include "../testBasic.h"

class OpenURLTest : public Layer
{
public:
    OpenURLTest();
    ~OpenURLTest();

    void onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event);
private:
    cocos2d::Label* _label;
};

class OpenURLTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif // _OPEN_URL_TEST_H_
