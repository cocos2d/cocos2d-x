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

#include "CCController.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "ccMacros.h"
#include "CCEventDispatcher.h"
#include "CCEventController.h"
#include "CCEventListenerController.h"
#include "CCDirector.h"

#include "jni/JniHelper.h"


NS_CC_BEGIN

static EventDispatcher* s_eventDispatcher = nullptr;

class ControllerImpl
{
public:
    ControllerImpl(Controller* controller)
            : _controller(controller)
            , _connectEvent()
    {
        if (s_eventDispatcher == nullptr)
        {
            s_eventDispatcher = Director::getInstance()->getEventDispatcher();
        }
        _connectEvent = new EventController(EventController::ControllerEventType::CONNECTION, controller, false);
        _keyEvent = new EventController(EventController::ControllerEventType::BUTTON_STATUS_CHANGED, controller, 0);
        _axisEvent = new EventController(EventController::ControllerEventType::AXIS_STATUS_CHANGED, controller, 0);
    }
    ~ControllerImpl()
    {
        delete _connectEvent;
        delete _keyEvent;
        delete _axisEvent;
    }

    static std::vector<Controller*>::iterator findController(const std::string& deviceName, int deviceId)
    {
        auto iter = std::find_if(Controller::s_allController.begin(), Controller::s_allController.end(), [&](Controller* controller){
                return (deviceName == controller->_deviceName) && (deviceId == controller->_deviceId);
            });
    }

    static void onConnected(const std::string& deviceName, int deviceId)
    {
        // Check whether the controller is already connected.
        log("onConnected %s,%d", deviceName.c_str(),deviceId);

        auto iter = findController(deviceName, deviceId);
        if (iter != Controller::s_allController.end())
            return;
        log("onConnected new device");
        // It's a new controller being connected.
        auto controller = new cocos2d::Controller();
        controller->_deviceId = deviceId;
        controller->_deviceName = deviceName;
        Controller::s_allController.push_back(controller);

        controller->_impl->_connectEvent->setConnectStatus(true);
        s_eventDispatcher->dispatchEvent(controller->_impl->_connectEvent);
    }

    static void onDisconnected(const std::string& deviceName, int deviceId)
    {
        log("onDisconnected %s,%d", deviceName.c_str(),deviceId);
        auto iter = findController(deviceName, deviceId);
        if (iter == Controller::s_allController.end())
        {
            log("Could not find the controller!");
            CCLOGERROR("Could not find the controller!");
            return;
        }

        (*iter)->_impl->_connectEvent->setConnectStatus(false);
        s_eventDispatcher->dispatchEvent((*iter)->_impl->_connectEvent);

        delete (*iter);
        Controller::s_allController.erase(iter);
    }

    static void onButtonEvent(const std::string& deviceName, int deviceId, int keyCode, bool isPressed, float value, bool isAnalog)
    {
        log("onButtonEvent %s,%d", deviceName.c_str(),deviceId);
        auto iter = findController(deviceName, deviceId);
        if (iter == Controller::s_allController.end())
        {
            log("onButtonEvent new connect");
            onConnected(deviceName, deviceId);
            iter = findController(deviceName, deviceId);
        }

        (*iter)->_allKeyPrevStatus[keyCode] = (*iter)->_allKeyStatus[keyCode];
        (*iter)->_allKeyStatus[keyCode].isPressed = isPressed;
        (*iter)->_allKeyStatus[keyCode].value = value;
        (*iter)->_allKeyStatus[keyCode].isAnalog = isAnalog;

        (*iter)->_impl->_keyEvent->setKeyCode(keyCode);
        s_eventDispatcher->dispatchEvent((*iter)->_impl->_keyEvent);
    }

    static void onAxisEvent(const std::string& deviceName, int deviceId, int axisCode, float value, bool isAnalog)
    {
        auto iter = findController(deviceName, deviceId);
        if (iter == Controller::s_allController.end())
        {
            onConnected(deviceName, deviceId);
            iter = findController(deviceName, deviceId);
        }

        (*iter)->_allKeyPrevStatus[axisCode] = (*iter)->_allKeyStatus[axisCode];
        (*iter)->_allKeyStatus[axisCode].value = value;
        (*iter)->_allKeyStatus[axisCode].isAnalog = isAnalog;

        (*iter)->_impl->_axisEvent->setKeyCode(axisCode);
        s_eventDispatcher->dispatchEvent((*iter)->_impl->_axisEvent);
    }

private:
    Controller* _controller;
    EventController *_connectEvent;
    EventController *_keyEvent;
    EventController *_axisEvent;
};


std::vector<Controller*> Controller::s_allController;

void Controller::startDiscoveryController()
{
    // Empty implementation on Android
}

void Controller::stopDiscoveryController()
{
    // Empty implementation on Android
}

Controller* Controller::getControllerByTag(int tag)
{
    for (auto controller:Controller::s_allController)
    {
        if (controller->_controllerTag == tag)
        {
            return controller;
        }
    }
    return nullptr;
}

const std::string& Controller::getDeviceName()
{
    return _deviceName;
}

bool Controller::isConnected() const
{
    // If there is a controller instance, it means that the controller is connected.
    // If a controller is disconnected, the instance will be destroyed.
    // So always returns true for this method.
    return true;
}

Controller::Controller()
    : _controllerTag(TAG_UNSET)
    , _impl(new ControllerImpl(this))
{
    for (int key = Key::JOYSTICK_LEFT_X; key < Key::KEY_MAX; ++key)
    {
        _allKeyStatus[key].isPressed = false;
        _allKeyStatus[key].value = 0.0f;

        _allKeyPrevStatus[key].isPressed = false;
        _allKeyPrevStatus[key].value = 0.0f;
    }
}

Controller::~Controller()
{
    CC_SAFE_DELETE(_impl);
}

const Controller::KeyStatus& Controller::getKeyStatus(int keyCode)
{
    if (_allKeyStatus.find(keyCode) == _allKeyStatus.end())
    {
        _allKeyStatus[keyCode].isPressed = false;
        _allKeyStatus[keyCode].value = 0.0f;
    }

    return _allKeyStatus[keyCode];
}

NS_CC_END

extern "C" {

    void Java_org_cocos2dx_lib_GameControllerAdapter_nativeControllerConnected(JNIEnv*  env, jobject thiz, jstring deviceName, jint controllerID)
    {
        CCLOG("controller id: %d connected!", controllerID);
        cocos2d::ControllerImpl::onConnected(cocos2d::JniHelper::jstring2string(deviceName), controllerID);
    }

    void Java_org_cocos2dx_lib_GameControllerAdapter_nativeControllerDisconnected(JNIEnv*  env, jobject thiz, jstring deviceName, jint controllerID)
    {
        CCLOG("controller id: %d disconnected!", controllerID);
        cocos2d::ControllerImpl::onDisconnected(cocos2d::JniHelper::jstring2string(deviceName), controllerID);
    }

    void Java_org_cocos2dx_lib_GameControllerAdapter_nativeControllerButtonEvent(JNIEnv*  env, jobject thiz, jstring deviceName, jint controllerID, jint button, jboolean isPressed, jfloat value, jboolean isAnalog)
    {
        cocos2d::ControllerImpl::onButtonEvent(cocos2d::JniHelper::jstring2string(deviceName), controllerID, button, isPressed, value, isAnalog);
    }

    void Java_org_cocos2dx_lib_GameControllerAdapter_nativeControllerAxisEvent(JNIEnv*  env, jobject thiz, jstring deviceName, jint controllerID, jint axis, jfloat value, jboolean isAnalog)
    {
        cocos2d::ControllerImpl::onAxisEvent(cocos2d::JniHelper::jstring2string(deviceName), controllerID, axis, value, isAnalog);
    }

} // extern "C" {


#endif // #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
