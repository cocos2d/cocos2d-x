/****************************************************************************
  Copyright (c) 2014 cocos2d-x.org
  Copyright (c) 2014-2016 Chukong Technologies Inc.
  Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
  Copyright (c) 2017 Wilson E. Alvarez <wilson.e.alvarez1@gmail.com>

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

#include "base/CCController.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#include <functional>
#include "base/ccMacros.h"
#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "base/CCEventController.h"
#include "glfw3.h"

NS_CC_BEGIN

class CC_DLL ControllerImpl
{
	public:

		ControllerImpl()
		{
		}


		~ControllerImpl()
		{
			// If there are any controllers connected that were not deleted at the end of execution, delete them.
			// This wil prevent any memory leaks showing up in valgrind
			for ( auto& controller : Controller::s_allController )
			{
				delete controller;
			}
			Controller::s_allController.clear();
		}

		static ControllerImpl* getInstance()
		{
			static ControllerImpl instance;
			return &instance;
		}

		static void setRawInputPreferred(bool isRawInputPreferred)
		{
			_isRawInputPreferred = isRawInputPreferred;
		}

		static std::vector<Controller*>::iterator findController(int deviceId)
		{
			// When controllers are disconnected, GLFW cannot provide their names. We only get their deviceId.
			auto iter = std::find_if(Controller::s_allController.begin(), Controller::s_allController.end(),
									 [&](Controller* controller)
									 {
										 return deviceId == controller->_deviceId;
									 }
									);
			return iter;
		}

		static void onConnected(const std::string& deviceName, int deviceId)
		{
			// Check whether the controller is already registered
			auto iter = findController(deviceId);
			if (iter != Controller::s_allController.end())
				return;

			// It's a new controller being connected.
			auto controller = new cocos2d::Controller();
			controller->_deviceId = deviceId;
			controller->_deviceName = deviceName;
			Controller::s_allController.push_back(controller);

			controller->onConnected();
		}

		static void onDisconnected(int deviceId)
		{
			// Check whether the controller is already registered
			auto iter = findController(deviceId);
			if (iter == Controller::s_allController.end())
			{
				CCLOGERROR("ControllerImpl Error: Could not find the controller!");
				return;
			}

			(*iter)->onDisconnected();
			Controller::s_allController.erase(iter);
		}

		static void onButtonEvent(int deviceId, int keyCode, bool isPressed, float value, bool isAnalog)
		{
			auto iter = findController(deviceId);
			if (iter == Controller::s_allController.end())
			{
				CCLOG("ControllerImpl::onButtonEvent: new controller detected. Registering...");
				handleConnectionEvent(deviceId, GLFW_CONNECTED);
				iter = findController(deviceId);
			}

			(*iter)->onButtonEvent(keyCode, isPressed, value, isAnalog);
		}

		static void onAxisEvent(int deviceId, int axisCode, float value, bool isAnalog)
		{
			auto iter = findController(deviceId);
			if (iter == Controller::s_allController.end())
			{
				CCLOG("ControllerImpl::onAxisEvent: new controller detected. Registering...");
				handleConnectionEvent(deviceId, GLFW_CONNECTED);
				iter = findController(deviceId);
			}

			(*iter)->onAxisEvent(axisCode, value, isAnalog);
		}

		static void handleConnectionEvent(int deviceId, int event)
		{
			// glfw supports up to 16 game controllers
			// Handle game controller connections and disconnections
			if ( event == GLFW_CONNECTED )
			{
				const char *name =
					(!_isRawInputPreferred && glfwJoystickIsGamepad(deviceId)) ?
					glfwGetGamepadName(deviceId) :
					glfwGetJoystickName(deviceId);
				onConnected(name, deviceId);
			}
			else if ( event == GLFW_DISCONNECTED )
			{
				ControllerImpl::getInstance()->onDisconnected(deviceId);
			}
			#ifdef COCOS2D_DEBUG
			else
			{
				CCLOG("ControllerImpl: Unhandled GLFW joystick event: %d", event);
			}
			#endif
		}

		void update(float /*dt*/)
		{
			for (int deviceId = GLFW_JOYSTICK_1;  deviceId <= GLFW_JOYSTICK_LAST;  ++deviceId)
			{
				if (!glfwJoystickPresent(deviceId)) continue;
				
				auto controller = Controller::getControllerByDeviceId(deviceId);

				GLFWgamepadstate state;

				if (!_isRawInputPreferred && glfwGetGamepadState(deviceId, &state))
				{
					for (int i = 0; i <= GLFW_GAMEPAD_BUTTON_LAST; i++)
						onButtonEvent(deviceId, buttonInputMap[i], state.buttons[i] == GLFW_PRESS, 0, false);

					for (int i = 0; i <= GLFW_GAMEPAD_AXIS_LAST; i++)
						onAxisEvent(deviceId, axisInputMap[i], state.axes[i], true);
				}
				else
				{
					// Poll game controller button presses
					int count;
					const unsigned char* buttonArray = glfwGetJoystickButtons(deviceId, &count);
					for ( int i = 0; i < count; ++i )
						ControllerImpl::onButtonEvent(deviceId, i, buttonArray[i] == GLFW_PRESS, 0, false);

					// Poll game controller joystick axis
					const float * axisArray = glfwGetJoystickAxes(deviceId, &count);
					for ( int i = 0; i < count; ++i )
						ControllerImpl::onAxisEvent(deviceId, i, axisArray[i], true);
				}
			}
		}

private:

		static const Controller::Key buttonInputMap[GLFW_GAMEPAD_BUTTON_LAST + 1];
		static const Controller::Key axisInputMap[GLFW_GAMEPAD_AXIS_LAST + 1];

		static bool _isRawInputPreferred;
};

const Controller::Key ControllerImpl::buttonInputMap[GLFW_GAMEPAD_BUTTON_LAST + 1] = {
	Controller::BUTTON_A,                   // GLFW_GAMEPAD_BUTTON_A
	Controller::BUTTON_B,                   // GLFW_GAMEPAD_BUTTON_B
	Controller::BUTTON_X,                   // GLFW_GAMEPAD_BUTTON_X
	Controller::BUTTON_Y,                   // GLFW_GAMEPAD_BUTTON_Y
	Controller::BUTTON_LEFT_SHOULDER,       // GLFW_GAMEPAD_BUTTON_LEFT_BUMPER
	Controller::BUTTON_RIGHT_SHOULDER,      // GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER
	Controller::BUTTON_PAUSE,               // GLFW_GAMEPAD_BUTTON_BACK
	Controller::BUTTON_START,               // GLFW_GAMEPAD_BUTTON_START
	Controller::BUTTON_SELECT,              // GLFW_GAMEPAD_BUTTON_GUIDE
	Controller::BUTTON_LEFT_THUMBSTICK,     // GLFW_GAMEPAD_BUTTON_LEFT_THUMB
	Controller::BUTTON_RIGHT_THUMBSTICK,    // GLFW_GAMEPAD_BUTTON_RIGHT_THUMB
	Controller::BUTTON_DPAD_UP,             // GLFW_GAMEPAD_BUTTON_DPAD_UP
	Controller::BUTTON_DPAD_RIGHT,          // GLFW_GAMEPAD_BUTTON_DPAD_RIGHT
	Controller::BUTTON_DPAD_DOWN,           // GLFW_GAMEPAD_BUTTON_DPAD_DOWN
	Controller::BUTTON_DPAD_LEFT,           // GLFW_GAMEPAD_BUTTON_DPAD_LEFT
};

const Controller::Key ControllerImpl::axisInputMap[GLFW_GAMEPAD_AXIS_LAST + 1] = {
	Controller::JOYSTICK_LEFT_X,    // GLFW_GAMEPAD_AXIS_LEFT_X
	Controller::JOYSTICK_LEFT_Y,    // GLFW_GAMEPAD_AXIS_LEFT_Y
	Controller::JOYSTICK_RIGHT_X,   // GLFW_GAMEPAD_AXIS_RIGHT_X
	Controller::JOYSTICK_RIGHT_Y,   // GLFW_GAMEPAD_AXIS_RIGHT_Y
	Controller::AXIS_LEFT_TRIGGER,  // GLFW_GAMEPAD_AXIS_LEFT_TRIGGER
	Controller::AXIS_RIGHT_TRIGGER, // GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER
};

bool ControllerImpl::_isRawInputPreferred = false;

void Controller::startDiscoveryController(bool isRawInputPreferred)
{
	ControllerImpl::setRawInputPreferred(isRawInputPreferred);

	// Check for existing josyticks and register them as cocos2d::Controller:
	for (int deviceId = GLFW_JOYSTICK_1;  deviceId <= GLFW_JOYSTICK_LAST;  ++deviceId)
	{
		if (glfwJoystickPresent(deviceId))
			ControllerImpl::handleConnectionEvent(deviceId, GLFW_CONNECTED);
	}

	// GFLW sends events when a joystick is connected and disconnected only.
	// These events need to be filtered:
	glfwSetJoystickCallback(ControllerImpl::handleConnectionEvent);

	// Poll the joystick axis and buttons
	Director::getInstance()->getScheduler()->scheduleUpdate(ControllerImpl::getInstance(), 0, false);
}

void Controller::stopDiscoveryController()
{
	Director::getInstance()->getScheduler()->unscheduleUpdate(ControllerImpl::getInstance());
	glfwSetJoystickCallback(nullptr);

	// Also remove all the connected controllers:
	for ( auto& controller : Controller::s_allController )
	{
		delete controller;
	}
	Controller::s_allController.clear();
}

void Controller::registerListeners()
{
}

bool Controller::isConnected() const
{
	// If there is a controller instance, it means that the controller is connected.
	// If a controller is disconnected, the instance will be destroyed.
	// Thus, always returns true for this method.
	return true;
}

Controller::Controller()
	: _controllerTag(TAG_UNSET)
	, _impl(nullptr)
	, _connectEvent(nullptr)
	, _keyEvent(nullptr)
	  , _axisEvent(nullptr)
{
	init();
}

Controller::~Controller()
{
	delete _connectEvent;
	delete _keyEvent;
	delete _axisEvent;
}


NS_CC_END

#endif // #if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
