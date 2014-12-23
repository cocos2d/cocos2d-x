/****************************************************************************
 Copyright (c) 2014 cocos2d-x.org
 Copyright (c) 2014 Chukong Technologies Inc.
 
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

#ifndef __cocos2d_libs__CCController__
#define __cocos2d_libs__CCController__

#include "platform/CCPlatformMacros.h"
#include <string>
#include <vector>
#include <unordered_map>

NS_CC_BEGIN

class ControllerImpl;
class EventListenerController;
class EventController;
class EventDispatcher;

class Controller
{
public:
    /** Controllers' standard  key
     * Controller receives only standard key which contained within enum Key by default.
     */
    enum Key
    {
        JOYSTICK_LEFT_X = 1000,
        JOYSTICK_LEFT_Y,
        JOYSTICK_RIGHT_X,
        JOYSTICK_RIGHT_Y,

        BUTTON_A,
        BUTTON_B,
        BUTTON_C,
        BUTTON_X,
        BUTTON_Y,
        BUTTON_Z,
       
        BUTTON_DPAD_UP,
        BUTTON_DPAD_DOWN,
        BUTTON_DPAD_LEFT,
        BUTTON_DPAD_RIGHT,
        BUTTON_DPAD_CENTER,

        BUTTON_LEFT_SHOULDER,
        BUTTON_RIGHT_SHOULDER,

        AXIS_LEFT_TRIGGER,
        AXIS_RIGHT_TRIGGER,

        BUTTON_LEFT_THUMBSTICK,
        BUTTON_RIGHT_THUMBSTICK,

        BUTTON_START,
        BUTTON_SELECT,

        BUTTON_PAUSE,
        KEY_MAX
    };

    typedef struct _keyStatus
    {
        bool isPressed;
        float value;
        bool isAnalog;
    }KeyStatus;
    
    static const int TAG_UNSET = -1;

    static const std::vector<Controller*>& getAllController(){ return s_allController;}
    /** Gets a controller with its tag
     * @param tag   An identifier to find the controller.
     */
    static Controller* getControllerByTag(int tag);
    /** To start discovering new controllers
     * @warning The API only work on the IOS platform.Empty implementation on Android
     */
    static void startDiscoveryController();
    /** End the discovery process
     * @warning The API only work on the IOS platform.Empty implementation on Android
     */
    static void stopDiscoveryController();

    const std::string& getDeviceName() const { return _deviceName;}
    int getDeviceId() const { return _deviceId;}

    bool isConnected() const;

    const KeyStatus& getKeyStatus(int keyCode);
    
    /** Activate receives key event from external key. e.g. back,menu.
     * Controller receives only standard key which contained within enum Key by default.
     * @warning The API only work on the android platform for support diversified game controller.
     *
     * @param externalKeyCode  external key code
     * @param receive  true if external key event on this controller should be receive, false otherwise.
     */
    void receiveExternalKeyEvent(int externalKeyCode,bool receive);

    /** Changes the tag that is used to identify the controller easily.
     * @param tag   A integer that identifies the controller.
     */
    void setTag(int tag) { _controllerTag = tag;}
    /**
     * Returns a tag that is used to identify the controller easily.
     *
     * @return An integer that identifies the controller.
     */
    int getTag() const { return _controllerTag;}

private:
    static std::vector<Controller*> s_allController;

    Controller();
    virtual ~Controller();

    void init();

    void onConnected();
    void onDisconnected();
    void onButtonEvent(int keyCode, bool isPressed, float value, bool isAnalog);
    void onAxisEvent(int axisCode, float value, bool isAnalog);
    void registerListeners();

    std::unordered_map<int, KeyStatus> _allKeyStatus;
    std::unordered_map<int, KeyStatus> _allKeyPrevStatus;

    std::string _deviceName;
    int _deviceId;

    int _controllerTag;

    ControllerImpl* _impl;

    EventDispatcher* _eventDispatcher;
    EventController *_connectEvent;
    EventController *_keyEvent;
    EventController *_axisEvent;

    friend class ControllerImpl;
    friend class EventListenerController;
};


NS_CC_END

#endif /* defined(__cocos2d_libs__CCController__) */
