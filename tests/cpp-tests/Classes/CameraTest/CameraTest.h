#ifndef _CAMERA_TEST_H_
#define _CAMERA_TEST_H_

#include "cocos2d.h"
#include "../testBasic.h"
#include "../BaseTest.h"

/**
* Scene to test Camera.
* Create CameraTest Layer.
*/
class CameraTestScene : public TestScene
{
public:
	/**
	* Default constructor
	*/
	CameraTestScene();

	/**
	* Destructor
	*/
	virtual ~CameraTestScene();

	/**
	* Start the test
	*/
	virtual void runThisTest();
};

/**
* Camera test layer.
* Where the action happened!
*/
class CameraTest : public BaseTest
{
public:
	/**
	* Default constructor
	*/
	CameraTest();

	/**
	* Destructor
	*/
	virtual ~CameraTest();

	/**
	* Create function
	*/
	CREATE_FUNC(CameraTest);

	/**
	* Get test title
	* @return test title
	*/
	virtual std::string title() const override;

	/**
	* Get test subtitle
	* @return test subtitle
	*/
	virtual std::string subtitle() const override;

	/**
	* Event when a mouse button is down
	* @param evt Mouse event description
	*/
	void onMouseDown(Event* evt);

	/**
	* Event when a mouse button is up
	* @param evt Mouse event description
	*/
	void onMouseUp(Event* evt);

	/**
	* Event when the mouse move
	* @param evt Mouse event description
	*/
	void onMouseMove(Event* evt);

	/**
	* Event when mouse is scrolling
	* @param evt Mouse event description
	*/
	void onMouseScroll(Event* evt);

	/**
	* Return test camera
	*/
	inline Camera* getCamera() const {	return _camera; }

private:
	/**
	* Camera use for our test
	*/
	Camera*				_camera;

	/**
	* Mouse listener use to catch mouse event and move the camera
	*/
	EventListenerMouse* _mouseListener;

	/**
	* True when mouse button  is down, false otherwise
	* If true, you can move the camera around
	*/
	bool				_moving;

	/**
	* Last x position of cursor, use to compute the translation of camera
	*/
	int					_xCursor;

	/**
	* Last y position of cursor, use to compute the translation of camera
	*/
	int					_yCursor;
};

#endif //_CAMERA_TEST_H_