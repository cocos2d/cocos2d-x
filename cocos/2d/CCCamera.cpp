#include "CCCamera.h"
#include "base/CCEventListenerTouch.h"


NS_CC_BEGIN

Camera::Camera() :
	_projectionType(Director::Projection::_2D),
	_touchListener(nullptr)
{
	// Arbitrary value from Director::setProjection
	_range.set(-1024, 1024);

	// Arbitrary value
	_zoomLimit.set(0.1f, 2.f);
	setZOrder(-1000);
}
	
Camera::~Camera()
{}

bool Camera::init()
{
	if (!cocos2d::Node::init())
	{
		return false;
	}
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(Camera::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Camera::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Camera::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(Camera::onTouchCancelled, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	_touchListener = listener;

	return true;
}

void Camera::getProjectionMatrix(cocos2d::Mat4& projMatrix)
{
	switch (_projectionType)
	{
	case cocos2d::Director::Projection::_2D:
		int left = _position.x;
		int right = _position.x + (_fov.x * _scaleX);

		int top = _position.y;
		int bottom = _position.y + (_fov.y * _scaleX);

		projMatrix.setIdentity();
		cocos2d::Mat4::createOrthographicOffCenter(left, right, top, bottom, _range.x, _range.y, &projMatrix);

		break;
	}
}

bool Camera::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}

void Camera::onTouchMoved(Touch *touch, Event *unused_event)
{
	setPosition(getPosition() - touch->getDelta());
}

void Camera::onTouchEnded(Touch *touch, Event *unused_event)
{
}

void Camera::onTouchCancelled(Touch *touch, Event *unused_event)
{
}

NS_CC_END
