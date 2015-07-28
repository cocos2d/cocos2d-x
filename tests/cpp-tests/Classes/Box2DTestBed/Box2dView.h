#ifndef _BOX2D_VIEW_H_
#define _BOX2D_VIEW_H_

#include "../BaseTest.h"
#include "renderer/CCCustomCommand.h"

DEFINE_TEST_SUITE(Box2dTestBedSuite);

class Box2dTestBed : public TestCase
{
public:
    static Box2dTestBed* createWithEntryID(int entryId);

    Box2dTestBed();
    virtual ~Box2dTestBed();

    bool initWithEntryID(int entryId);

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
private:
    int        m_entryID;
    cocos2d::EventListenerTouchOneByOne* _touchListener;
};

struct TestEntry;
class Test;
class Box2DView : public cocos2d::Layer
{
    cocos2d::EventListenerTouchOneByOne* _touchListener;
    cocos2d::EventListenerKeyboard* _keyboardListener;
    TestEntry*    m_entry;
    Test*        m_test;
    int            m_entryID;
public:
    Box2DView(void);
    virtual ~Box2DView(void);

    bool initWithEntryID(int entryId);
    std::string title() const;
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;

//    virtual void registerWithTouchDispatcher();
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)override;
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)override;
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)override;
    
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event)override;
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event)override;
    //virtual void accelerometer(UIAccelerometer* accelerometer, cocos2d::Acceleration* acceleration);

    static Box2DView* viewWithEntryID(int entryId);
protected:
    void onDraw(const cocos2d::Mat4& transform, uint32_t flags);

    cocos2d::CustomCommand _customCmd;
};

#endif
