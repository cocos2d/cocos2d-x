#include "CameraTest.h"

#define CAMERA_ZOOM_VELOCITY 0.02f

CameraTestScene::CameraTestScene()
{}

CameraTestScene::~CameraTestScene()
{}

void CameraTestScene::runThisTest()
{
	auto camView = CameraView::create();
	addChild(camView);

	auto layer = CameraTest::create();
	camView->addChild(layer);

	addChild(layer->getCamera());
	camView->setCamera(layer->getCamera());

	Director::getInstance()->replaceScene(this);
}

CameraTest::CameraTest():
	_moving(false),
	_xCursor(0),
	_yCursor(0)
{
	_camera = Camera::create();
	Size winSize = Director::getInstance()->getWinSize();
	_camera->setFOV(winSize.width, winSize.height);
	_camera->setZoomLimit(0.5f, 1.2f);

	_mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseMove = CC_CALLBACK_1(CameraTest::onMouseMove, this);
	_mouseListener->onMouseUp = CC_CALLBACK_1(CameraTest::onMouseUp, this);
	_mouseListener->onMouseDown = CC_CALLBACK_1(CameraTest::onMouseDown, this);
	_mouseListener->onMouseScroll = CC_CALLBACK_1(CameraTest::onMouseScroll, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
}

CameraTest::~CameraTest()
{
	_eventDispatcher->removeEventListener(_mouseListener);
}

void CameraTest::onMouseDown(Event* evt)
{
	EventMouse* e = (EventMouse*)evt;
	if (e->getMouseButton() == 0)
	{
		_moving = true;
		_xCursor = e->getCursorX();
		_yCursor = e->getCursorY();
	}
	
}

void CameraTest::onMouseUp(Event* evt)
{
	EventMouse* e = (EventMouse*)evt;
	if (e->getMouseButton() == 0)
	{
		_moving = false;
	}
	else if (e->getMouseButton() == 1)
	{
		_camera->setPosition(0, 0);
		_camera->setZoom(1.f);
	}
}

void CameraTest::onMouseMove(Event* evt)
{
	if (_moving)
	{
		EventMouse* e = (EventMouse*)evt;
		int xCursor = e->getCursorX();
		int yCursor = e->getCursorY();

		_camera->setPosition(_camera->getPositionX() + _xCursor - xCursor, _camera->getPositionY() + _yCursor - yCursor);

		_xCursor = xCursor;
		_yCursor = yCursor;
	}
}

void CameraTest::onMouseScroll(Event* evt)
{
	EventMouse* e = (EventMouse*)evt;
	float zoom = e->getScrollY() * CAMERA_ZOOM_VELOCITY;

	_camera->addZoom(-zoom);

}

std::string CameraTest::title() const
{
	return "Camera test";
}

std::string CameraTest::subtitle() const
{
	return "Use your mouse to move/zoom camera";
}
