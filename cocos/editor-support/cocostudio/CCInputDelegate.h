/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#ifndef __CC_EXTENTIONS_CCINPUTDELEGATE_H__
#define __CC_EXTENTIONS_CCINPUTDELEGATE_H__

#include "platform/CCPlatformMacros.h"
#include "base/CCTouch.h"
#include "base/CCEvent.h"
#include "base/ccTypes.h"
#include "base/CCEventKeyboard.h"
#include "base/CCEventListener.h"
#include "cocostudio/CocosStudioExport.h"

namespace cocos2d {
    class __Set;
}

namespace cocostudio {

/**
 *  @lua NA
 */
 /** 
 @类名 InputDelegate
 @主题 逻辑组件获取输入接口辅助类
 @细节 定义获取输入接口，被逻辑组件继承重载，从而方便逻辑组件获取输入。
 @组 组件
 */
/** 
 * @class InputDelegate
 * @brief @~english InputDelegate.
 * @~chinese 输入代理。
 * @details @~english 
 * @~chinese 定义获取输入接口，被逻辑组件继承重载，从而方便逻辑组件获取输入。
 *  @lua NA.
*/
class CC_STUDIO_DLL InputDelegate
{
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    InputDelegate(void);
    /**
     * @js NA
     */
    virtual ~InputDelegate(void);
    
public:
    /**
    @主题 触摸是否可用
    @返回 true 可以接收到触摸事件 否则接受不到
    */
    virtual bool isTouchEnabled() const;
    /**
    @主题 设置触摸可用
    @参数 value true 开启触摸事件接收否则不开启
    @返回 无
    */
    virtual void setTouchEnabled(bool value);
    /**
    @主题 加速计是否可用
    @返回 true 可以接收到加速计事件 否则接受不到
    */
    virtual bool isAccelerometerEnabled() const;
    /**
    @主题 设置加速计可用
    @参数 value true 开启加速计事件接收否则不开启
    @返回 无
    */
    virtual void setAccelerometerEnabled(bool value);
    /**
    @主题 键盘是否可用
    @返回 true 可以接收到加速计事件 否则接受不到
    */
    virtual bool isKeypadEnabled() const;
    /**
    @主题 设置键盘可用
    @参数 value true 开启键盘事件接收否则不开启
    @返回 无
    */
    virtual void setKeypadEnabled(bool value);
    /**
    @主题 设置触摸事件接收类型
    @参数 mode ALL_AT_ONCE 多个触摸事件一次接收  ONE_BY_ONE 多个触摸时间一个接着一个接收
    @返回 无
    */
    virtual void setTouchMode(cocos2d::Touch::DispatchMode mode);
    /**
    @主题 获取触摸事件接收类型
    @返回 ALL_AT_ONCE 多个触摸事件一次接收  ONE_BY_ONE 多个触摸时间一个接着一个接收
    */
    virtual cocos2d::Touch::DispatchMode getTouchMode() const;
    /**
    @主题 设置触摸事件接收优先级
    @参数 priority 优先级数值
    @返回 无
    */
    virtual void setTouchPriority(int priority);
    /**
    @主题 获取触摸事件接收优先级
    @返回 触摸事件接收优先级数值
    */
    virtual int  getTouchPriority() const;
 /** @deprecated Please override onAcceleration */
    /**
     * @js NA
     */
    /**
    @主题 cocos2d-x 2.x 接收加速计虚函数，3.x不建议使用此接口
    @参数 accelerationValue 加速计所产生的数据
    @返回 无
    */
    CC_DEPRECATED_ATTRIBUTE virtual void didAccelerate(cocos2d::Acceleration* accelerationValue) final { CC_UNUSED_PARAM(accelerationValue); };
    // Deprecated touch callbacks.
    /**
     * @js NA
     */
     /**
    @主题 cocos2d-x 2.x 接收触摸开始虚函数，3.x不建议使用此接口
    @参数 pTouch 触摸所产生的数据 
    @参数 pEvent 事件类型 
    @返回 无
    */
    CC_DEPRECATED_ATTRIBUTE virtual bool ccTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) final {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent); return false;};
    /**
     * @js NA
     */
   /**
    @主题 cocos2d-x 2.x 接收触摸滑动虚函数，3.x不建议使用此接口
    @参数 pTouch 触摸所产生的数据 
    @参数 pEvent 事件类型 
    @返回 无
    */
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) final {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
    /**
     * @js NA
     */
   /**
    @主题 cocos2d-x 2.x 接收触摸停止虚函数，3.x不建议使用此接口
    @参数 pTouch 触摸所产生的数据 
    @参数 pEvent 事件类型 
    @返回 无
    */
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) final {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
    /**
     * @js NA
     */
    /**
    @主题 cocos2d-x 2.x 接收触摸取消虚函数，3.x不建议使用此接口
    @参数 pTouch 触摸所产生的数据 
    @参数 pEvent 事件类型 
    @返回 无
    */
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) final {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
    /**
     * @js NA
     */
    /**
    @主题 cocos2d-x 2.x 接收多点触摸开始虚函数，3.x不建议使用此接口
    @参数 pTouch 触摸所产生的数据 
    @参数 pEvent 事件类型 
    @返回 无
    */
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchesBegan(cocos2d::__Set *pTouches, cocos2d::Event *pEvent) final {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
    /**
     * @js NA
     */
    /**
    @主题 cocos2d-x 2.x 接收多点触摸滑动虚函数，3.x不建议使用此接口
    @参数 pTouch 触摸所产生的数据 
    @参数 pEvent 事件类型 
    @返回 无
    */
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchesMoved(cocos2d::__Set *pTouches, cocos2d::Event *pEvent) final {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
    /**
     * @js NA
     */
    /**
    @主题 cocos2d-x 2.x 接收多点触摸结束虚函数，3.x不建议使用此接口
    @参数 pTouch 触摸所产生的数据 
    @参数 pEvent 事件类型 
    @返回 无
    */
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchesEnded(cocos2d::__Set *pTouches, cocos2d::Event *pEvent) final {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
    /**
     * @js NA
     */
    /**
    @主题 cocos2d-x 2.x 接收多点触摸取消虚函数，3.x不建议使用此接口
    @参数 pTouch 触摸所产生的数据 
    @参数 pEvent 事件类型 
    @返回 无
    */
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchesCancelled(cocos2d::__Set *pTouches, cocos2d::Event *pEvent) final {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
    /**
     * @js NA
     */
    /**
    @主题 cocos2d-x 3.x 接收加速计虚函数
    @参数 acc 加速计所产生的数据
    @参数 pEvent 事件类型 
    @返回 无
    */
    virtual void onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* event) {};
    /**
     * @js NA
     */
    /**
    @主题 cocos2d-x 3.x 接收键盘按下虚函数
    @参数 keyCode 按下按键
    @参数 pEvent 事件类型 
    @返回 无
    */
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {};
    /**
     * @js NA
     */
    /**
    @主题 cocos2d-x 3.x 接收键盘抬起虚函数
    @参数 keyCode 抬起按键
    @参数 pEvent 事件类型 
    @返回 无
    */
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {};
    /**
     * @js NA
     */
    /**
    @主题 cocos2d-x 3.x 接收触摸开始虚函数
    @参数 touch 触摸所产生的数据
    @参数 pEvent 事件类型 
    @返回 无
    */
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    /**
     * @js NA
     */
    /**
    @主题 cocos2d-x 3.x 接收触摸滑动虚函数
    @参数 touch 触摸所产生的数据
    @参数 pEvent 事件类型 
    @返回 无
    */
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    /**
     * @js NA
     */
    /**
    @主题 cocos2d-x 3.x 接收触摸结束虚函数
    @参数 touch 触摸所产生的数据
    @参数 pEvent 事件类型 
    @返回 无
    */
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    /**
     * @js NA
     */
    /**
    @主题 cocos2d-x 3.x 接收触摸取消虚函数
    @参数 touch 触摸所产生的数据
    @参数 pEvent 事件类型 
    @返回 无
    */
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);
    /**
     * @js NA
     */
    /**
    @主题 cocos2d-x 3.x 接收多点触摸开始虚函数
    @参数 touch 触摸所产生的数据
    @参数 pEvent 事件类型 
    @返回 无
    */
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    /**
     * @js NA
     */
    /**
    @主题 cocos2d-x 3.x 接收多点触摸滑动虚函数
    @参数 touch 触摸所产生的数据
    @参数 pEvent 事件类型 
    @返回 无
    */
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    /**
     * @js NA
     */
    /**
    @主题 cocos2d-x 3.x 接收多点触摸结束虚函数
    @参数 touch 触摸所产生的数据
    @参数 pEvent 事件类型 
    @返回 无
    */
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    /**
     * @js NA
     */
    /**
    @主题 cocos2d-x 3.x 接收多点触摸取消虚函数
    @参数 touch 触摸所产生的数据
    @参数 pEvent 事件类型 
    @返回 无
    */
    virtual void onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);

protected:   
    bool _touchEnabled;
    cocos2d::EventListener* _touchListener;
    bool _accelerometerEnabled;
    cocos2d::EventListener*  _accelerometerListener;
    bool _keypadEnabled;
    cocos2d::EventListener*  _keyboardListener;
private:
     int _touchPriority;
    cocos2d::Touch::DispatchMode _touchMode;
};

}

#endif  // __FUNDATION__CCCOMPONENT_H__
