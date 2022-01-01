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

#ifndef __MOUSE_TEST_H_
#define __MOUSE_TEST_H_

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)

#include "cocos2d.h"
#include "../BaseTest.h"

DEFINE_TEST_SUITE(MouseTests);

class BaseMouseTest : public TestCase
{
public:
    
};

class MouseEventTest : public BaseMouseTest
{
public:
    CREATE_FUNC(MouseEventTest);
    MouseEventTest();
    ~MouseEventTest();

    void onMouseDown(cocos2d::Event* event);
    void onMouseUp(cocos2d::Event* event);
    void onMouseMove(cocos2d::Event* event);
    void onMouseScroll(cocos2d::Event* event);
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

private:
    cocos2d::Label*   _labelAction;
    cocos2d::Label*   _labelPosition;
    cocos2d::EventListenerMouse* _mouseListener;
};

class HideMouseTest : public BaseMouseTest
{
public:
    CREATE_FUNC(HideMouseTest);
    HideMouseTest();
    ~HideMouseTest();
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
private:
    cocos2d::EventListenerMouse* _lis;
};

class CursorTest : public BaseMouseTest
{
public:
    CREATE_FUNC(CursorTest);
    CursorTest();
    ~CursorTest();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;

private:
    int _cursor;
    cocos2d::EventListenerMouse* _lis;
};


class CursorPositionTest : public BaseMouseTest
{
public:
	CREATE_FUNC(CursorPositionTest);
	CursorPositionTest();
	~CursorPositionTest();

	void switchScreenSize();
	void usingFrameSize();

	void onMouseMove(cocos2d::Event * event);

	virtual std::string title() const override;
	virtual std::string subtitle() const override;
private:
	int _mode;
	cocos2d::EventListenerMouse* _lis;
	cocos2d::Label* _lblMousePos;
};

class FirstPersonShooter : public BaseMouseTest
{
public:
	CREATE_FUNC(FirstPersonShooter);
	FirstPersonShooter();
	~FirstPersonShooter();

	virtual void update(float dt) override;

	void switchScreenSize();

	void onMouseMove(cocos2d::Event * evnt);

	void onFocused();
	void onUnFocused();

	void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
	void keyReleased(cocos2d::EventKeyboard::KeyCode keyCode);

	virtual std::string title() const override;
	virtual std::string subtitle() const override;
private:
	void processInput();
	void updateCamera(float dt);

	int _mode;
	cocos2d::EventListenerMouse* _lis;
	cocos2d::EventListenerKeyboard* _kbLis;
	bool _keyStates[256];
	cocos2d::Label* _lblMousePos;
	cocos2d::Camera* _camera;

	float _sensitivity, _vel;
    float _pitch, _yaw;
    cocos2d::Vec2 _prevMousePos;
	int _forward, _sideward, _upward;

	bool _cursorFree;
	bool _focused;
    bool _firstMove;
};
#endif // !CC_TARGET_PLATFORM

#endif // !__MOUSE_TEST_H_
