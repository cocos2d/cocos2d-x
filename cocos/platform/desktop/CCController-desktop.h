//
//  CCController-desktop.h
//  cocos2d_libs
//
//  Created by Chad Ata on 2/10/15.
//
//

#ifndef cocos2d_libs_CCController_desktop_h
#define cocos2d_libs_CCController_desktop_h
#include "base/CCController.h"
#include <functional>

NS_CC_BEGIN

struct ButtonMapping
{
	int	JOYSTICK_LEFT_X;
	int	JOYSTICK_LEFT_Y;
	int	JOYSTICK_RIGHT_X;
	int JOYSTICK_RIGHT_Y;

	int	BUTTON_A;
	int BUTTON_B;
	int BUTTON_C;
	int BUTTON_X;
	int BUTTON_Y;
	int BUTTON_Z;

	int BUTTON_DPAD_UP;
	int BUTTON_DPAD_DOWN;
	int BUTTON_DPAD_LEFT;
	int BUTTON_DPAD_RIGHT;
	int BUTTON_DPAD_CENTER;

	int BUTTON_LEFT_SHOULDER;
	int BUTTON_RIGHT_SHOULDER;

	int AXIS_LEFT_TRIGGER;
	int AXIS_RIGHT_TRIGGER;

	int BUTTON_LEFT_THUMBSTICK;
	int BUTTON_RIGHT_THUMBSTICK;

	int BUTTON_START;
	int BUTTON_SELECT;

	int BUTTON_PAUSE;
	int KEY_MAX;
    bool isTriggerAnalog;
};

static const int BUTTON_MAPPING_INDEX_UNSPECIFIED = 0;

static const ButtonMapping buttonMappingPS3{
	0, /*JOYSTICK_LEFT_X,*/
	1, /*JOYSTICK_LEFT_Y,*/
	2, /*JOYSTICK_RIGHT_X,*/
	3, /*JOYSTICK_RIGHT_Y,*/

	14, /*BUTTON_A,*/
	13, /*BUTTON_B,*/
	BUTTON_MAPPING_INDEX_UNSPECIFIED, /*BUTTON_C,*/
	15, /*BUTTON_X,*/
	12, /*BUTTON_Y,*/
	BUTTON_MAPPING_INDEX_UNSPECIFIED, /*BUTTON_Z,*/

	4, /*BUTTON_DPAD_UP,*/
	6, /*BUTTON_DPAD_DOWN,*/
	7, /*BUTTON_DPAD_LEFT,*/
	5, /*BUTTON_DPAD_RIGHT,*/
	BUTTON_MAPPING_INDEX_UNSPECIFIED, /*BUTTON_DPAD_CENTER,*/

	10, /*BUTTON_LEFT_SHOULDER,*/
	11, /*BUTTON_RIGHT_SHOULDER,*/

	8, /*AXIS_LEFT_TRIGGER,*/
	9, /*AXIS_RIGHT_TRIGGER,*/

	1, /*BUTTON_LEFT_THUMBSTICK,*/
	2, /*BUTTON_RIGHT_THUMBSTICK,*/

	16, /*BUTTON_START,*/
	0, /*BUTTON_SELECT,*/

	3, /*BUTTON_PAUSE,*/
	BUTTON_MAPPING_INDEX_UNSPECIFIED, /*KEY_MAX*/
    false /*isTriggerAnalog*/
};

static const ButtonMapping buttonMappingXBox360PC{
	0, /*JOYSTICK_LEFT_X,*/
	1, /*JOYSTICK_LEFT_Y,*/
	4, /*JOYSTICK_RIGHT_X,*/
	3, /*JOYSTICK_RIGHT_Y,*/

	0, /*BUTTON_A,*/
	1, /*BUTTON_B,*/
	BUTTON_MAPPING_INDEX_UNSPECIFIED, /*BUTTON_C,*/
	2, /*BUTTON_X,*/
	3, /*BUTTON_Y,*/
	BUTTON_MAPPING_INDEX_UNSPECIFIED, /*BUTTON_Z,*/

	10, /*BUTTON_DPAD_UP,*/
	12, /*BUTTON_DPAD_DOWN,*/
	13, /*BUTTON_DPAD_LEFT,*/
	11, /*BUTTON_DPAD_RIGHT,*/
	BUTTON_MAPPING_INDEX_UNSPECIFIED, /*BUTTON_DPAD_CENTER,*/

	4, /*BUTTON_LEFT_SHOULDER,*/
	5, /*BUTTON_RIGHT_SHOULDER,*/

	2, /*AXIS_LEFT_TRIGGER,*/
	2, /*AXIS_RIGHT_TRIGGER,*/

	8, /*BUTTON_LEFT_THUMBSTICK,*/
	9, /*BUTTON_RIGHT_THUMBSTICK,*/

	7, /*BUTTON_START,*/
	6, /*BUTTON_SELECT,*/

	7, /*BUTTON_PAUSE,*/
	BUTTON_MAPPING_INDEX_UNSPECIFIED, /*KEY_MAX*/
    true /*isTriggerAnalog*/
};

class CC_DLL ControllerDesktop : public Controller
{
private:
	const ButtonMapping* buttonMapping = NULL;
public:
	void setButtonMapping(const ButtonMapping* b);
	
	friend class ControllerImpl;
};

/**
 * Controller implementation for desktop controller support
 */
class ControllerImpl
{
public:
    ControllerImpl(Controller* controller);
    static void pollJoystick( int id );

private:
    Controller* _controller;
};

NS_CC_END
#endif
