/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

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
