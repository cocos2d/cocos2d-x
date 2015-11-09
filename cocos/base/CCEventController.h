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

#ifndef __cocos2d_libs__EventController__
#define __cocos2d_libs__EventController__

#include "platform/CCPlatformMacros.h"
#include "base/CCEvent.h"

/**
 * @addtogroup base
 * @{
 */

NS_CC_BEGIN

/// @cond EventController
class Controller;
class EventListenerController;

/** @class EventController
 * @brief @~english Controller event.
 * @~chinese 事件控制器。
 */
class EventController : public Event
{
public:
    /** @~english ControllerEventType Controller event type. @~chinese 事件控制器类型。*/
    enum class ControllerEventType
    {
        CONNECTION,
        BUTTON_STATUS_CHANGED,
        AXIS_STATUS_CHANGED,
    };
    
    /** @~english Create a EventController with controller event type, contrlloer and key code.
     *
     * @~chinese 根据事件类型,控制器对象和事件码，创建一个事件控制器
     * 
     * @param type @~english A given controller event type.
     * @~chinese 一个给定控制器事件类型。
     * @param controller @~english A given controller pointer.
     * @~chinese 一个给定控制器指针。
     * @param keyCode @~english A given key code.
     * @~chinese 一个给定的事件码。
     * @return @~english An autoreleased EventController object.
     * @~chinese 一个自动释放的事件控制器对象。
     */
	EventController(ControllerEventType type, Controller* controller, int keyCode);
    /** @~english Create a EventController with controller event type, contrlloer and whether or not is connected.
     *
     * @~chinese 根据事件类型、控制器对象和是否已连接，创建一个事件控制器
     * 
     * @param type @~english A given controller event type.
     * @~chinese 一个给定控制器事件类型。
     * @param controller @~english A given controller pointer.
     * @~chinese 一个给定控制器指针。
     * @param isConnected @~english True if it is connected.
     * @~chinese 是否已连接。
     * @return @~english An autoreleased EventController object.
     * @~chinese 一个自动释放的事件控制器对象。
     */
    EventController(ControllerEventType type, Controller* controller, bool isConnected);

    /** @~english Gets the event type of the controller.
     *
     * @~chinese 获取控制器的事件类型。
     * 
     * @return @~english The event type of the controller.
     * @~chinese 返回控制器的事件类型。
     */
    ControllerEventType getControllerEventType() const { return _controllerEventType; }
    Controller* getController() const { return _controller; }

    /** @~english Gets the key code of the controller.
     *
     * @~chinese 获取控制器的事件码。
     * 
     * @return @~english The key code of the controller.
     * @~chinese 返回控制器的事件码。
     */
    int getKeyCode() const{ return _keyCode; }
    void setKeyCode(int keyCode) { _keyCode = keyCode;}

    /** @~english Sets the connect status.
     *
     * @~chinese 设置连接状态。
     * 
     * @param True @~english if it's connected.
     * @~chinese 如果已连接值设置为true。
     */
    void setConnectStatus(bool isConnected) {_isConnected = isConnected;}
    /** @~english Gets the connect status.
     *
     * @~chinese 获取连接状态。
     * 
     * @return @~english True if it's connected.
     * @~chinese 如果已连接值设置为true。
     */
    bool isConnected() const { return _isConnected; }
    
protected:
    ControllerEventType _controllerEventType;
    Controller* _controller;
    int _keyCode;
    bool _isConnected;

    friend class EventListenerController;
};
/// @endcond EventController
NS_CC_END

// end of base group
/// @}

#endif /* defined(__cocos2d_libs__EventController__) */
