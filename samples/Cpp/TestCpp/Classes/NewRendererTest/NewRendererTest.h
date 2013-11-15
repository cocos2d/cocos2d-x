//
// Created by NiTe Luo on 11/1/13.
//



#ifndef __NewRendererTest_H_
#define __NewRendererTest_H_

#include "cocos2d.h"
#include "../testBasic.h"
#include "../BaseTest.h"

using namespace std;

#define kTagSpriteBatchNode 100

class NewRendererTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

class MultiSceneTest : public BaseTest
{
public:
    MultiSceneTest();
    virtual ~MultiSceneTest();

    virtual string title();
    virtual string subtitle();
    virtual void onEnter();

    void restartCallback(Object* sender);
    void nextCallback(Object* sender);
    void backCallback(Object* sender);
};

class NewSpriteTest : public MultiSceneTest
{
public:
    NewSpriteTest();
    virtual ~NewSpriteTest();

    virtual string title();
    virtual string subtitle();

    void createSpriteTest();
    void createNewSpriteTest();
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);

protected:

};

class NewSpriteBatchTest : public MultiSceneTest
{
public:
    NewSpriteBatchTest();
    virtual ~NewSpriteBatchTest();

    virtual string title();
    virtual string subtitle();

    void onTouchesEnded(const vector<Touch*>& touches, Event* event);
    void addNewSpriteWithCoords(Point p);

};




#endif //__NewRendererTest_H_
