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

#include "MouseTest.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
#include "Sprite3DTest/DrawNode3D.h"

USING_NS_CC;

template <typename T> std::string tostr(const T& t) { std::ostringstream os; os<<t; return os.str(); }

MouseTests::MouseTests()
{
    ADD_TEST_CASE(MouseEventTest);
    ADD_TEST_CASE(HideMouseTest);
    ADD_TEST_CASE(CursorTest);
	ADD_TEST_CASE(CursorPositionTest);
	ADD_TEST_CASE(FirstPersonShooter);
}

//------------------------------------------------------------------
//
// MouseEventTest
//
//------------------------------------------------------------------
MouseEventTest::MouseEventTest()
{
    auto s = Director::getInstance()->getWinSize();

    //Create a label to display the mouse action
    _labelAction = Label::createWithTTF("Click mouse button and see this change", "fonts/arial.ttf", 22);
    _labelAction->setPosition(Vec2(s.width/2, s.height*2/3));
    addChild(_labelAction, 0);

    //Create a label to display the mouse position
    _labelPosition = Label::createWithTTF("Mouse not supported on this device", "fonts/arial.ttf", 22);
    _labelPosition->setPosition(Vec2(s.width/2, s.height/3));
    addChild(_labelPosition);


    _mouseListener = EventListenerMouse::create();
    _mouseListener->onMouseMove = CC_CALLBACK_1(MouseEventTest::onMouseMove, this);
    _mouseListener->onMouseUp = CC_CALLBACK_1(MouseEventTest::onMouseUp, this);
    _mouseListener->onMouseDown = CC_CALLBACK_1(MouseEventTest::onMouseDown, this);
    _mouseListener->onMouseScroll = CC_CALLBACK_1(MouseEventTest::onMouseScroll, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
}

MouseEventTest::~MouseEventTest()
{
    _eventDispatcher->removeEventListener(_mouseListener);
}

void MouseEventTest::onMouseDown(Event *event)
{
    EventMouse* e = (EventMouse*)event;
    std::string str = "Mouse Down detected, Key: ";
    str += tostr(static_cast<int>(e->getMouseButton()));
    _labelAction->setString(str);
}

void MouseEventTest::onMouseUp(Event *event)
{
    EventMouse* e = (EventMouse*)event;
    std::string str = "Mouse Up detected, Key: ";
    str += tostr(static_cast<int>(e->getMouseButton()));
    _labelAction->setString(str);
}

void MouseEventTest::onMouseMove(Event *event)
{
    EventMouse* e = (EventMouse*)event;
    std::string str = "MousePosition X:";
    str = str + tostr(e->getCursorX()) + " Y:" + tostr(e->getCursorY());
    _labelPosition->setString(str);
}

void MouseEventTest::onMouseScroll(Event *event)
{
    EventMouse* e = (EventMouse*)event;
    std::string str = "Mouse Scroll detected, X: ";
    str = str + tostr(e->getScrollX()) + " Y: " + tostr(e->getScrollY());
    _labelAction->setString(str);
}

std::string MouseEventTest::title() const
{
    return "Mouse Event Test";
}

std::string MouseEventTest::subtitle() const
{
    return "This tests the mouse events";
}

//------------------------------------------------------------------
//
// HideMouseTest
//
//------------------------------------------------------------------

HideMouseTest::HideMouseTest()
{
    
    _lis = EventListenerMouse::create();
    _lis->onMouseDown = [](Event* e){
        Director::getInstance()->getOpenGLView()->setCursorVisible(false);
    };
    
    _lis->onMouseUp = [](Event* e){
        Director::getInstance()->getOpenGLView()->setCursorVisible(true);
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_lis, this);
}

HideMouseTest::~HideMouseTest()
{
    _eventDispatcher->removeEventListener(_lis);
}

std::string HideMouseTest::title() const
{
    return "Hide/Show Mouse";
}

std::string HideMouseTest::subtitle() const
{
    return "Click to hide mouse";
}

//------------------------------------------------------------------
//
// CursorTest
//
//------------------------------------------------------------------

CursorTest::CursorTest()
{
    _cursor = 0;
    _lis = EventListenerMouse::create();
    _lis->onMouseDown = [this](Event* e){
        _cursor = (_cursor + 1) % 3;
        switch (_cursor) {
            case 1:
                Director::getInstance()->getOpenGLView()->setCursor("InputTest/cursor1.png");
                break;
            case 2:
                Director::getInstance()->getOpenGLView()->setCursor("InputTest/cursor2.png", Point::ANCHOR_MIDDLE);
                break;
            default:
                Director::getInstance()->getOpenGLView()->setDefaultCursor();
                break;
        }
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(_lis, this);
}

CursorTest::~CursorTest()
{
    _eventDispatcher->removeEventListener(_lis);
}

std::string CursorTest::title() const
{
    return "Custom Mouse Cursor";
}

std::string CursorTest::subtitle() const
{
    return "Click to change cursor";
}


//------------------------------------------------------------------
//
// CursorPositionTest
//
//------------------------------------------------------------------
CursorPositionTest::CursorPositionTest()
{
	_mode = 1;

	_lis = EventListenerMouse::create();
	_lis->onMouseMove = CC_CALLBACK_1(CursorPositionTest::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_lis, this);

	TTFConfig ttfConfig("fonts/arial.ttf", 10);

	auto lbl1 = Label::createWithTTF(ttfConfig, "Switch Screen Size");
	auto menuItem1 = MenuItemLabel::create(lbl1, CC_CALLBACK_0(CursorPositionTest::switchScreenSize, this));

	auto lbl2 = Label::createWithTTF(ttfConfig, "Set cursor to middle using getFrameSize()");
	auto menuItem2 = MenuItemLabel::create(lbl2, CC_CALLBACK_0(CursorPositionTest::usingFrameSize, this));

	auto menu = Menu::create(menuItem1, menuItem2, nullptr);
	menu->setPosition(Vec2::ZERO);
	menuItem1->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	menuItem1->setPosition(Vec2(VisibleRect::left().x, VisibleRect::top().y - 100));
	menuItem2->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	menuItem2->setPosition(Vec2(VisibleRect::left().x, VisibleRect::top().y - 120));
	addChild(menu);

	_lblMousePos = Label::createWithTTF(ttfConfig, "MousePosition (move the mouse)");
	_lblMousePos->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	_lblMousePos->setPosition(Vec2(VisibleRect::left().x, VisibleRect::top().y - 160));
	addChild(_lblMousePos);
}

CursorPositionTest::~CursorPositionTest()
{
	_eventDispatcher->removeEventListener(_lis);
}

void CursorPositionTest::switchScreenSize()
{
	GLViewImpl* view = dynamic_cast<GLViewImpl*>(Director::getInstance()->getOpenGLView());

	switch (_mode)
	{
	case 1:
		view->setWindowed(480, 320);
		break;
	case 2:
		view->setWindowed(960, 640);
		break;
	case 3:
		view->setFullscreen();
		break;
	case 4:
		view->setFullscreen(1);
		_mode = 0;
		break;
	}
	_mode++;
}

void CursorPositionTest::usingFrameSize()
{
	GLView* view = Director::getInstance()->getOpenGLView();

	float x = view->getFrameSize().width / 2;
	float y = view->getFrameSize().height / 2;

	view->setCursorPosition(x, y);
}

void CursorPositionTest::onMouseMove(Event *event)
{
	EventMouse* e = (EventMouse*)event;
	std::string str = "MousePosition X:";
	str = str + tostr(e->getCursorX()) + " Y:" + tostr(e->getCursorY());
	_lblMousePos->setString(str);
}

std::string CursorPositionTest::title() const
{
	return "Set Mouse Position";
}

std::string CursorPositionTest::subtitle() const
{
	return "Mouse Should spawn at middle of screen";
}


//------------------------------------------------------------------
//
// FirstPersonShooter
//
//------------------------------------------------------------------
FirstPersonShooter::FirstPersonShooter()
{
	auto layer3D = Layer::create();

	DrawNode3D* line = DrawNode3D::create();
	//draw x
	for (int j = -20; j <= 20; j++)
	{
		line->drawLine(Vec3(-100, 0, 5 * j), Vec3(100, 0, 5 * j), Color4F(1, 0, 0, 1));
	}
	//draw z
	for (int j = -20; j <= 20; j++)
	{
		line->drawLine(Vec3(5 * j, 0, -100), Vec3(5 * j, 0, 100), Color4F(0, 0, 1, 1));
	}
	//draw y
	line->drawLine(Vec3(0, -50, 0), Vec3(0, 0, 0), Color4F(0, 0.5, 0, 1));
	line->drawLine(Vec3(0, 0, 0), Vec3(0, 50, 0), Color4F(0, 1, 0, 1));
	line->setAnchorPoint(Vec2::ZERO);
	line->setPosition3D(Vec3::ZERO);
	layer3D->addChild(line);

	_mode = 1;

	_lis = EventListenerMouse::create();
	_lis->onMouseMove = CC_CALLBACK_1(FirstPersonShooter::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_lis, this);

	for (int i = 0; i < 256; i++)
		_keyStates[i] = false;

	_kbLis = EventListenerKeyboard::create();

	Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);
	_kbLis->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* ccevnt)
	{
		_keyStates[static_cast<int>(keyCode)] = true;
		keyPressed(keyCode);
	};
	_kbLis->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* ccevnt)
	{
		_keyStates[static_cast<int>(keyCode)] = false;
		keyReleased(keyCode);
	};
	getEventDispatcher()->addEventListenerWithFixedPriority(_kbLis, 1);

	TTFConfig ttfConfig("fonts/arial.ttf", 10);

	auto lbl1 = Label::createWithTTF(ttfConfig, "Switch Screen Size");
	auto menuItem1 = MenuItemLabel::create(lbl1, CC_CALLBACK_0(FirstPersonShooter::switchScreenSize, this));

	auto menu = Menu::create(menuItem1, nullptr);
	menu->setPosition(Vec2::ZERO);
	menuItem1->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	menuItem1->setPosition(Vec2(VisibleRect::left().x, VisibleRect::top().y - 100));
	addChild(menu);

	_lblMousePos = Label::createWithTTF(ttfConfig, "MousePosition (move the mouse)");
	_lblMousePos->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	_lblMousePos->setPosition(Vec2(VisibleRect::left().x, VisibleRect::top().y - 160));
	addChild(_lblMousePos);

	Size winSize = Director::getInstance()->getWinSize();
	_camera = Camera::createPerspective(60, (GLfloat)winSize.width / winSize.height, 0.1f, 800.0f);
	_camera->setDepth(-1);
	_camera->setCameraFlag(CameraFlag::USER1);
	_camera->setPosition3D(Vec3(0.0f, 5.0f, 20.0f));
	_camera->lookAt(Vec3::ZERO);
	_camera->setRotation3D(Vec3::ZERO);
	layer3D->addChild(_camera);

	_sensitivity = 0.1f;
	_vel = 5.0f;
	_forward = 0;
	_sideward = 0;
	_upward = 0;
    _pitch = 0;
    _yaw = 0;

	layer3D->setCameraMask(static_cast<int>(CameraFlag::USER1));
	addChild(layer3D);

	_cursorFree = false;
	_focused = true;
    _firstMove = true;

	_eventDispatcher->addCustomEventListener(GLViewImpl::EVENT_WINDOW_FOCUSED, CC_CALLBACK_0(FirstPersonShooter::onFocused, this));
	_eventDispatcher->addCustomEventListener(GLViewImpl::EVENT_WINDOW_UNFOCUSED, CC_CALLBACK_0(FirstPersonShooter::onUnFocused, this));

    Director::getInstance()->getOpenGLView()->setInputModeCursorDisabled();
    
	scheduleUpdate();
}

FirstPersonShooter::~FirstPersonShooter()
{
	_eventDispatcher->removeEventListener(_lis);
	_eventDispatcher->removeEventListener(_kbLis);
	_eventDispatcher->removeCustomEventListeners(GLViewImpl::EVENT_WINDOW_FOCUSED);
	_eventDispatcher->removeCustomEventListeners(GLViewImpl::EVENT_WINDOW_UNFOCUSED);
    
    Director::getInstance()->getOpenGLView()->setInputModeCursorNormal();
}

void FirstPersonShooter::update(float dt)
{
	processInput();
	updateCamera(dt);
}

void FirstPersonShooter::switchScreenSize()
{
	GLViewImpl* view = dynamic_cast<GLViewImpl*>(Director::getInstance()->getOpenGLView());

	switch (_mode)
	{
	case 1:
		view->setWindowed(480, 320);
		break;
	case 2:
		view->setWindowed(960, 640);
		break;
	case 3:
		view->setFullscreen();
		break;
	case 4:
		view->setFullscreen(1);
		_mode = 0;
		break;
	}
	_mode++;
}

void FirstPersonShooter::onMouseMove(Event *evnt)
{
	EventMouse* e = dynamic_cast<EventMouse*>(evnt);
	std::string str = "MousePosition X:";
	str = str + tostr(e->getCursorX()) + " Y:" + tostr(e->getCursorY());
	_lblMousePos->setString(str);
    
	if (_cursorFree || !_focused)
		return;
    
    if (_firstMove)
    {
        _prevMousePos.x = e->getCursorX();
        _prevMousePos.y = e->getCursorY();
        _firstMove = false;
    }
    
    float xoffset = e->getCursorX() - _prevMousePos.x;
    float yoffset = _prevMousePos.y - e->getCursorY();
    
    _prevMousePos.x = e->getCursorX();
    _prevMousePos.y = e->getCursorY();
    
    xoffset *= _sensitivity;
    yoffset *= _sensitivity;
    
    _yaw   -= xoffset;
    _pitch -= yoffset;
    
    if (_pitch > 89.0f)
        _pitch = 89.0f;
    if (_pitch < -89.0f)
        _pitch = -89.0f;
    
    _camera->setRotation3D(Vec3(_pitch, _yaw, 0.0f));
}

void FirstPersonShooter::onFocused()
{
	_focused = true;
}

void FirstPersonShooter::onUnFocused()
{
	_focused = false;
}

void FirstPersonShooter::keyPressed(EventKeyboard::KeyCode keyCode)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_R:
		_cursorFree = true;
        Director::getInstance()->getOpenGLView()->setInputModeCursorNormal();
		break;
    default:
        break;
	}
}

void FirstPersonShooter::keyReleased(EventKeyboard::KeyCode keyCode)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_R:
		_cursorFree = false;
        _firstMove = true;
        Director::getInstance()->getOpenGLView()->setInputModeCursorDisabled();
		break;
    default:
        break;
	}
}

std::string FirstPersonShooter::title() const
{
	return "First Person Shooter";
}

std::string FirstPersonShooter::subtitle() const
{
    return "Move the Camera with mouse / Hold R to release cursor";
}

void FirstPersonShooter::processInput()
{
	_forward = 0;
	_sideward = 0;
	_upward = 0;

	if (_keyStates[static_cast<int>(EventKeyboard::KeyCode::KEY_W)])
		_forward = 1;
	else if (_keyStates[static_cast<int>(EventKeyboard::KeyCode::KEY_S)])
		_forward = -1;
	if (_keyStates[static_cast<int>(EventKeyboard::KeyCode::KEY_D)])
		_sideward = 1;
	else if (_keyStates[static_cast<int>(EventKeyboard::KeyCode::KEY_A)])
		_sideward = -1;
	if (_keyStates[static_cast<int>(EventKeyboard::KeyCode::KEY_SPACE)])
		_upward = 1;
	else if (_keyStates[static_cast<int>(EventKeyboard::KeyCode::KEY_LEFT_SHIFT)])
		_upward = -1;
}

void FirstPersonShooter::updateCamera(float dt)
{
	Vec3 cameraDir;
	_camera->getNodeToWorldTransform().getForwardVector(&cameraDir);
	cameraDir.normalize();

	Vec3 cameraRightDir;
	_camera->getNodeToWorldTransform().getRightVector(&cameraRightDir);
	cameraRightDir.normalize();

	Vec3 upDir;
	_camera->getNodeToWorldTransform().getUpVector(&upDir);
	upDir.normalize();

	Vec3 cameraPos = _camera->getPosition3D();

	cameraPos += cameraDir * _forward * (_vel * dt);
	cameraPos += cameraRightDir * _sideward * (_vel * dt);
	//cameraPos += upDir * _upward * (vel * dt);
	cameraPos.y += _upward * (_vel * dt);

	_camera->setPosition3D(cameraPos);
}

#endif // !CC_TARGET_PLATFORM
