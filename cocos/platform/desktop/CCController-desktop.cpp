//
//  CCController-desktop.cpp
//  cocos2d_libs
//
//  Created by Chad Ata on 2/10/15.
//
//


#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
#include "CCController-desktop.h"

#include "CCGLViewImpl-desktop.h"
#include "cocos2d.h"


NS_CC_BEGIN

void ControllerDesktop::setButtonMapping(const ButtonMapping* b)
{
	this->buttonMapping = b;
}

// TODO - controller - implement disconnect event
// TODO - controller - add destructor and shutdown operations
ControllerImpl::ControllerImpl(Controller* controller)
: _controller(controller)
{
}

/**
 * Polls glfw for controller events and dispatches the results
 */
void ControllerImpl::pollJoystick( int id )
{
    // TODO - controller - this entire function needs optimization
    int count = 0;
    bool isPresent = glfwJoystickPresent(id);

    if( isPresent )
    {
        const char* name = glfwGetJoystickName(id);
		ControllerDesktop* controller = (ControllerDesktop*)Controller::getControllerByTag(id);
		const ButtonMapping* buttonMapping = NULL;
		if (controller == NULL)
        {
            // It's a new controller being connected.
			controller = new cocos2d::ControllerDesktop();
            controller->_deviceId = id;
            controller->_deviceName = name;
            controller->setTag(id);

			// TODO - controller - handle more controller types
			// TODO - controller - handle unknown controllers
			const ButtonMapping* buttonMapping = &buttonMappingXBox360PC;
			if (strstr(name, "3"))	// looking for the "3" in PS3
				buttonMapping = &buttonMappingPS3;
			controller->setButtonMapping(buttonMapping);
			//controller->mapButton = mapButton;
            
			Controller::s_allController.push_back(controller);
            controller->onConnected();
			log("Controller connected: %s", name);
        }
		buttonMapping = controller->buttonMapping;
		
		// TODO - controller - handle unknown controllers
		const unsigned char* values = glfwGetJoystickButtons(id, &count);
        // TODO - controller - efficiently check out of bounds on index
		// trying to avoid conditional statements here for optimization reasons
		controller->onButtonEvent(Controller::Key::BUTTON_A, values[buttonMapping->BUTTON_A] ? true : false, values[buttonMapping->BUTTON_A], false);
		controller->onButtonEvent(Controller::Key::BUTTON_B, values[buttonMapping->BUTTON_B] ? true : false, values[buttonMapping->BUTTON_B], false);
		controller->onButtonEvent(Controller::Key::BUTTON_X, values[buttonMapping->BUTTON_X] ? true : false, values[buttonMapping->BUTTON_X], false);
		controller->onButtonEvent(Controller::Key::BUTTON_Y, values[buttonMapping->BUTTON_Y] ? true : false, values[buttonMapping->BUTTON_Y], false);
		controller->onButtonEvent(Controller::Key::BUTTON_DPAD_UP, values[buttonMapping->BUTTON_DPAD_UP] ? true : false, values[buttonMapping->BUTTON_DPAD_UP], false);
		controller->onButtonEvent(Controller::Key::BUTTON_DPAD_DOWN, values[buttonMapping->BUTTON_DPAD_DOWN] ? true : false, values[buttonMapping->BUTTON_DPAD_DOWN], false);
		controller->onButtonEvent(Controller::Key::BUTTON_DPAD_LEFT, values[buttonMapping->BUTTON_DPAD_LEFT] ? true : false, values[buttonMapping->BUTTON_DPAD_LEFT], false);
		controller->onButtonEvent(Controller::Key::BUTTON_DPAD_RIGHT, values[buttonMapping->BUTTON_DPAD_RIGHT] ? true : false, values[buttonMapping->BUTTON_DPAD_RIGHT], false);
		controller->onButtonEvent(Controller::Key::BUTTON_LEFT_SHOULDER, values[buttonMapping->BUTTON_LEFT_SHOULDER] ? true : false, values[buttonMapping->BUTTON_LEFT_SHOULDER], false);
		controller->onButtonEvent(Controller::Key::BUTTON_RIGHT_SHOULDER, values[buttonMapping->BUTTON_RIGHT_SHOULDER] ? true : false, values[buttonMapping->BUTTON_RIGHT_SHOULDER], false);
		controller->onButtonEvent(Controller::Key::BUTTON_LEFT_THUMBSTICK, values[buttonMapping->BUTTON_LEFT_THUMBSTICK] ? true : false, values[buttonMapping->BUTTON_LEFT_THUMBSTICK], false);
		controller->onButtonEvent(Controller::Key::BUTTON_RIGHT_THUMBSTICK, values[buttonMapping->BUTTON_RIGHT_THUMBSTICK] ? true : false, values[buttonMapping->BUTTON_RIGHT_THUMBSTICK], false);
		controller->onButtonEvent(Controller::Key::BUTTON_START, values[buttonMapping->BUTTON_START] ? true : false, values[buttonMapping->BUTTON_START], false);
		controller->onButtonEvent(Controller::Key::BUTTON_SELECT, values[buttonMapping->BUTTON_SELECT] ? true : false, values[buttonMapping->BUTTON_SELECT], false);
		controller->onButtonEvent(Controller::Key::BUTTON_PAUSE, values[buttonMapping->BUTTON_PAUSE] ? true : false, values[buttonMapping->BUTTON_PAUSE], false);

        // left: x,y right:x,y x (left)-1<=x<=1(right) (up)-1<=y<=1(down)
		// TODO - controller - handle unknown controllers
        // TODO - controller - efficiently check out of bounds on index
		const float* axes = glfwGetJoystickAxes(id, &count);
		controller->onAxisEvent(Controller::Key::JOYSTICK_LEFT_X, axes[buttonMapping->JOYSTICK_LEFT_X], true);
		controller->onAxisEvent(Controller::Key::JOYSTICK_LEFT_Y, axes[buttonMapping->JOYSTICK_LEFT_Y], true);
		controller->onAxisEvent(Controller::Key::JOYSTICK_RIGHT_X, axes[buttonMapping->JOYSTICK_RIGHT_X], true);
		controller->onAxisEvent(Controller::Key::JOYSTICK_RIGHT_Y, axes[buttonMapping->JOYSTICK_RIGHT_Y], true);
        
		// TODO - controller - find a better way to handle analog vs digital discrepancies across different controllers
        if( buttonMapping->isTriggerAnalog )
        {
            controller->onButtonEvent(Controller::Key::AXIS_LEFT_TRIGGER, axes[buttonMapping->AXIS_LEFT_TRIGGER] > 0.5 ? true : false, axes[buttonMapping->AXIS_LEFT_TRIGGER], false);
            controller->onButtonEvent(Controller::Key::AXIS_RIGHT_TRIGGER, axes[buttonMapping->AXIS_RIGHT_TRIGGER] < -0.5 ? true : false, axes[buttonMapping->AXIS_RIGHT_TRIGGER], false);
        }
        else
        {
            controller->onButtonEvent(Controller::Key::AXIS_LEFT_TRIGGER, values[buttonMapping->AXIS_LEFT_TRIGGER] ? true : false, values[buttonMapping->AXIS_LEFT_TRIGGER], false);
            controller->onButtonEvent(Controller::Key::AXIS_RIGHT_TRIGGER, values[buttonMapping->AXIS_RIGHT_TRIGGER] ? true : false, values[buttonMapping->AXIS_RIGHT_TRIGGER], false);
        }
	}
}


Controller::Controller()
: _controllerTag(TAG_UNSET)
, _impl(new ControllerImpl(this))
, _connectEvent(nullptr)
, _keyEvent(nullptr)
, _axisEvent(nullptr)
{
    init();
}

Controller::~Controller()
{
        // TODO - controller
}

void Controller::startDiscoveryController()
{
    
}

NS_CC_END

#endif // #if (CC_TARGET_PLATFORM == ...)