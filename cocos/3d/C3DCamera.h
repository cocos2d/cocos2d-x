#ifndef CAMERA_H_
#define CAMERA_H_

#include "Transform.h"
#include "C3DNode.h"

#include "C3DAABB.h"
#include "C3DOBB.h"

namespace cocos2d
{
class C3DCameraNode;
class C3DViewport;
class Vector3;
class Vector2;
class C3DRay;

/**
* Defines a camera which acts as a view of a scene to be rendered.
*/
class  C3DCamera : public C3DNode, public C3DNode::Listener
{
	friend class C3DCameraNode;

public:

	/**
	* get type. inherit from C3DNode
	*/
	C3DNode::Type getType() const { return C3DNode::NodeType_Camera; }

	/**
	* The type of camera.
	*/
	enum Type
	{
		PERSPECTIVE = 1,
		ORTHOGRAPHIC = 2
	};

	/**
	* Creates a perspective camera.
	*
	* @param fieldOfView The field of view for the perspective camera (normally in the range of 40-60 degrees).
	* @param aspectRatio The aspect ratio of the camera (normally the width of the viewport divided by the height of the viewport).
	* @param nearPlane The near plane distance.
	* @param farPlane The far plane distance.
	* @param strId camera id
	*/
	static C3DCamera* createPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane, const char* strId = "perspective camera");

	/**
	* set perspective camera parameter
	*/
	void setPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);

	/**
	* Creates an orthographic camera.
	*
	* @param zoomX The zoom factor along the X-axis of the orthographic projection (the width of the ortho projection).
	* @param zoomY The zoom factor along the Y-axis of the orthographic projection (the height of the ortho projection).
	* @param aspectRatio The aspect ratio of the orthographic projection.
	* @param nearPlane The near plane distance.
	* @param farPlane The far plane distance.
	* @param strId Camera id
	*/
	static C3DCamera* createOrthographic(float zoomX, float zoomY, float aspectRatio, float nearPlane, float farPlane, const char* strId = "orthographic camera");

	/**
	* set Orthographic camera parameter
	*/
	void setOrthographic(float zoomX, float zoomY, float aspectRatio, float nearPlane, float farPlane);

	/**
	* create camera
	*/
	static C3DCamera* create(const char* id);

	/**
	* Gets the type of camera.
	*
	* @return The camera type.
	*/
	C3DCamera::Type getCameraType() const;

	/**
	* Gets the field of view for a perspective camera.
	*
	* @return The field of view.
	*/
	float getFieldOfView() const;

	/**
	* Sets the field of view.
	*
	* @param fieldOfView The field of view.
	*/
	void setFieldOfView(float fieldOfView);

	/**
	* Gets the x-zoom (magnification) for an orthographic camera.
	* Default is 1.0f.
	*
	* @return The magnification (zoom) for x.
	*/
	float getZoomX() const;

	/**
	* Sets the x-zoom (magnification) for a orthographic camera.
	* Default is 1.0f.
	*
	* @param zoomX The magnification (zoom) for x.
	*/
	void setZoomX(float zoomX);

	/**
	* Gets the y-zoom (magnification) for a orthographic camera.
	* Default is 1.0f.
	*
	* @return The magnification (zoom) for y.
	*/
	float getZoomY() const;

	/**
	* Sets the y-zoom (magnification) for a orthographic camera.
	*
	* @param zoomY The magnification (zoom) for y.
	*/
	void setZoomY(float zoomY);

	/**
	* Gets the aspect ratio.
	*
	* @return The aspect ratio.
	*/
	float getAspectRatio() const;

	/**
	* Sets the aspect ratio.
	*
	* @param aspectRatio The aspect ratio.
	*/
	void setAspectRatio(float aspectRatio);

	/**
	* Gets the near z clipping plane distance.
	*
	* @return The near z clipping plane distance.
	*/
	float getNearPlane() const;

	/**
	* Sets the near z clipping plane distance.
	*
	* @param nearPlane The near z clipping plane distance.
	*/
	void setNearPlane(float nearPlane);

	/**
	* Gets the far z clipping plane distance.
	*
	* @return The far z clipping plane distance.
	*/
	float getFarPlane() const;

	/**
	* Sets the far z clipping plane distance.
	*
	* @param farPlane The far z clipping plane distance.
	*/
	void setFarPlane(float farPlane);

	/**
	* Gets the camera's view matrix.
	*
	* @return The camera view matrix.
	*/
	const Matrix& getViewMatrix();

	/**
	* Gets the camera's inverse view matrix.
	*
	* @return The camera inverse view matrix.
	*/
	const Matrix& getInverseViewMatrix();

	/**
	* Gets the camera's projection matrix.
	*
	* @return The camera projection matrix.
	*/
	const Matrix& getProjectionMatrix() const;

	/**
	* Gets the camera's view * projection matrix.
	*
	* @return The camera view * projection matrix.
	*/
	const Matrix& getViewProjectionMatrix();

	/**
	* Gets the camera's inverse view * projection matrix.
	*
	* @return The camera inverse view * projection matrix.
	*/
	const Matrix& getInverseViewProjectionMatrix();

	/**
	* Projects the specified world position into the viewport coordinates.
	*
	*/
	void project(const C3DViewport* viewport, Vector3* src, Vector2* dst);

	/**
	* Converts a viewport-space coordinate to a world-space position for the given depth value.
	*/
	void unproject(const C3DViewport* viewport, Vector3* src, Vector3* dst);

	/**
	* Ray from camera to the screen position
	*/
	void getAxes(const C3DViewport* viewport, float x, float y, C3DRay* dst);

	/**
	* translate camera
	*/
	void translateX(float tx);
	void translateY(float ty);
	void translateZ(float tz);

	/**
	* set camera position
	*/
	void setPosition(float tx, float ty, float tz);

	/**
	* rotate camera
	*/
	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);

private:
	/**
	* Constructor & Destructor
	*/
	C3DCamera(const char* id);
	C3DCamera(float fieldOfView, float aspectRatio, float nearPlane, float farPlane, const char* strId);
	C3DCamera(float zoomX, float zoomY, float aspectRatio, float nearPlane, float farPlane, const char* strId);
	virtual ~C3DCamera();

	/**
	* @see Transform::Listener::transformChanged
	*/
	void transformChanged(Transform* transform);

	// camera properties
	C3DCamera::Type _type;

	float		_fieldOfView;
	float		_zoom[2];
	float		_aspectRatio;
	float		_nearPlane;
	float		_farPlane;

	mutable Matrix _view;
	mutable Matrix _projection;
	mutable Matrix _viewProjection;
	mutable Matrix _inverseView;
	mutable Matrix _inverseViewProjection;

	mutable int _dirtyBits;

	Vector3		_target;	// camera look focus

	bool		_bDrawCamera;
};
}

#endif
