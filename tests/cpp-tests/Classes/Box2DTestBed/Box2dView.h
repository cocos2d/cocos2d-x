#ifndef _BOX2D_VIEW_H_
#define _BOX2D_VIEW_H_

//#include "cocos2d.h"
#include "../testBasic.h"
#include "renderer/CCCustomCommand.h"

class MenuLayer : public Layer
{
    int        m_entryID;
    EventListenerTouchOneByOne* _touchListener;
public:
    MenuLayer(void);
    virtual ~MenuLayer(void);

    bool initWithEntryID(int entryId);

    void restartCallback(Ref* sender);
    void nextCallback(Ref* sender);
    void backCallback(Ref* sender);


    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);

public:
    static MenuLayer* menuWithEntryID(int entryId);
};

struct TestEntry;
class Test;
class Box2DView : public Layer
{
    EventListenerTouchOneByOne* _touchListener;
    EventListenerKeyboard* _keyboardListener;
    TestEntry*    m_entry;
    Test*        m_test;
    int            m_entryID;
public:
    Box2DView(void);
    virtual ~Box2DView(void);

    bool initWithEntryID(int entryId);
    std::string title() const;
    virtual void draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated) override;

//    virtual void registerWithTouchDispatcher();
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    
    void onKeyPressed(EventKeyboard::KeyCode code, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode code, Event* event);
    //virtual void accelerometer(UIAccelerometer* accelerometer, Acceleration* acceleration);

    static Box2DView* viewWithEntryID(int entryId);
protected:
    void onDraw(const kmMat4 &transform, bool transformUpdated);

    CustomCommand _customCmd;
};

class Box2dTestBedScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
