#ifndef _BOX2D_VIEW_H_
#define _BOX2D_VIEW_H_

//#include "cocos2d.h"
#include "../testBasic.h"

class MenuLayer : public Layer
{
    int        m_entryID;

public:
    MenuLayer(void);
    virtual ~MenuLayer(void);

    bool initWithEntryID(int entryId);

    void restartCallback(Object* sender);
    void nextCallback(Object* sender);
    void backCallback(Object* sender);

    virtual void registerWithTouchDispatcher();

    virtual bool ccTouchBegan(Touch* touch, Event* event);
    virtual void ccTouchMoved(Touch* touch, Event* event);

public:
    static MenuLayer* menuWithEntryID(int entryId);
};

struct TestEntry;
class Test;
class Box2DView : public Layer
{
    TestEntry*    m_entry;
    Test*        m_test;
    int            m_entryID;
public:
    Box2DView(void);
    virtual ~Box2DView(void);

    bool initWithEntryID(int entryId);
    std::string title();
    void tick(float dt);
    void draw();

    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(Touch* touch, Event* event);
    virtual void ccTouchMoved(Touch* touch, Event* event);
    virtual void ccTouchEnded(Touch* touch, Event* event);
    //virtual void accelerometer(UIAccelerometer* accelerometer, Acceleration* acceleration);

    static Box2DView* viewWithEntryID(int entryId);
};

class Box2dTestBedScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
