/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.
Copyright (c) 2014      Julien Maigrot

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
#ifndef __2D_CCCAMERA_H__
#define __2D_CCCAMERA_H__

#include "CCGL.h"
#include "2d/CCNode.h"
// Include to get projection type.
// Not sure if director should manage projection or if all that part should be moved to an other context.
#include "base/CCDirector.h"

NS_CC_BEGIN

/**
* Camera class. Use to control the view.
* Only test and use for 2d.
*/
class CC_DLL Camera : public cocos2d::Node
{
public:
	/**
	* Create camera function
	*/
	CREATE_FUNC(Camera);

	/**
	* Destructor
	*/
	virtual ~Camera();

	/**
	* init camera
	*/
	virtual bool init();

	/**
	* Set field of view
	* @param width Width of view
	* @param height Height of view
	*/
	inline void setFOV(int width, int height){ _fov.set(width, height); }

	/**
	* Set near and far range
	* @param nearRange Near range of the camera
	* @param farRange Far range of the camera
	*/
	inline void setRange(int nearRange, int farRange){ _range.set(nearRange, farRange); }

	/**
	* Get zoom value.
	* Use scale as zoom. Assume it won't be changed directly by other method.
	* @return the zoom value
	*/
	inline float getZoom() const { return _scaleX; }

	/**
	* Set zoom value.
	* Zoom will modify the projection matrix by changing the fov.
	* @param value The zoom value
	*/
	inline void setZoom(float value)
	{ 
		float zoom = clampf(value, _zoomLimit.x, _zoomLimit.y); 
		setScale(zoom, zoom); 
	}

	/**
	* Add zoom value to current zoom.
	* Zoom will modify the projection matrix by changing the fov.
	* @param value The zoom value
	*/
	inline void addZoom(float value)
	{ 
		float zoom = clampf(_scaleX + value, _zoomLimit.x, _zoomLimit.y);
		setScale(zoom, zoom); 
	}

	/**
	* Set zoom boundaries
	* As we use the scale, we should reverse the value
	* @param min Min value of zoom (farthest)
	* @param max Max value of zoom (nearest)
	*/
	inline void setZoomLimit(float min, float max) { _zoomLimit.set(1.f / max, 1.f / min); }

	/**
	* Compute the current camera projection matrix.
	* @param projMatrix get the projection matrix computed
	*/
	virtual void getProjectionMatrix(Mat4& projMatrix);

private:
	/**
	* Default constructor
	* Use "create" to create a camera.
	*/
	Camera();

	/**
	* Camera projection 2d or 3d (ortho or persp)
	* Only 2d so far
	*/
	Director::Projection		_projectionType;

	/**
	* Field of view
	*/
	Vec2			_fov;

	/**
	* Near and far range
	*/
	Vec2			_range;

	/**
	* Zoom boundaries
	*/
	Vec2			_zoomLimit;
};

NS_CC_END

#endif //__2D_CCCAMERA_H__