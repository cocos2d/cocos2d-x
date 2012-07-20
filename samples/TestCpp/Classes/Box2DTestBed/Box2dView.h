#ifndef _BOX2D_VIEW_H_
#define _BOX2D_VIEW_H_

//#include "cocos2d.h"
#include "../testBasic.h"

class MenuLayer : public CCLayer
{
    int        m_entryID;

public:
    MenuLayer(void);
    virtual ~MenuLayer(void);

    bool initWithEntryID(int entryId);

    void restartCallback(CCObject* sender);
    void nextCallback(CCObject* sender);
    void backCallback(CCObject* sender);

    virtual void registerWithTouchDispatcher();

    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);

public:
    static MenuLayer* menuWithEntryID(int entryId);
};

struct TestEntry;
class Test;
class Box2DView : public CCLayer
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
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    //virtual void accelerometer(UIAccelerometer* accelerometer, CCAcceleration* acceleration);

    static Box2DView* viewWithEntryID(int entryId);
};

class Box2dTestBedScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
