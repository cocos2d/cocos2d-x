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

#include "base/CCController.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <functional>
#include "base/ccMacros.h"
#include "base/CCDirector.h"
#include "platform/android/jni/JniHelper.h"
#include "base/CCEventController.h"

NS_CC_BEGIN

class ControllerImpl
{
public:
    ControllerImpl(Controller* controller)
            : _controller(controller)
    {
    }

    static std::vector<Controller*>::iterator findController(const std::string& deviceName, int deviceId)
    {
        auto iter = std::find_if(Controller::s_allController.begin(), Controller::s_allController.end(), [&](Controller* controller){
                return (deviceName == controller->_deviceName) && (deviceId == controller->_deviceId);
            });

        return iter;
    }

    static void onConnected(const std::string& deviceName, int deviceId)
    {
        // Check whether the controller is already connected.
        CCLOG("onConnected %s,%d", deviceName.c_str(),deviceId);

        auto iter = findController(deviceName, deviceId);
        if (iter != Controller::s_allController.end())
            return;

        // It's a new controller being connected.
        auto controller = new cocos2d::Controller();
        controller->_deviceId = deviceId;
        controller->_deviceName = deviceName;
        Controller::s_allController.push_back(controller);

        controller->onConnected();
    }

    static void onDisconnected(const std::string& deviceName, int deviceId)
    {
        CCLOG("onDisconnected %s,%d", deviceName.c_str(),deviceId);

        auto iter = findController(deviceName, deviceId);
        if (iter == Controller::s_allController.end())
        {
            CCLOGERROR("Could not find the controller!");
            return;
        }

        (*iter)->onDisconnected();
        Controller::s_allController.erase(iter);
    }

    static void onButtonEvent(const std::string& deviceName, int deviceId, int keyCode, bool isPressed, float value, bool isAnalog)
    {
        auto iter = findController(deviceName, deviceId);
        if (iter == Controller::s_allController.end())
        {
            CCLOG("onButtonEvent:connect new controller.");
            onConnected(deviceName, deviceId);
            iter = findController(deviceName, deviceId);
        }

        (*iter)->onButtonEvent(keyCode, isPressed, value, isAnalog);
    }

    static void onAxisEvent(const std::string& deviceName, int deviceId, int axisCode, float value, bool isAnalog)
    {
        auto iter = findController(deviceName, deviceId);
        if (iter == Controller::s_allController.end())
        {
            CCLOG("onAxisEvent:connect new controller.");
            onConnected(deviceName, deviceId);
            iter = findController(deviceName, deviceId);
        }
        
        (*iter)->onAxisEvent(axisCode, value, isAnalog);
    }

private:
    Controller* _controller;
};

void Controller::startDiscoveryController()
{
    // Empty implementation on Android
}

void Controller::stopDiscoveryController()
{
    // Empty implementation on Android
}

Controller::~Controller()
{
    delete _impl;

    delete _connectEvent;
    delete _keyEvent;
    delete _axisEvent;
}

void Controller::registerListeners()
{
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
    , _connectEvent(nullptr)
    , _keyEvent(nullptr)
    , _axisEvent(nullptr)
{
    init();
}

void Controller::receiveExternalKeyEvent(int externalKeyCode,bool receive) {
    JniHelper::callStaticVoidMethod("org/cocos2dx/lib/GameControllerHelper", "receiveExternalKeyEvent", _deviceId, externalKeyCode, receive);
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
