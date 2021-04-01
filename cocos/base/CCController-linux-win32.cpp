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

#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
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
			//FIXME: Once GLFW 3.3 is bundled with cocos2d-x and no extra
			//controllers have been added here, remove all the code here.  If
			//extra controllers were added, make sure to add them to the SDL
			//Controller Database at
			//https://github.com/gabomdq/SDL_GameControllerDB which GLFW uses
			//for providing the new gamepad API. We are going to map the GLFW
			//game pad events to Controller::Key key codes.


			// Note: the controllers input profile were taken from the
			// RetroArch joypad autoconfig project at:
			// https://github.com/libretro/retroarch-joypad-autoconfig/tree/master/udev

			// The configuration files were parsed into C++ code with:
			// https://github.com/Rubonnek/retroarch-joypad-config-to-cpp-mapper
			// which provides the following mapping from the RetroArch
			// configuration variables towards the cocos2d::Controller::Key key
			// codes.  Hardware-wise, the mapping goes from a theoretical SNES
			// controller with extra joysticks and shoulder buttons, towards an
			// Xbox-like controller which is widely common on mobile phones.

			// RetroArch variable    ->   Cocos2D-X equivalent
			// input_a_btn           ->   Controller::Key::BUTTON_B
			// input_b_btn           ->   Controller::Key::BUTTON_A
			// input_down_btn        ->   Controller::Key::BUTTON_DPAD_DOWN
			// input_l2_axis         ->   Controller::Key::AXIS_LEFT_TRIGGER
			// input_l3_btn          ->   Controller::Key::BUTTON_LEFT_THUMBSTICK
			// input_l_btn           ->   Controller::Key::BUTTON_LEFT_SHOULDER
			// input_l_x_minus_axis  ->   Controller::Key::JOYSTICK_LEFT_X
			// input_l_y_minus_axis  ->   Controller::Key::JOYSTICK_LEFT_Y
			// input_left_btn        ->   Controller::Key::BUTTON_DPAD_LEFT
			// input_r2_axis         ->   Controller::Key::AXIS_RIGHT_TRIGGER
			// input_r3_btn          ->   Controller::Key::BUTTON_RIGHT_THUMBSTICK
			// input_r_btn           ->   Controller::Key::BUTTON_RIGHT_SHOULDER
			// input_r_x_minus_axis  ->   Controller::Key::JOYSTICK_RIGHT_X
			// input_r_y_minus_axis  ->   Controller::Key::JOYSTICK_RIGHT_Y
			// input_right_btn       ->   Controller::Key::BUTTON_DPAD_RIGHT
			// input_select_btn      ->   Controller::Key::BUTTON_SELECT
			// input_start_btn       ->   Controller::Key::BUTTON_START
			// input_up_btn          ->   Controller::Key::BUTTON_DPAD_UP
			// input_x_btn           ->   Controller::Key::BUTTON_Y
			// input_y_btn           ->   Controller::Key::BUTTON_X

			// Preliminary support is added for 169 controllers, but on some
			// cases the mapping provided might not be correct and has to be
			// manually adjusted.


			// Create the necessary variables:
			std::string deviceName = "2Axes 11Keys Game  Pad";
			std::unordered_map<int,int> buttonInputMap;
			std::unordered_map<int,int> axisInputMap;


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[2] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[0] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "8Bitdo FC30 GamePad";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[4] = Controller::Key::BUTTON_X;
			buttonInputMap[10] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[11] = Controller::Key::BUTTON_START;
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "8Bitdo FC30 II";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[4] = Controller::Key::BUTTON_X;
			buttonInputMap[10] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[11] = Controller::Key::BUTTON_START;
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "8Bitdo FC30 II Joystick";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[4] = Controller::Key::BUTTON_X;
			buttonInputMap[10] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[11] = Controller::Key::BUTTON_START;
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "FC30               FC30  Joystick";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[4] = Controller::Key::BUTTON_X;
			buttonInputMap[10] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[11] = Controller::Key::BUTTON_START;
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "8Bitdo NES30 GamePad";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[4] = Controller::Key::BUTTON_X;
			buttonInputMap[10] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[11] = Controller::Key::BUTTON_START;
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "8Bitdo NES30 GamePad Joystick";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[4] = Controller::Key::BUTTON_X;
			buttonInputMap[10] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[11] = Controller::Key::BUTTON_START;
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "NES30              NES30 Joystick";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[4] = Controller::Key::BUTTON_X;
			buttonInputMap[10] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[11] = Controller::Key::BUTTON_START;
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "8Bitdo SFC30 GamePad";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[4] = Controller::Key::BUTTON_X;
			buttonInputMap[10] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[11] = Controller::Key::BUTTON_START;
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "8Bitdo SFC30 GamePad Joystick";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[4] = Controller::Key::BUTTON_X;
			buttonInputMap[10] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[11] = Controller::Key::BUTTON_START;
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "SFC30              SFC30 Joystick";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[4] = Controller::Key::BUTTON_X;
			buttonInputMap[10] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[11] = Controller::Key::BUTTON_START;
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "8Bitdo SNES30 GamePad";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[4] = Controller::Key::BUTTON_X;
			buttonInputMap[10] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[11] = Controller::Key::BUTTON_START;
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "8Bitdo SNES30 GamePad Joystick";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[4] = Controller::Key::BUTTON_X;
			buttonInputMap[10] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[11] = Controller::Key::BUTTON_START;
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "SNES30             SNES30 Joy    ";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[4] = Controller::Key::BUTTON_X;
			buttonInputMap[10] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[11] = Controller::Key::BUTTON_START;
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "8Bitdo Joy";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[11] = Controller::Key::BUTTON_A;
			buttonInputMap[14] = Controller::Key::BUTTON_X;
			buttonInputMap[21] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[22] = Controller::Key::BUTTON_START;
			buttonInputMap[12] = Controller::Key::BUTTON_B;
			buttonInputMap[15] = Controller::Key::BUTTON_Y;
			buttonInputMap[17] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[18] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "8Bitdo JoyStick    8Bitdo Joy    ";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "8Bitdo N64 GamePad";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[11] = Controller::Key::BUTTON_START;
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "8Bitdo N64         8Bitdo N64     ";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[11] = Controller::Key::BUTTON_START;
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[5] = Controller::Key::BUTTON_DPAD_LEFT;
			axisInputMap[4] = Controller::Key::BUTTON_DPAD_RIGHT;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "8Bitdo FC30 Pro";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[4] = Controller::Key::BUTTON_X;
			buttonInputMap[10] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[11] = Controller::Key::BUTTON_START;
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[13] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[14] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "8Bitdo FC30 Pro    8Bitdo FC30 Pro";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[4] = Controller::Key::BUTTON_X;
			buttonInputMap[10] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[11] = Controller::Key::BUTTON_START;
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[13] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[14] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;
			axisInputMap[7] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[7] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[5] = Controller::Key::BUTTON_DPAD_LEFT;
			axisInputMap[4] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "8Bitdo NES30 Pro";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[4] = Controller::Key::BUTTON_X;
			buttonInputMap[10] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[11] = Controller::Key::BUTTON_START;
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[13] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[14] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "8Bitdo NES30 Pro Joystick";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[4] = Controller::Key::BUTTON_X;
			buttonInputMap[10] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[11] = Controller::Key::BUTTON_START;
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[13] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[14] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "8Bitdo NES30 Pro   8Bitdo NES30 Pro";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[4] = Controller::Key::BUTTON_X;
			buttonInputMap[10] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[11] = Controller::Key::BUTTON_START;
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[13] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[14] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;
			axisInputMap[7] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[7] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[5] = Controller::Key::BUTTON_DPAD_LEFT;
			axisInputMap[4] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "8Bitdo Zero GamePad";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[10] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[11] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[4] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "raphnet.net (S)NES Atari USB";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[5] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[4] = Controller::Key::BUTTON_B;
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[8] = Controller::Key::BUTTON_Y;
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[3] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[2] = Controller::Key::BUTTON_RIGHT_SHOULDER;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "ACRUX QuanBa Arcade JoyStick 1008";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[2] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[5] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[4] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Afterglow controller for PS3";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Afterglow Gamepad for Xbox 360";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[6] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[7] = Controller::Key::BUTTON_START;
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[2] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[9] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[10] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[2] = Controller::Key::AXIS_LEFT_TRIGGER;
			axisInputMap[5] = Controller::Key::AXIS_RIGHT_TRIGGER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[4] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "BLISS-BOX 4PLAY PORT";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[5] = Controller::Key::BUTTON_A;
			buttonInputMap[4] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[14] = Controller::Key::BUTTON_DPAD_UP;
			buttonInputMap[15] = Controller::Key::BUTTON_DPAD_DOWN;
			buttonInputMap[16] = Controller::Key::BUTTON_DPAD_LEFT;
			buttonInputMap[17] = Controller::Key::BUTTON_DPAD_RIGHT;
			buttonInputMap[7] = Controller::Key::BUTTON_B;
			buttonInputMap[6] = Controller::Key::BUTTON_Y;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[18] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[19] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[4] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "ControlBlock Arcade Gamepad";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[5] = Controller::Key::BUTTON_X;
			buttonInputMap[11] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[10] = Controller::Key::BUTTON_START;
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[4] = Controller::Key::BUTTON_Y;
			buttonInputMap[2] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[3] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[8] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[9] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "ControlBlock SNES Gamepad";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[6] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[7] = Controller::Key::BUTTON_START;
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[2] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "ShanWan USB WirelessGamepad ";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[2] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[0] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;
			//axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			//axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "DragonRise Inc.   Generic   USB  Joystick  ";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_Y;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[2] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "DragonRise Inc. PC TWIN SHOCK Gamepad";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[2] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[0] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;
			//axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			//axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Performance Designed Products EA SPORTS Controller for PS3";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "USB GAMEPAD 8116";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[2] = Controller::Key::BUTTON_Y;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[4] = Controller::Key::AXIS_LEFT_TRIGGER;
			//axisInputMap[4] = Controller::Key::AXIS_RIGHT_TRIGGER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "G27 Racing Wheel";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[11] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[8] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[7] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[6] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[21] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[19] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[5] = Controller::Key::JOYSTICK_LEFT_Y;
			//axisInputMap[0] = Controller::Key::JOYSTICK_RIGHT_X;
			//axisInputMap[5] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Gamegirl Controller";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[1] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[2] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[3] = Controller::Key::BUTTON_DPAD_UP;
			buttonInputMap[4] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[5] = Controller::Key::BUTTON_X;
			buttonInputMap[6] = Controller::Key::BUTTON_DPAD_DOWN;
			buttonInputMap[7] = Controller::Key::BUTTON_Y;
			buttonInputMap[8] = Controller::Key::BUTTON_DPAD_RIGHT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[10] = Controller::Key::BUTTON_A;
			buttonInputMap[11] = Controller::Key::BUTTON_DPAD_LEFT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Gamtec.,Ltd SmartJoy PLUS Adapter";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[2] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[9] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[8] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[0] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;
			//axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			//axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Gasia Co.,Ltd PS(R) Gamepad";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[14] = Controller::Key::BUTTON_A;
			buttonInputMap[15] = Controller::Key::BUTTON_X;
			buttonInputMap[0] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[3] = Controller::Key::BUTTON_START;
			buttonInputMap[4] = Controller::Key::BUTTON_DPAD_UP;
			buttonInputMap[6] = Controller::Key::BUTTON_DPAD_DOWN;
			buttonInputMap[7] = Controller::Key::BUTTON_DPAD_LEFT;
			buttonInputMap[5] = Controller::Key::BUTTON_DPAD_RIGHT;
			buttonInputMap[13] = Controller::Key::BUTTON_B;
			buttonInputMap[12] = Controller::Key::BUTTON_Y;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[1] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[2] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "GEN GAME S3";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[9] = Controller::Key::BUTTON_A;
			buttonInputMap[12] = Controller::Key::BUTTON_X;
			buttonInputMap[19] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[20] = Controller::Key::BUTTON_START;
			buttonInputMap[10] = Controller::Key::BUTTON_B;
			buttonInputMap[13] = Controller::Key::BUTTON_Y;
			buttonInputMap[15] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[16] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[22] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[23] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Generic X-Box pad";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[2] = Controller::Key::BUTTON_X;
			buttonInputMap[6] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[7] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[9] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[10] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[2] = Controller::Key::AXIS_LEFT_TRIGGER;
			axisInputMap[5] = Controller::Key::AXIS_RIGHT_TRIGGER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[4] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "ShanWan Gioteck PS3 Wired Controller";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[2] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[0] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Gravis Destroyer Tiltpad";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[4] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[5] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			//buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			//buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			//buttonInputMap[4] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			//buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "GreenAsia Inc.    USB Joystick     ";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[2] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[0] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;
			//axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			//axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "GreenAsia Inc.      USB  Joystick  ";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[2] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[0] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "HJZ Mayflash WiiU Pro Game Controller Adapter";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "HORI CO.,LTD. Fighting Commander 4";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[5] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "HORI CO.,LTD. Fighting Commander";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Hori Fighting Stick EX2";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[2] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "HORI CO.,LTD. Fighting Stick mini 4";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "HORIPAD ONE";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[2] = Controller::Key::BUTTON_X;
			buttonInputMap[6] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[7] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[9] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[10] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[2] = Controller::Key::AXIS_LEFT_TRIGGER;
			axisInputMap[5] = Controller::Key::AXIS_RIGHT_TRIGGER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[4] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "HORI CO.,LTD  PAD A";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[2] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[0] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "HORI CO.,LTD. REAL ARCADE PRO.3";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "HORI CO.,LTD. Real Arcade Pro.4";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "BUFFALO BSGP1601 Series ";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[5] = Controller::Key::BUTTON_A;
			buttonInputMap[4] = Controller::Key::BUTTON_X;
			buttonInputMap[14] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[15] = Controller::Key::BUTTON_START;
			buttonInputMap[3] = Controller::Key::BUTTON_B;
			buttonInputMap[2] = Controller::Key::BUTTON_Y;
			buttonInputMap[8] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[9] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "USB,2-axis 8-button gamepad";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[6] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[7] = Controller::Key::BUTTON_START;
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[2] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "ION iCade";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[9] = Controller::Key::BUTTON_A;
			buttonInputMap[6] = Controller::Key::BUTTON_X;
			buttonInputMap[5] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[4] = Controller::Key::BUTTON_START;
			buttonInputMap[0] = Controller::Key::BUTTON_DPAD_UP;
			buttonInputMap[3] = Controller::Key::BUTTON_DPAD_DOWN;
			buttonInputMap[1] = Controller::Key::BUTTON_DPAD_LEFT;
			buttonInputMap[2] = Controller::Key::BUTTON_DPAD_RIGHT;
			buttonInputMap[8] = Controller::Key::BUTTON_B;
			buttonInputMap[7] = Controller::Key::BUTTON_Y;
			buttonInputMap[11] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_RIGHT_SHOULDER;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "ipega classic gamepad";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[19] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[20] = Controller::Key::BUTTON_START;
			buttonInputMap[10] = Controller::Key::BUTTON_B;
			buttonInputMap[13] = Controller::Key::BUTTON_Y;
			buttonInputMap[9] = Controller::Key::BUTTON_A;
			buttonInputMap[12] = Controller::Key::BUTTON_X;
			buttonInputMap[15] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[16] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[22] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[23] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[5] = Controller::Key::AXIS_LEFT_TRIGGER;
			axisInputMap[4] = Controller::Key::AXIS_RIGHT_TRIGGER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Jess Tech Colour Rumble Pad";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[2] = Controller::Key::BUTTON_A;
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[3] = Controller::Key::BUTTON_B;
			buttonInputMap[1] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[6] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Jess Tech Dual Analog Rumble Pad";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[2] = Controller::Key::BUTTON_A;
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[3] = Controller::Key::BUTTON_B;
			buttonInputMap[1] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[6] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "kadevice.com KADE - Kick Ass Dynamic Encoder";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Logic3 Controller";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[2] = Controller::Key::BUTTON_X;
			buttonInputMap[6] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[7] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[9] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[10] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[2] = Controller::Key::AXIS_LEFT_TRIGGER;
			axisInputMap[5] = Controller::Key::AXIS_RIGHT_TRIGGER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[4] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Logitech ChillStream PS3/USB Corded Gamepad";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[2] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[0] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Logitech Logitech Cordless RumblePad 2";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Logitech Logitech Dual Action";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Logitech Gamepad F310";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[2] = Controller::Key::BUTTON_X;
			buttonInputMap[6] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[7] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[9] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[10] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[2] = Controller::Key::AXIS_LEFT_TRIGGER;
			axisInputMap[5] = Controller::Key::AXIS_RIGHT_TRIGGER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[4] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Logitech Gamepad F510";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[2] = Controller::Key::BUTTON_X;
			buttonInputMap[6] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[7] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[9] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[10] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[2] = Controller::Key::AXIS_LEFT_TRIGGER;
			axisInputMap[5] = Controller::Key::AXIS_RIGHT_TRIGGER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[4] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Logitech Gamepad F710";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[2] = Controller::Key::BUTTON_X;
			buttonInputMap[6] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[7] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[9] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[10] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[2] = Controller::Key::AXIS_LEFT_TRIGGER;
			axisInputMap[5] = Controller::Key::AXIS_RIGHT_TRIGGER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[4] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Logitech Logitech(R) Precision(TM) Gamepad";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[2] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[0] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;
			//axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			//axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_Y;
			//axisInputMap[0] = Controller::Key::JOYSTICK_RIGHT_X;
			//axisInputMap[0] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Logitech Logitech RumblePad 2 USB";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;
			axisInputMap[4] = Controller::Key::JOYSTICK_LEFT_X;
			//axisInputMap[4] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Logitech WingMan Action Pad";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[4] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Mad catz Inc. Mad Catz FightPad PRO PS3";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Mad catz Inc. Mad Catz FightPad PRO PS4";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[5] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Mad Catz FightStick TE2+ PS3";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Mad Catz FightStick TE2+ PS4";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Mad Catz Wired Xbox 360 Controller (SFIV)";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[2] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[5] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Mad Catz Xbox 360 Controller";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[2] = Controller::Key::BUTTON_X;
			buttonInputMap[6] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[7] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[9] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[10] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[2] = Controller::Key::AXIS_LEFT_TRIGGER;
			axisInputMap[5] = Controller::Key::AXIS_RIGHT_TRIGGER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[4] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "  MAYFLASH Arcade Fightstick F300";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[4] = Controller::Key::BUTTON_X;
			buttonInputMap[10] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[11] = Controller::Key::BUTTON_START;
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "MAYFLASH Arcade Fightstick F300";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[2] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[0] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "HuiJia  USB GamePad";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[2] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[12] = Controller::Key::BUTTON_DPAD_UP;
			buttonInputMap[14] = Controller::Key::BUTTON_DPAD_DOWN;
			buttonInputMap[15] = Controller::Key::BUTTON_DPAD_LEFT;
			buttonInputMap[13] = Controller::Key::BUTTON_DPAD_RIGHT;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[0] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[3] = Controller::Key::AXIS_LEFT_TRIGGER;
			axisInputMap[4] = Controller::Key::AXIS_RIGHT_TRIGGER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[5] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Mega World Thrustmaster dual analog 3.2";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[1] = Controller::Key::BUTTON_X;
			buttonInputMap[11] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[10] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[6] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[8] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[9] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Mega World USB 2-Axis 8-Button Gamepad";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[1] = Controller::Key::BUTTON_X;
			buttonInputMap[5] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[7] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[6] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Microntek              USB Joystick          ";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[2] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[0] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;
			//axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			//axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Microsoft SideWinder Dual Strike USB version 1.0";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[3] = Controller::Key::BUTTON_A;
			buttonInputMap[1] = Controller::Key::BUTTON_X;
			buttonInputMap[5] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[4] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[0] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Microsoft® Microsoft® SideWinder® Game Pad USB";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[9] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[8] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[4] = Controller::Key::BUTTON_Y;
			buttonInputMap[5] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[2] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Microsoft® Microsoft® SideWinder® Plug & Play Game Pad";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[2] = Controller::Key::BUTTON_X;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Microsoft X-Box 360 pad";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[2] = Controller::Key::BUTTON_X;
			buttonInputMap[6] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[7] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[9] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[10] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[2] = Controller::Key::AXIS_LEFT_TRIGGER;
			axisInputMap[5] = Controller::Key::AXIS_RIGHT_TRIGGER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[4] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Microsoft X-Box One Elite pad";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[2] = Controller::Key::BUTTON_X;
			buttonInputMap[6] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[7] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[9] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[10] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[2] = Controller::Key::AXIS_LEFT_TRIGGER;
			axisInputMap[5] = Controller::Key::AXIS_RIGHT_TRIGGER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[4] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Microsoft X-Box One pad";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[2] = Controller::Key::BUTTON_X;
			buttonInputMap[6] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[7] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[9] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[10] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[2] = Controller::Key::AXIS_LEFT_TRIGGER;
			axisInputMap[5] = Controller::Key::AXIS_RIGHT_TRIGGER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[4] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Microsoft X-Box One pad (Firmware 2015)";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[2] = Controller::Key::BUTTON_X;
			buttonInputMap[6] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[7] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[9] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[10] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[2] = Controller::Key::AXIS_LEFT_TRIGGER;
			axisInputMap[5] = Controller::Key::AXIS_RIGHT_TRIGGER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[4] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Microsoft X-Box One S pad";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[2] = Controller::Key::BUTTON_X;
			buttonInputMap[6] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[7] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[9] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[10] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[2] = Controller::Key::AXIS_LEFT_TRIGGER;
			axisInputMap[5] = Controller::Key::AXIS_RIGHT_TRIGGER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[4] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Microsoft X-Box pad (Japan)";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[6] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[7] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[4] = Controller::Key::BUTTON_Y;
			buttonInputMap[5] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[2] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[8] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[9] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[2] = Controller::Key::AXIS_LEFT_TRIGGER;
			axisInputMap[5] = Controller::Key::AXIS_RIGHT_TRIGGER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[4] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Microsoft X-Box pad v1 (US)";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[6] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[7] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[4] = Controller::Key::BUTTON_Y;
			buttonInputMap[5] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[2] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[8] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[9] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[2] = Controller::Key::AXIS_LEFT_TRIGGER;
			axisInputMap[5] = Controller::Key::AXIS_RIGHT_TRIGGER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[4] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Microsoft X-Box pad v2 (US)";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[6] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[7] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[4] = Controller::Key::BUTTON_Y;
			buttonInputMap[5] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[2] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[8] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[9] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[2] = Controller::Key::AXIS_LEFT_TRIGGER;
			axisInputMap[5] = Controller::Key::AXIS_RIGHT_TRIGGER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[4] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "MOCUTE-032_B43-0F1E";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[13] = Controller::Key::BUTTON_A;
			buttonInputMap[15] = Controller::Key::BUTTON_X;
			//buttonInputMap[] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[21] = Controller::Key::BUTTON_START;
			buttonInputMap[12] = Controller::Key::BUTTON_B;
			buttonInputMap[14] = Controller::Key::BUTTON_Y;
			buttonInputMap[19] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[17] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			//buttonInputMap[] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			//buttonInputMap[] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;
			//axisInputMap[] = Controller::Key::JOYSTICK_LEFT_X;
			//axisInputMap[] = Controller::Key::JOYSTICK_LEFT_Y;
			//axisInputMap[] = Controller::Key::JOYSTICK_RIGHT_X;
			//axisInputMap[] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "MOSIC      SPEED-LINK Competition Pro ";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[2] = Controller::Key::BUTTON_A;
			buttonInputMap[1] = Controller::Key::BUTTON_START;
			buttonInputMap[3] = Controller::Key::BUTTON_SELECT;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "MOSIC      USB 2A8K  GamePad          ";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[2] = Controller::Key::BUTTON_A;
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[6] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[7] = Controller::Key::BUTTON_START;
			buttonInputMap[3] = Controller::Key::BUTTON_B;
			buttonInputMap[1] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "WiseGroup.,Ltd MP-8800 Quad USB Joypad";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[2] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[9] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[8] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[0] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "WiseGroup.,Ltd MP-8866 Dual USB Joypad";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[2] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[9] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[8] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[0] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "MY-POWER CO.,LTD. 2In1 USB Joystick";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[2] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[0] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Nintendo Clovercon - controller1";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[2] = Controller::Key::BUTTON_Y;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[11] = Controller::Key::BUTTON_DPAD_LEFT;
			buttonInputMap[12] = Controller::Key::BUTTON_DPAD_RIGHT;
			buttonInputMap[13] = Controller::Key::BUTTON_DPAD_UP;
			buttonInputMap[14] = Controller::Key::BUTTON_DPAD_DOWN;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Nintendo Clovercon - controller2";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[2] = Controller::Key::BUTTON_Y;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[11] = Controller::Key::BUTTON_DPAD_LEFT;
			buttonInputMap[12] = Controller::Key::BUTTON_DPAD_RIGHT;
			buttonInputMap[13] = Controller::Key::BUTTON_DPAD_UP;
			buttonInputMap[14] = Controller::Key::BUTTON_DPAD_DOWN;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Nintendo Wii Remote Pro Controller";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[13] = Controller::Key::BUTTON_DPAD_UP;
			buttonInputMap[14] = Controller::Key::BUTTON_DPAD_DOWN;
			buttonInputMap[15] = Controller::Key::BUTTON_DPAD_LEFT;
			buttonInputMap[16] = Controller::Key::BUTTON_DPAD_RIGHT;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[2] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[11] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[12] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Nintendo Wii Remote";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[4] = Controller::Key::BUTTON_A;
			buttonInputMap[7] = Controller::Key::BUTTON_X;
			buttonInputMap[10] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_DPAD_UP;
			buttonInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			buttonInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			buttonInputMap[3] = Controller::Key::BUTTON_DPAD_RIGHT;
			buttonInputMap[5] = Controller::Key::BUTTON_B;
			buttonInputMap[6] = Controller::Key::BUTTON_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Nintendo Wii Remote Classic Controller";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[5] = Controller::Key::BUTTON_A;
			buttonInputMap[7] = Controller::Key::BUTTON_X;
			buttonInputMap[14] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[13] = Controller::Key::BUTTON_START;
			buttonInputMap[0] = Controller::Key::BUTTON_DPAD_UP;
			buttonInputMap[3] = Controller::Key::BUTTON_DPAD_DOWN;
			buttonInputMap[1] = Controller::Key::BUTTON_DPAD_LEFT;
			buttonInputMap[2] = Controller::Key::BUTTON_DPAD_RIGHT;
			buttonInputMap[4] = Controller::Key::BUTTON_B;
			buttonInputMap[6] = Controller::Key::BUTTON_Y;
			buttonInputMap[9] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[8] = Controller::Key::BUTTON_LEFT_SHOULDER;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "NVIDIA Corporation NVIDIA Controller v01.04";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[2] = Controller::Key::BUTTON_X;
			buttonInputMap[6] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[8] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[5] = Controller::Key::AXIS_LEFT_TRIGGER;
			axisInputMap[4] = Controller::Key::AXIS_RIGHT_TRIGGER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "NVIDIA Corporation NVIDIA Controller v01.03";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[4] = Controller::Key::BUTTON_A;
			buttonInputMap[6] = Controller::Key::BUTTON_X;
			buttonInputMap[3] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[11] = Controller::Key::BUTTON_START;
			buttonInputMap[5] = Controller::Key::BUTTON_B;
			buttonInputMap[7] = Controller::Key::BUTTON_Y;
			buttonInputMap[8] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[9] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[12] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[13] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[5] = Controller::Key::AXIS_LEFT_TRIGGER;
			axisInputMap[4] = Controller::Key::AXIS_RIGHT_TRIGGER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "OUYA Game Controller";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[3] = Controller::Key::BUTTON_A;
			buttonInputMap[4] = Controller::Key::BUTTON_X;
			buttonInputMap[9] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[10] = Controller::Key::BUTTON_START;
			buttonInputMap[11] = Controller::Key::BUTTON_DPAD_UP;
			buttonInputMap[12] = Controller::Key::BUTTON_DPAD_DOWN;
			buttonInputMap[13] = Controller::Key::BUTTON_DPAD_LEFT;
			buttonInputMap[14] = Controller::Key::BUTTON_DPAD_RIGHT;
			buttonInputMap[6] = Controller::Key::BUTTON_B;
			buttonInputMap[5] = Controller::Key::BUTTON_Y;
			buttonInputMap[7] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[8] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			//buttonInputMap[9] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			//buttonInputMap[10] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[4] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "USB,4-Axis,12-Button with POV";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "playsega controller";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[4] = Controller::Key::BUTTON_Y;
			buttonInputMap[3] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "PLAYSTATION(R)3Conteroller-PANHAI";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[14] = Controller::Key::BUTTON_A;
			buttonInputMap[15] = Controller::Key::BUTTON_X;
			buttonInputMap[0] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[3] = Controller::Key::BUTTON_START;
			buttonInputMap[4] = Controller::Key::BUTTON_DPAD_UP;
			buttonInputMap[6] = Controller::Key::BUTTON_DPAD_DOWN;
			buttonInputMap[7] = Controller::Key::BUTTON_DPAD_LEFT;
			buttonInputMap[5] = Controller::Key::BUTTON_DPAD_RIGHT;
			buttonInputMap[13] = Controller::Key::BUTTON_B;
			buttonInputMap[12] = Controller::Key::BUTTON_Y;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[1] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[2] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Pro Controller";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[2] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Qnyx Snes Replica";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[2] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			//buttonInputMap[] = Controller::Key::BUTTON_DPAD_UP;
			//buttonInputMap[] = Controller::Key::BUTTON_DPAD_DOWN;
			//buttonInputMap[] = Controller::Key::BUTTON_DPAD_LEFT;
			//buttonInputMap[] = Controller::Key::BUTTON_DPAD_RIGHT;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[0] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			//buttonInputMap[] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			//buttonInputMap[] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			//axisInputMap[] = Controller::Key::JOYSTICK_RIGHT_X;
			//axisInputMap[] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "raphnet.net 4nes4snes";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[4] = Controller::Key::BUTTON_START;
			buttonInputMap[5] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[6] = Controller::Key::BUTTON_A;
			buttonInputMap[7] = Controller::Key::BUTTON_B;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "raphnet.net Saturn_Adapter_2.0";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[2] = Controller::Key::BUTTON_A;
			buttonInputMap[1] = Controller::Key::BUTTON_X;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[5] = Controller::Key::BUTTON_B;
			buttonInputMap[0] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Razer Serval";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[2] = Controller::Key::BUTTON_X;
			buttonInputMap[6] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[7] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[9] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[10] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[5] = Controller::Key::AXIS_LEFT_TRIGGER;
			axisInputMap[4] = Controller::Key::AXIS_RIGHT_TRIGGER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Retrolink Nintento 64 Classic USB";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[8] = Controller::Key::BUTTON_A;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[6] = Controller::Key::BUTTON_B;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "retronicdesign.com Sega Joypad Adapter v3.0";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[3] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "RetroUSB.com RetroPad";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[2] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[3] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "RetroUSB.com SNES RetroPort";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[2] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[3] = Controller::Key::BUTTON_START;
			buttonInputMap[5] = Controller::Key::BUTTON_B;
			buttonInputMap[4] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Rock Candy Gamepad for PS3";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Saitek Cyborg Rumble Pad";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[2] = Controller::Key::BUTTON_X;
			buttonInputMap[6] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[7] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[2] = Controller::Key::AXIS_LEFT_TRIGGER;
			axisInputMap[5] = Controller::Key::AXIS_RIGHT_TRIGGER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[4] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "SAITEK P880";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[2] = Controller::Key::BUTTON_A;
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[4] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[5] = Controller::Key::BUTTON_START;
			buttonInputMap[3] = Controller::Key::BUTTON_B;
			buttonInputMap[1] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[8] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[9] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[5] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[5] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[4] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[4] = Controller::Key::BUTTON_DPAD_RIGHT;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Saitek P990 Dual Analog Pad";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[9] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[8] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Saitek PLC Saitek P2600 Rumble Force Pad";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[9] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[8] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Saitek Saitek X52 Flight Control System";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[2] = Controller::Key::BUTTON_X;
			buttonInputMap[30] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[6] = Controller::Key::BUTTON_START;
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[18] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[16] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[5] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Samsung Game Pad EI-GP20";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[11] = Controller::Key::BUTTON_A;
			buttonInputMap[14] = Controller::Key::BUTTON_X;
			buttonInputMap[21] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[22] = Controller::Key::BUTTON_START;
			buttonInputMap[12] = Controller::Key::BUTTON_B;
			buttonInputMap[15] = Controller::Key::BUTTON_Y;
			buttonInputMap[17] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[18] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "CYPRESS USB Gamepad";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Smartjoy Family Super Smartjoy 2";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[2] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[4] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[5] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[0] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "SNES-to-Gamepad Device";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[6] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[7] = Controller::Key::BUTTON_START;
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[2] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "PLAYSTATION(R)3 Controller";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[14] = Controller::Key::BUTTON_A;
			buttonInputMap[15] = Controller::Key::BUTTON_X;
			buttonInputMap[0] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[3] = Controller::Key::BUTTON_START;
			buttonInputMap[4] = Controller::Key::BUTTON_DPAD_UP;
			buttonInputMap[6] = Controller::Key::BUTTON_DPAD_DOWN;
			buttonInputMap[7] = Controller::Key::BUTTON_DPAD_LEFT;
			buttonInputMap[5] = Controller::Key::BUTTON_DPAD_RIGHT;
			buttonInputMap[13] = Controller::Key::BUTTON_B;
			buttonInputMap[12] = Controller::Key::BUTTON_Y;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[1] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[2] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Sony Computer Entertainment Wireless Controller";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[14] = Controller::Key::BUTTON_A;
			buttonInputMap[15] = Controller::Key::BUTTON_X;
			buttonInputMap[0] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[3] = Controller::Key::BUTTON_START;
			buttonInputMap[4] = Controller::Key::BUTTON_DPAD_UP;
			buttonInputMap[6] = Controller::Key::BUTTON_DPAD_DOWN;
			buttonInputMap[7] = Controller::Key::BUTTON_DPAD_LEFT;
			buttonInputMap[5] = Controller::Key::BUTTON_DPAD_RIGHT;
			buttonInputMap[13] = Controller::Key::BUTTON_B;
			buttonInputMap[12] = Controller::Key::BUTTON_Y;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[1] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[2] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Sony PLAYSTATION(R)3 Controller";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[14] = Controller::Key::BUTTON_A;
			buttonInputMap[15] = Controller::Key::BUTTON_X;
			buttonInputMap[0] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[3] = Controller::Key::BUTTON_START;
			buttonInputMap[4] = Controller::Key::BUTTON_DPAD_UP;
			buttonInputMap[6] = Controller::Key::BUTTON_DPAD_DOWN;
			buttonInputMap[7] = Controller::Key::BUTTON_DPAD_LEFT;
			buttonInputMap[5] = Controller::Key::BUTTON_DPAD_RIGHT;
			buttonInputMap[13] = Controller::Key::BUTTON_B;
			buttonInputMap[12] = Controller::Key::BUTTON_Y;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[1] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[2] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Wireless Controller";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[2] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[11] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[12] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[4] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Sony Interactive Entertainment Wireless Controller";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[5] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Steam Controller";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[2] = Controller::Key::BUTTON_X;
			buttonInputMap[6] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[7] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			//buttonInputMap[0] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			//buttonInputMap[2] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;
			axisInputMap[2] = Controller::Key::AXIS_LEFT_TRIGGER;
			axisInputMap[5] = Controller::Key::AXIS_RIGHT_TRIGGER;
			axisInputMap[6] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[7] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[4] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Street Fighter IV FightPad";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[2] = Controller::Key::BUTTON_X;
			buttonInputMap[6] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[7] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;
			axisInputMap[5] = Controller::Key::AXIS_RIGHT_TRIGGER;
			//axisInputMap[DPad Up] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[DPad Down] = Controller::Key::BUTTON_DPAD_DOWN;
			//axisInputMap[DPad Left] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[DPad Right] = Controller::Key::BUTTON_DPAD_RIGHT;
			//axisInputMap[Right Trigger] = Controller::Key::AXIS_RIGHT_TRIGGER;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Thrustmaster Dual Trigger 3-in-1";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[5] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "THRUSTMASTER FireStorm Dual Analog 2";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[1] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[6] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			//buttonInputMap[8] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			//buttonInputMap[9] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "THRUSTMASTER FireStorm Dual Power 2 ";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[1] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[6] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Thrustmaster T Mini";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[1] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[6] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Thrustmaster T Mini Wireless";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "THRUSTMASTER Top Gun Fox 2  Pro ";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[6] = Controller::Key::BUTTON_X;
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "PC Game Controller       ";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[4] = Controller::Key::BUTTON_A;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[5] = Controller::Key::BUTTON_B;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "TOMMO NEOGEOX Arcade Stick";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[2] = Controller::Key::BUTTON_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Toodles 2008 ChImp PC/PS3 Controller";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[5] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Twin USB Joystick";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[2] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[0] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;
			//axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			//axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "USB,2-axis 8-button gamepad  ";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[6] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[7] = Controller::Key::BUTTON_START;
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[2] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "USB gamepad           ";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[2] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[0] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "USB Gamepad ";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[2] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[0] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "usb gamepad           ";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[2] = Controller::Key::BUTTON_A;
			buttonInputMap[0] = Controller::Key::BUTTON_Y;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "USB Joystick ";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[2] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[0] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;
			//axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			//axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "USB Vibration Joystick";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[2] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[12] = Controller::Key::BUTTON_DPAD_UP;
			buttonInputMap[14] = Controller::Key::BUTTON_DPAD_DOWN;
			buttonInputMap[15] = Controller::Key::BUTTON_DPAD_LEFT;
			buttonInputMap[13] = Controller::Key::BUTTON_DPAD_RIGHT;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[0] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Venom Limited PS3/PS4 Arcade Joystick";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[2] = Controller::Key::BUTTON_B;
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[0] = Controller::Key::BUTTON_X;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Wii U GameCube Adapter Port 1";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[3] = Controller::Key::BUTTON_A;
			buttonInputMap[2] = Controller::Key::BUTTON_X;
			buttonInputMap[6] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[7] = Controller::Key::BUTTON_START;
			buttonInputMap[8] = Controller::Key::BUTTON_DPAD_UP;
			buttonInputMap[9] = Controller::Key::BUTTON_DPAD_DOWN;
			buttonInputMap[10] = Controller::Key::BUTTON_DPAD_LEFT;
			buttonInputMap[11] = Controller::Key::BUTTON_DPAD_RIGHT;
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[1] = Controller::Key::BUTTON_Y;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[4] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "WiseGroup.,Ltd SmartJoy Dual PLUS Adapter";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[2] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[9] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[8] = Controller::Key::BUTTON_START;
			buttonInputMap[12] = Controller::Key::BUTTON_DPAD_UP;
			buttonInputMap[14] = Controller::Key::BUTTON_DPAD_DOWN;
			buttonInputMap[15] = Controller::Key::BUTTON_DPAD_LEFT;
			buttonInputMap[13] = Controller::Key::BUTTON_DPAD_RIGHT;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[0] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;
			//axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			//axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Xarcade-to-Gamepad Device";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[3] = Controller::Key::BUTTON_A;
			buttonInputMap[0] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[4] = Controller::Key::BUTTON_B;
			buttonInputMap[1] = Controller::Key::BUTTON_Y;
			buttonInputMap[2] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[1] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[1] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[0] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[0] = Controller::Key::BUTTON_DPAD_RIGHT;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Xbox 360 Wireless Receiver";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[2] = Controller::Key::BUTTON_X;
			buttonInputMap[6] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[7] = Controller::Key::BUTTON_START;
			buttonInputMap[13] = Controller::Key::BUTTON_DPAD_UP;
			buttonInputMap[14] = Controller::Key::BUTTON_DPAD_DOWN;
			buttonInputMap[11] = Controller::Key::BUTTON_DPAD_LEFT;
			buttonInputMap[12] = Controller::Key::BUTTON_DPAD_RIGHT;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[9] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[10] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[2] = Controller::Key::AXIS_LEFT_TRIGGER;
			axisInputMap[5] = Controller::Key::AXIS_RIGHT_TRIGGER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[4] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Xbox 360 Wireless Receiver (XBOX)";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[2] = Controller::Key::BUTTON_X;
			buttonInputMap[6] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[7] = Controller::Key::BUTTON_START;
			buttonInputMap[13] = Controller::Key::BUTTON_DPAD_UP;
			buttonInputMap[14] = Controller::Key::BUTTON_DPAD_DOWN;
			buttonInputMap[11] = Controller::Key::BUTTON_DPAD_LEFT;
			buttonInputMap[12] = Controller::Key::BUTTON_DPAD_RIGHT;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[9] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[10] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[2] = Controller::Key::AXIS_LEFT_TRIGGER;
			axisInputMap[5] = Controller::Key::AXIS_RIGHT_TRIGGER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[4] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Wireless Xbox 360 Controller";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[2] = Controller::Key::BUTTON_X;
			buttonInputMap[6] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[7] = Controller::Key::BUTTON_START;
			buttonInputMap[13] = Controller::Key::BUTTON_DPAD_UP;
			buttonInputMap[14] = Controller::Key::BUTTON_DPAD_DOWN;
			buttonInputMap[11] = Controller::Key::BUTTON_DPAD_LEFT;
			buttonInputMap[12] = Controller::Key::BUTTON_DPAD_RIGHT;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[9] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[10] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[2] = Controller::Key::AXIS_LEFT_TRIGGER;
			axisInputMap[5] = Controller::Key::AXIS_RIGHT_TRIGGER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[4] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));

			// Prepare variables:
			deviceName = "Xbox Gamepad (userspace driver)";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[2] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[11] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[12] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[5] = Controller::Key::BUTTON_DPAD_UP;
			//axisInputMap[5] = Controller::Key::BUTTON_DPAD_DOWN;
			axisInputMap[4] = Controller::Key::BUTTON_DPAD_LEFT;
			//axisInputMap[4] = Controller::Key::BUTTON_DPAD_RIGHT;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Xbox 360 Controller";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[2] = Controller::Key::BUTTON_X;
			buttonInputMap[6] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[7] = Controller::Key::BUTTON_START;
			buttonInputMap[13] = Controller::Key::BUTTON_DPAD_UP;
			buttonInputMap[14] = Controller::Key::BUTTON_DPAD_DOWN;
			buttonInputMap[11] = Controller::Key::BUTTON_DPAD_LEFT;
			buttonInputMap[12] = Controller::Key::BUTTON_DPAD_RIGHT;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[3] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[9] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[10] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[4] = Controller::Key::AXIS_LEFT_TRIGGER;
			axisInputMap[5] = Controller::Key::AXIS_RIGHT_TRIGGER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));

			// Prepare variables:
			deviceName = "SL-6566";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[1] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[0] = Controller::Key::BUTTON_B;
			buttonInputMap[2] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Gamesir-G3s";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[10] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[11] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[4] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[13] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[14] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "xiaoji Gamesir-G3s 1.02";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[10] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[11] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[4] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[13] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[14] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Gamesir-G3v";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[10] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[11] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[4] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[13] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[14] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "xiaoji Gamesir-G3v 1.00";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[10] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[11] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[4] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[13] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[14] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "小米蓝牙手柄";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[4] = Controller::Key::BUTTON_A;
			buttonInputMap[7] = Controller::Key::BUTTON_X;
			buttonInputMap[14] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[15] = Controller::Key::BUTTON_START;
			buttonInputMap[5] = Controller::Key::BUTTON_B;
			buttonInputMap[8] = Controller::Key::BUTTON_Y;
			buttonInputMap[10] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[11] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[17] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[18] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[5] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "USB Game Device";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[2] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[8] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[9] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[0] = Controller::Key::BUTTON_Y;
			buttonInputMap[4] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[5] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Zeemote: SteelSeries FREE";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[0] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[12] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[11] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[4] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));


			// Prepare variables:
			deviceName = "Zeroplus PS Vibration Feedback Converter ";
			buttonInputMap.clear();
			axisInputMap.clear();


			// Map the controller inputs to Controller::Key codes
			buttonInputMap[2] = Controller::Key::BUTTON_A;
			buttonInputMap[3] = Controller::Key::BUTTON_X;
			buttonInputMap[11] = Controller::Key::BUTTON_SELECT;
			buttonInputMap[8] = Controller::Key::BUTTON_START;
			buttonInputMap[1] = Controller::Key::BUTTON_B;
			buttonInputMap[0] = Controller::Key::BUTTON_Y;
			buttonInputMap[6] = Controller::Key::BUTTON_LEFT_SHOULDER;
			buttonInputMap[7] = Controller::Key::BUTTON_RIGHT_SHOULDER;
			buttonInputMap[9] = Controller::Key::BUTTON_LEFT_THUMBSTICK;
			buttonInputMap[10] = Controller::Key::BUTTON_RIGHT_THUMBSTICK;
			axisInputMap[0] = Controller::Key::JOYSTICK_LEFT_X;
			axisInputMap[1] = Controller::Key::JOYSTICK_LEFT_Y;
			axisInputMap[3] = Controller::Key::JOYSTICK_RIGHT_X;
			axisInputMap[2] = Controller::Key::JOYSTICK_RIGHT_Y;


			// Add the controller profile to the map
			s_controllerProfiles.insert(std::make_pair(deviceName, std::make_pair(buttonInputMap, axisInputMap)));
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

			// Check if we already have an available input controller profile. If so, attach it it to the controller.
			for (const auto & it : s_controllerProfiles)
			{
				if ( deviceName.compare(it.first) == 0 )
				{
					// Found controller profile. Attach it to the controller:
					CCLOG("ControllerImpl: Found input profile for controller: %s", deviceName.c_str());
					controller->_buttonInputMap = it.second.first;
					controller->_axisInputMap = it.second.second;


					// Show a one-time warning in debug mode for every button that's currently not matched in the input profile.
					// This will let the developers know that the mapping must be included in the constructor of ControllerImpl located above.
					#ifdef COCOS2D_DEBUG
					int count;
					glfwGetJoystickButtons(deviceId, &count);
					for ( int i = 0; i < count; ++i )
					{
						// Check the mapping of each button:
						const auto & it = controller->_buttonInputMap.find(i);
						if ( it == controller->_buttonInputMap.end() )
						{
							CCLOG("ControllerImpl: Could not find a button input mapping for controller \"%s\", and keyCode \"%d\". This keyCode will not match any from Controller::Key", controller->getDeviceName().c_str(), i);
						}
					}

					glfwGetJoystickAxes(deviceId, &count);
					for ( int i = 0; i < count; ++i )
					{
						// Check the mapping of each axis
						const auto & it = controller->_axisInputMap.find(i);
						if ( it == controller->_axisInputMap.end() )
						{
							CCLOG("ControllerImpl: Could not find an axis input mapping for controller \"%s\", and keyCode \"%d\". This keyCode will not match any from Controller::Key", controller->getDeviceName().c_str(), i);
						}
					}
					#endif

					break;
				}
			}

			// Show a warning if the controller input profile is non-existent:
			#ifdef COCOS2D_DEBUG
			if ( controller->_buttonInputMap.empty() )
			{
				CCLOG("ControllerImpl: Could not find a button input map for controller: %s", deviceName.c_str());
			}

			if ( controller->_axisInputMap.empty() )
			{
				CCLOG("ControllerImpl: Could not find an axis input map for controller: %s", deviceName.c_str());
			}
			#endif

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
				onConnected(glfwGetJoystickName(deviceId), deviceId);
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
				onConnected(glfwGetJoystickName(deviceId), deviceId);
				iter = findController(deviceId);
			}

			(*iter)->onAxisEvent(axisCode, value, isAnalog);
		}

		static void handleConnectionsAndDisconnections(int deviceId, int event)
		{
			// glfw supports up to 16 game controllers
			// Handle game controller connections and disconnections
			if ( event == GLFW_CONNECTED )
			{
				onConnected(glfwGetJoystickName(deviceId), deviceId);
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
				if ( glfwJoystickPresent(deviceId) )
				{
					auto controller = Controller::getControllerByDeviceId(deviceId);

					// Poll game controller button presses
					int count;
					const unsigned char* buttonArray = glfwGetJoystickButtons(deviceId, &count);
					for ( int i = 0; i < count; ++i )
					{
						// Map the button to the Controller:Key keys from the controller profile if it's available:
						int keyCode = i;
						const auto & it = controller->_buttonInputMap.find(keyCode);
						if ( it != controller->_buttonInputMap.end() )
						{
							keyCode = it->second;
						}
						ControllerImpl::onButtonEvent(deviceId, keyCode, buttonArray[i] == GLFW_PRESS, 0, false);
					}

					// Poll game controller joystick axis
					const float * axisArray = glfwGetJoystickAxes(deviceId, &count);
					for ( int i = 0; i < count; ++i )
					{
						// Map the axis to the Controller:Key keys from the controller profile if it's available:
						int keyCode = i;
						const auto & it = controller->_axisInputMap.find(keyCode);
						if ( it != controller->_axisInputMap.end() )
						{
							keyCode = it->second;
						}
						ControllerImpl::onAxisEvent(deviceId, keyCode, axisArray[i], true);
					}
				}
			}
		}

	private:
		//FIXME: Once GLFW 3.3 is bundled with cocos2d-x, remove these
		//controller profiles and all the related code.  We will only need to
		//provide a mapping from the GLFW gamepad key codes to the
		//Controller::Key keycodes. So far an std::unordered_map<int,int>
		//should suffice.
		static std::map<std::string, std::pair< std::unordered_map<int, int>, std::unordered_map<int, int> > > s_controllerProfiles;
};

std::map<std::string, std::pair< std::unordered_map<int, int>, std::unordered_map<int, int> > > ControllerImpl::s_controllerProfiles;

void Controller::startDiscoveryController()
{
	// Check for existing josyticks and register them as cocos2d::Controller:
	for (int deviceId = GLFW_JOYSTICK_1;  deviceId <= GLFW_JOYSTICK_LAST;  ++deviceId)
	{
		if (glfwJoystickPresent(deviceId))
		{
			int axis_count, button_count;
			glfwGetJoystickAxes(deviceId, &axis_count);
			glfwGetJoystickButtons(deviceId, &button_count);
			const char* name = glfwGetJoystickName(deviceId);
			ControllerImpl::onConnected(name, deviceId);
		}
	}

	// GFLW sends events when a joystick is connected and disconnected only.
	// These events need to be filtered:
	glfwSetJoystickCallback(ControllerImpl::handleConnectionsAndDisconnections);

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

#endif // #if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
