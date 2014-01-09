#include "Base.h"
#include "C3DCamera.h"
#include "C3DNode.h"
#include "C3DViewport.h"
#include "Vector2.h"
#include "Vector3.h"
#include "C3DRay.h"
#include "C3DScene.h"

#include "C3DRenderSystem.h"

// C3DCamera dirty bits
#define CAMERA_DIRTY_VIEW 1
#define CAMERA_DIRTY_PROJ 2
#define CAMERA_DIRTY_VIEW_PROJ 4
#define CAMERA_DIRTY_INV_VIEW 8
#define CAMERA_DIRTY_INV_VIEW_PROJ 16
#define CAMERA_DIRTY_BOUNDS 32
#define CAMERA_DIRTY_ALL (CAMERA_DIRTY_VIEW | CAMERA_DIRTY_PROJ | CAMERA_DIRTY_VIEW_PROJ | CAMERA_DIRTY_INV_VIEW | CAMERA_DIRTY_INV_VIEW_PROJ | CAMERA_DIRTY_BOUNDS)

namespace cocos2d
{
C3DCamera::C3DCamera(const char* id)
	:C3DNode(id),  _type(PERSPECTIVE), _fieldOfView(45.0f), _aspectRatio(0.75), _nearPlane(10.0f), _farPlane(1000.0f),
	 _dirtyBits(CAMERA_DIRTY_ALL), _target(Vector3(0, 0, 0)), _bDrawCamera(false)
{
	this->addListener(this);
}

C3DCamera::C3DCamera(float fieldOfView, float aspectRatio, float nearPlane, float farPlane, const char* strId)
	:C3DNode(strId),  _type(PERSPECTIVE), _fieldOfView(fieldOfView), _aspectRatio(aspectRatio), _nearPlane(nearPlane), _farPlane(farPlane),
	 _dirtyBits(CAMERA_DIRTY_ALL), _target(Vector3(0, 0, 0)), _bDrawCamera(false)
{
	this->addListener(this);
}

C3DCamera::C3DCamera(float zoomX, float zoomY, float aspectRatio, float nearPlane, float farPlane, const char* strId)
	:C3DNode(strId),  _type(ORTHOGRAPHIC), _aspectRatio(aspectRatio), _nearPlane(nearPlane), _farPlane(farPlane),
	 _dirtyBits(CAMERA_DIRTY_ALL), _target(Vector3(0, 0, 0)), _bDrawCamera(false)
{
	// Orthographic camera.
	_zoom[0] = zoomX;
	_zoom[1] = zoomY;
	this->addListener(this);
}

C3DCamera* C3DCamera::create(const char* id)
{
	C3DCamera* camera = new C3DCamera(id);
	camera->autorelease();
	return camera;
}

C3DCamera::~C3DCamera()
{
	this->removeListener(this);
}

void C3DCamera::setPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{
	_fieldOfView = fieldOfView;
	_aspectRatio = aspectRatio;
	_nearPlane = nearPlane;
	_farPlane = farPlane;
}

C3DCamera* C3DCamera::createPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane, const char* strId)
{
	C3DCamera* camera = new C3DCamera(fieldOfView, aspectRatio, nearPlane, farPlane, strId);
	camera->autorelease();
	return camera;
}

C3DCamera* C3DCamera::createOrthographic(float zoomX, float zoomY, float aspectRatio, float nearPlane, float farPlane, const char* strId)
{
	C3DCamera* camera = new C3DCamera(zoomX, zoomY, aspectRatio, nearPlane, farPlane, strId);
	camera->autorelease();
	return camera;
}

void C3DCamera::setOrthographic(float zoomX, float zoomY, float aspectRatio, float nearPlane, float farPlane)
{
	_zoom[0] = zoomX;
	_zoom[1] = zoomY;
	_aspectRatio = aspectRatio;
	_nearPlane = nearPlane;
	_farPlane = farPlane;
}

C3DCamera::Type C3DCamera::getCameraType() const
{
	return _type;
}

float C3DCamera::getFieldOfView() const
{
	assert(_type == C3DCamera::PERSPECTIVE);

	return _fieldOfView;
}

void C3DCamera::setFieldOfView(float fieldOfView)
{
	assert(_type == C3DCamera::PERSPECTIVE);

	_fieldOfView = fieldOfView;
	_dirtyBits |= CAMERA_DIRTY_PROJ | CAMERA_DIRTY_VIEW_PROJ | CAMERA_DIRTY_INV_VIEW_PROJ | CAMERA_DIRTY_BOUNDS;
}

float C3DCamera::getZoomX() const
{
	assert(_type == C3DCamera::ORTHOGRAPHIC);

	return _zoom[0];
}

void C3DCamera::setZoomX(float zoomX)
{
	assert(_type == C3DCamera::ORTHOGRAPHIC);

	_zoom[0] = zoomX;
	_dirtyBits |= CAMERA_DIRTY_PROJ | CAMERA_DIRTY_VIEW_PROJ | CAMERA_DIRTY_INV_VIEW_PROJ | CAMERA_DIRTY_BOUNDS;
}

float C3DCamera::getZoomY() const
{
	assert(_type == C3DCamera::ORTHOGRAPHIC);

	return _zoom[1];
}

void C3DCamera::setZoomY(float zoomY)
{
	assert(_type == C3DCamera::ORTHOGRAPHIC);

	_zoom[1] = zoomY;
	_dirtyBits |= CAMERA_DIRTY_PROJ | CAMERA_DIRTY_VIEW_PROJ | CAMERA_DIRTY_INV_VIEW_PROJ | CAMERA_DIRTY_BOUNDS;
}

float C3DCamera::getAspectRatio() const
{
	return _aspectRatio;
}

void C3DCamera::setAspectRatio(float aspectRatio)
{
	_aspectRatio = aspectRatio;
	_dirtyBits |= CAMERA_DIRTY_PROJ | CAMERA_DIRTY_VIEW_PROJ | CAMERA_DIRTY_INV_VIEW_PROJ | CAMERA_DIRTY_BOUNDS;
}

float C3DCamera::getNearPlane() const
{
	return _nearPlane;
}

void C3DCamera::setNearPlane(float nearPlane)
{
	_nearPlane = nearPlane;
	_dirtyBits |= CAMERA_DIRTY_PROJ | CAMERA_DIRTY_VIEW_PROJ | CAMERA_DIRTY_INV_VIEW_PROJ | CAMERA_DIRTY_BOUNDS;
}

float C3DCamera::getFarPlane() const
{
	return _farPlane;
}

void C3DCamera::setFarPlane(float farPlane)
{
	_farPlane = farPlane;
	_dirtyBits |= CAMERA_DIRTY_PROJ | CAMERA_DIRTY_VIEW_PROJ | CAMERA_DIRTY_INV_VIEW_PROJ | CAMERA_DIRTY_BOUNDS;
}

const Matrix& C3DCamera::getViewMatrix()
{
	if (_dirtyBits & CAMERA_DIRTY_VIEW)
	{
		getWorldMatrix().invert(&_view);
		_dirtyBits &= ~CAMERA_DIRTY_VIEW;
	}

	return _view;
}

const Matrix& C3DCamera::getInverseViewMatrix()
{
	if (_dirtyBits & CAMERA_DIRTY_INV_VIEW)
	{
		getViewMatrix().invert(&_inverseView);

		_dirtyBits &= ~CAMERA_DIRTY_INV_VIEW;
	}

	return _inverseView;
}

const Matrix& C3DCamera::getProjectionMatrix() const
{
	if (_dirtyBits & CAMERA_DIRTY_PROJ)
	{
		if (_type == PERSPECTIVE)
		{
			Matrix::createPerspective(_fieldOfView, _aspectRatio, _nearPlane, _farPlane, &_projection);
		}
		else
		{
			Matrix::createOrthographic(_zoom[0], _zoom[1], _nearPlane, _farPlane, &_projection);
		}

		_dirtyBits &= ~CAMERA_DIRTY_PROJ;
	}

	return _projection;
}

const Matrix& C3DCamera::getViewProjectionMatrix()
{
	if (_dirtyBits & CAMERA_DIRTY_VIEW_PROJ)
	{
		Matrix::multiply(getProjectionMatrix(), getViewMatrix(), &_viewProjection);

		_dirtyBits &= ~CAMERA_DIRTY_VIEW_PROJ;
	}

	return _viewProjection;
}

const Matrix& C3DCamera::getInverseViewProjectionMatrix()
{
	if (_dirtyBits & CAMERA_DIRTY_INV_VIEW_PROJ)
	{
		getViewProjectionMatrix().invert(&_inverseViewProjection);

		_dirtyBits &= ~CAMERA_DIRTY_INV_VIEW_PROJ;
	}

	return _inverseViewProjection;
}

void C3DCamera::transformChanged(Transform* transform)
{
	_dirtyBits |= CAMERA_DIRTY_VIEW | CAMERA_DIRTY_INV_VIEW | CAMERA_DIRTY_INV_VIEW_PROJ | CAMERA_DIRTY_VIEW_PROJ | CAMERA_DIRTY_BOUNDS;
}

void C3DCamera::project(const C3DViewport* viewport, Vector3* src, Vector2* dst)
{
	assert(src);
	assert(dst);

	// Transform the point to clip-space.
	Vector4 clipPos;
	getViewProjectionMatrix().transformVector(Vector4(src->x, src->y, src->z, 1.0f), &clipPos);

	// Compute normalized device coordinates.
	assert(clipPos.w != 0.0f);
	float ndcX = clipPos.x / clipPos.w;
	float ndcY = clipPos.y / clipPos.w;

	// Compute screen coordinates by applying our viewport transformation.
	dst->x = viewport->x + (ndcX + 1.0f) * 0.5f * viewport->width;
	dst->y = viewport->y + (1.0f - (ndcY + 1.0f) * 0.5f) * viewport->height;
}

void C3DCamera::unproject(const C3DViewport* viewport, Vector3* src, Vector3* dst)
{
	assert(dst);

	// Create our screen space position in NDC.
	assert(viewport->width != 0.0f && viewport->height != 0.0f);
	Vector4 screen((src->x - viewport->x) / viewport->width, ((viewport->height - src->y) - viewport->y) / viewport->height, src->z, 1.0f);

	// Map to range -1 to 1.
	screen.x = screen.x * 2.0f - 1.0f;
	screen.y = screen.y * 2.0f - 1.0f;
	screen.z = screen.z * 2.0f - 1.0f;

	// Transform the screen-space NDC by our inverse view projection matrix.
	getInverseViewProjectionMatrix().transformVector(screen, &screen);

	// Divide by our W coordinate.
	if (screen.w != 0.0f)
	{
		screen.x /= screen.w;
		screen.y /= screen.w;
		screen.z /= screen.w;
	}

	dst->set(screen.x, screen.y, screen.z);
}

void C3DCamera::getAxes(const C3DViewport* viewport, float x, float y, C3DRay* dst)
{
	// Get the world-space position at the near clip plane.
	Vector3 nearPoint;
	Vector3 src = Vector3 (x,y,0.0f);
	unproject(viewport, &src, &nearPoint);

	// Get the world-space position at the far clip plane.
	Vector3 farPoint;
	src = Vector3 (x,y,1.0f);
	unproject(viewport, &src, &farPoint);

	// Set the direction of the ray.
	Vector3 direction;
	Vector3::subtract(farPoint, nearPoint, &direction);
	direction.normalize();

	dst->set(nearPoint, direction);
}

void C3DCamera::translateX(float tx)
{
	C3DNode::translateX(tx);
	_dirtyBits |= CAMERA_DIRTY_VIEW | CAMERA_DIRTY_INV_VIEW | CAMERA_DIRTY_INV_VIEW_PROJ | CAMERA_DIRTY_VIEW_PROJ | CAMERA_DIRTY_BOUNDS;
}

void C3DCamera::translateY(float ty)
{
	C3DNode::translateY(ty);
	_dirtyBits |= CAMERA_DIRTY_VIEW | CAMERA_DIRTY_INV_VIEW | CAMERA_DIRTY_INV_VIEW_PROJ | CAMERA_DIRTY_VIEW_PROJ | CAMERA_DIRTY_BOUNDS;
}

void C3DCamera::translateZ(float tz)
{
	C3DNode::translateZ(tz);
	_dirtyBits |= CAMERA_DIRTY_VIEW | CAMERA_DIRTY_INV_VIEW | CAMERA_DIRTY_INV_VIEW_PROJ | CAMERA_DIRTY_VIEW_PROJ | CAMERA_DIRTY_BOUNDS;
}

void C3DCamera::setPosition(float tx, float ty, float tz)
{
	C3DNode::setPosition(tx, ty, tz);
	_dirtyBits |= CAMERA_DIRTY_VIEW | CAMERA_DIRTY_INV_VIEW | CAMERA_DIRTY_INV_VIEW_PROJ | CAMERA_DIRTY_VIEW_PROJ | CAMERA_DIRTY_BOUNDS;
}

void C3DCamera::rotateX(float angle)
{
	C3DNode::rotateX(angle);
	_dirtyBits |= CAMERA_DIRTY_VIEW | CAMERA_DIRTY_INV_VIEW | CAMERA_DIRTY_INV_VIEW_PROJ | CAMERA_DIRTY_VIEW_PROJ | CAMERA_DIRTY_BOUNDS;
}

void C3DCamera::rotateY(float angle)
{
	C3DNode::rotateY(angle);
	_dirtyBits |= CAMERA_DIRTY_VIEW | CAMERA_DIRTY_INV_VIEW | CAMERA_DIRTY_INV_VIEW_PROJ | CAMERA_DIRTY_VIEW_PROJ | CAMERA_DIRTY_BOUNDS;
}

void C3DCamera::rotateZ(float angle)
{
	C3DNode::rotateZ(angle);
	_dirtyBits |= CAMERA_DIRTY_VIEW | CAMERA_DIRTY_INV_VIEW | CAMERA_DIRTY_INV_VIEW_PROJ | CAMERA_DIRTY_VIEW_PROJ | CAMERA_DIRTY_BOUNDS;
}
}
