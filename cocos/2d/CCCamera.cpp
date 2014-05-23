#include "CCCamera.h"


NS_CC_BEGIN

Camera::Camera() :
	_projectionType(Director::Projection::_2D),
	_zoom(1.f)
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
		// Get size difference between regular screen and zoomed screen
		int offsetZoomedWidth = (_fov.x - _fov.x * _zoom) / 2;
		int offsetZoomedHeight = (_fov.y - _fov.y * _zoom) / 2;

		int left = _position.x - offsetZoomedWidth;
		int right = _fov.x + _position.x + offsetZoomedWidth;

		int top = _position.y - offsetZoomedHeight;
		int bottom = _fov.y + _position.y + offsetZoomedHeight;

		projMatrix.setIdentity();
		cocos2d::Mat4::createOrthographicOffCenter(left, right, top, bottom, _range.x, _range.y, &projMatrix);

		break;
	}
}

NS_CC_END
