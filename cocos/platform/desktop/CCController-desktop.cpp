//
//  CCController-desktop.cpp
//  cocos2d_libs
//
//  Created by Chad Ata on 2/10/15.
//
//


#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#include "CCController-desktop.h"
#include "glfw3.h"
#include "cocos2d.h"


NS_CC_BEGIN

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
        Controller* controller = Controller::getControllerByTag(id);
        if( controller == NULL )
        {
            // It's a new controller being connected.
            controller = new cocos2d::Controller();
            controller->_deviceId = id;
            controller->_deviceName = name;
            controller->setTag(id);
            Controller::s_allController.push_back(controller);
            controller->onConnected();
        }
        
        const unsigned char* values = glfwGetJoystickButtons(id, &count);
        for( int i = 0; i < count; ++i )
        {
            // TODO - controller - add more button mappings -
            // button mappings - currently based off PS3 controller
            int keyCode = i;
            switch( i )
            {
                case 0:
                    keyCode = Controller::Key::BUTTON_SELECT;
                    break;
                case 1:
                    keyCode = Controller::Key::BUTTON_LEFT_THUMBSTICK;
                    break;
                case 2:
                    keyCode = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
                    break;
                case 3:
                    keyCode = Controller::Key::BUTTON_PAUSE;
                    break;
                case 4:
                    keyCode = Controller::Key::BUTTON_DPAD_UP;
                    break;
                case 5:
                    keyCode = Controller::Key::BUTTON_DPAD_RIGHT;
                    break;
                case 6:
                    keyCode = Controller::Key::BUTTON_DPAD_DOWN;
                    break;
                case 7:
                    keyCode = Controller::Key::BUTTON_DPAD_LEFT;
                    break;
                // TODO - controller - treat these as axis instead of button
                case 8:
                    keyCode = Controller::Key::AXIS_LEFT_TRIGGER;
                    break;
                // TODO - controller - treat these as axis instead of button
                case 9:
                    keyCode = Controller::Key::AXIS_RIGHT_TRIGGER;
                    break;
                case 10:
                    keyCode = Controller::Key::BUTTON_LEFT_SHOULDER;
                    break;
                case 11:
                    keyCode = Controller::Key::BUTTON_RIGHT_SHOULDER;
                    break;
                case 12:
                    keyCode = Controller::Key::BUTTON_Y;
                    break;
                case 13:
                    keyCode = Controller::Key::BUTTON_B;
                    break;
                case 14:
                    keyCode = Controller::Key::BUTTON_A;
                    break;
                case 15:
                    keyCode = Controller::Key::BUTTON_X;
                    break;
                case 16:
                    keyCode = Controller::Key::BUTTON_START;
                    break;
            }
            controller->onButtonEvent(keyCode, values[i]?true:false, values[i], false);
        }

        // ps3: left: x,y right:x,y x (left)-1<=x<=1(right) (up)-1<=y<=1(down)
        const float* axes = glfwGetJoystickAxes(id, &count);
        // TODO - controller - need to map - 0 = leftX
        if( count >= 4 )
        {
            int axisId = 0;
            controller->onAxisEvent(Controller::Key::JOYSTICK_LEFT_X, axes[axisId], true);

            axisId = 1;
            controller->onAxisEvent(Controller::Key::JOYSTICK_LEFT_Y, axes[axisId], true);

            axisId = 2;
            controller->onAxisEvent(Controller::Key::JOYSTICK_RIGHT_X, axes[axisId], true);

            axisId = 3;
            controller->onAxisEvent(Controller::Key::JOYSTICK_RIGHT_Y, axes[axisId], true);
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