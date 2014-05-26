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
#ifndef __2D_CCCAMERA_VIEW_H__
#define __2D_CCCAMERA_VIEW_H__

#include "CCGL.h"
#include "2d/CCNode.h"
#include "2d/CCCamera.h"
#include "renderer/CCCustomCommand.h"

NS_CC_BEGIN

/**
* Camera view node define the view for it's children node.
* It takes a camera and push its projection matrix when visiting, prior to parse it's children.
* It allows the possibility to have multiple camera with different projection in a scene.
* i.e. A camera for the scene and a camera for the ui.
*/
class CC_DLL CameraView : public cocos2d::Node
{
public:
	/**
	* Create camera view function
	*/
	CREATE_FUNC(CameraView);

	/**
	* Destructor
	*/
	virtual ~CameraView();

	/**
	* Apply camera projection for rendering,
	* Then visit children.
	*/
	virtual void visit(Renderer *renderer, const Mat4& parentTransform, bool parentTransformUpdated);

	/**
	* Needed for compilation
	* Use parameterless visit function from Node.
	*/
	using Node::visit;

	/**
	* Set camera for rendering
	* @param camera Camera to set
	*/
	inline void setCamera(Camera* camera) { _camera = camera; }

	/**
	* Get current camera
	* @return the camera, nullptr if not assigned
	*/
	inline Camera* getCamera() const { return _camera; }

private:
	/**
	* Default constructor
	*/
	CameraView();

	/**
	* Camera to get the projection from
	* Extent: could be a list of camera when you have to draw different view of the same scene (split screen)
	*/
	Camera*		_camera;

	/**
	* Apply projection of camera
	*/
	cocos2d::CustomCommand _pushProj;

	/**
	* Remove projection of camera
	*/
	cocos2d::CustomCommand _popProj;
};

NS_CC_END

#endif //__2D_CCCAMERA_VIEW_H__