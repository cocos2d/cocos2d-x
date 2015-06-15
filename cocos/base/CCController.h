/****************************************************************************
 Copyright (c) 2014-2015 Chukong Technologies Inc.
 
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


/**
 * @addtogroup base
 * @{
 */


/**
 * @class Controller
 * @brief @~english A Controller object represents a connected physical game controller.
 * @~chinese 一个连接实体游戏的手柄。
 * @js NA
 */
class Controller
{
public:

    /** @~english
     * Controllers' standard  key
     * Controller receives only standard key which contained within enum Key by default.
     * @~chinese 
     * 控制器的标准键
     * 默认地，控制器只接收包含在enum Key中的标准key。
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


    /**
     * @struct KeyStatus
     *
     */
    typedef struct _keyStatus
    {

        /** @~english A Boolean value that indicates whether the key is considered pressed.  @~chinese 一个布尔值,表明键是否按下。*/
        bool isPressed;

        /** @~english The value of key.This value is used in conjunction with the isPressed parameter.  @~chinese 键值。这个值是与isPressed参数一起使用。*/
        float value;

        /** @~english A Boolean value that indicates whether the value of key is analog.
         * If isAnalog is true, the key value might be a float from -1 to 1. 
         * If isAnalog is false, the key value would be contain one number: 0 or 1.
         * @~chinese 一个布尔值,指示键值是否是模拟的。
         * 如果isAnalog是真的,键值可能是一个浮点数从1到1。
         * 如果isAnalog是假的,键值将包含一个数字:0或1。
         */
        bool isAnalog;
    }KeyStatus;
    
    static const int TAG_UNSET = -1;


    /**@~english
     * Gets all Controller objects.
     * @~chinese 
     * 获取所有控制器对象。
     * @return @~english all Controller objects.
     * @~chinese 所有控制器对象。
     */
    static const std::vector<Controller*>& getAllController(){ return s_allController;}


    /** @~english
     * Gets a Controller object with tag.
     *
     * @~chinese 
     * 根据标签得到一个控制器对象。
     * 
     * @param tag   @~english An identifier to find the controller.
     * @~chinese 一个用于查找控制器的标识。
     * @return @~english A Controller object.
     * @~chinese 一个控制器对象。
     */
    static Controller* getControllerByTag(int tag);


    /**@~english
     * Start discovering new controllers.
     *
     * @~chinese 
     * 开始搜索新控制器。
     * 
     * @warning @~english The API only work on the IOS platform. Empty implementation on other platform.
     * @~chinese 此API只在IOS平台上工作。其他平台为空实现。
     */
    static void startDiscoveryController();


    /** @~english
     * Stop the discovery process.
     *
     * @~chinese 
     * 停止搜索控制器。
     * 
     * @warning @~english The API only work on the IOS platform.Empty implementation on other platform.
     * @~chinese 此API只在IOS平台上工作。其他平台上为空实现。
     */
    static void stopDiscoveryController();


    /**@~english
     * Gets the name of this Controller object.
     * @~chinese 
     * 获取这个控制器对象的名称。
     * @return @~english The name of the Controller object.
     8 @~chinese 控制器对象的名称。
     */
    const std::string& getDeviceName() const { return _deviceName;}


    /**@~english
     * Gets the Controller id.
     * @~chinese 
     * 获取控制器对象id。
     * @return @~english The Controller id.
     * @~chinese 控制器对象id。
     */
    int getDeviceId() const { return _deviceId;}


    /**@~english
     * Indicates whether the Controller is connected.
     * @~chinese 
     * 指示控制器是否是连接状态。
     */
    bool isConnected() const;


    /** @~english 
     * Get key status by key code.
     * @~chinese
     * 通过按键code获取按键的状态。
     * @return @~english key status.
     * @~chinese 按键状态。
     */
    const KeyStatus& getKeyStatus(int keyCode);
    

    /** @~english
     * Activate receives key event from external key. e.g. back,menu.
     * Controller receives only standard key which contained within enum Key by default.
     *
     * @~chinese 
     * 激活从外部按键接收按键事件。例如,菜单。
     * 默认地，控制器只接收包含在enum Key中的标准key。
     * 
     * @warning @~english The API only work on the android platform for support diversified game controller.
     *
     * @~chinese 此API只支持android平台上多元化的游戏控制器。
     * 
     * @param externalKeyCode   @~english External key code.
     * @~chinese 外部按键代码。
     * @param receive   @~english True if external key event on this controller should be receive, false otherwise.
     * @~chinese 如果控制器应该收到外部按键事件则为真,否则假。
     */
    void receiveExternalKeyEvent(int externalKeyCode,bool receive);


    /** @~english
     * Changes the tag that is used to identify the controller easily.
     * @~chinese 
     * 更改标签,方便用于识别控制器。
     * @param tag   @~english A integer that identifies the controller.
     * @~chinese 一个标识控制器的整数。
     */
    void setTag(int tag) { _controllerTag = tag;}


    /**@~english
     * Returns a tag that is used to identify the controller easily.
     *
     * @~chinese 
     * 返回一个用于识别控制器的标识。
     * 
     * @return @~english An integer that identifies the controller.
     * @~chinese 一个标识控制器的整数。
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

// end group
/// @}

NS_CC_END

#endif /* defined(__cocos2d_libs__CCController__) */
