#ifndef __DIRECTOR_TEST_H__
#define __DIRECTOR_TEST_H__

#include "../testBasic.h"

class DirectorTest: public CCLayer
{
public:
    virtual bool init();

    void restartCallback(CCObject* pSender);
    void nextCallback(CCObject* pSender);
    void backCallback(CCObject* pSender);

    virtual std::string title();
    virtual std::string subtitle();
};

class Director1 : public DirectorTest
{
public:
    virtual bool init();

    void newOrientation();
    void rotateDevice(CCObject* pSender);
    void ccTouchesEnded(CCSet * touches, CCEvent* event);

    virtual std::string title();
    virtual std::string subtitle();
};

class DirectorTestScene : public TestScene
{
public:
    virtual void runThisTest();

    virtual void MainMenuCallback(CCObject* pSender);
};

#endif
