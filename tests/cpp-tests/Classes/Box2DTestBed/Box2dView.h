#ifndef _BOX2D_VIEW_H_
#define _BOX2D_VIEW_H_

#include "../BaseTest.h"
#include "renderer/CCCustomCommand.h"

DEFINE_TEST_SUITE(Box2dTestBedSuite);

class Box2dTestBed : public TestCase
{
    int        m_entryID;
    EventListenerTouchOneByOne* _touchListener;
public:
    static Box2dTestBed* createWithEntryID(int entryId);

    Box2dTestBed();
    virtual ~Box2dTestBed();

    bool initWithEntryID(int entryId);

    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
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
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

//    virtual void registerWithTouchDispatcher();
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    
    void onKeyPressed(EventKeyboard::KeyCode code, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode code, Event* event);
    //virtual void accelerometer(UIAccelerometer* accelerometer, Acceleration* acceleration);

    static Box2DView* viewWithEntryID(int entryId);
protected:
    void onDraw(const Mat4 &transform, uint32_t flags);

    CustomCommand _customCmd;
};

#endif
