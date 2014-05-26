#include "CCCamera.h"


NS_CC_BEGIN

Camera::Camera() :
	_projectionType(Director::Projection::_2D)
{
	// Arbitrary value from Director::setProjection
	_range.set(-1024, 1024);

	// Arbitrary value
	_zoomLimit.set(0.1f, 2.f);
}
	
Camera::~Camera()
{}

bool Camera::init()
{
	return cocos2d::Node::init();
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

NS_CC_END
