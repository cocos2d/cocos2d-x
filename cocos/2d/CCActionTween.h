/****************************************************************************
Copyright (c) 2009      lhunath (Maarten Billemont)
Copyright (c) 2010-2012 cocos2d-x.org
CopyRight (c) 2013-2014 Chukong Technologies Inc.
 
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
#ifndef __CCACTIONTWEEN_H__
#define __CCACTIONTWEEN_H__

#include "2d/CCActionInterval.h"

NS_CC_BEGIN

/**
 * @addtogroup actions
 * @{
 */

/**
@brief @~english The delegate class for ActionTween.
 * @~chinese ActionTween委托类。
@details @~english If you want to use ActionTween on a node.
        You should implement the node follow these steps:
        1. The node should be inherit from ActionTweenDelegate.
        2. Override the virtual method updateTweenAction in the node.

        Then once you running ActionTween on the node, the method updateTweenAction will be invoked.
 * @~chinese 如果你想在某个节点上使用ActionTween,
 * 你应该遵循以下步骤实现节点:
 * 1。节点应该继承自ActionTweenDelegate。
 * 2。在节点中重写虚方法updateTweenAction。
 * 
 * 一旦你在节点上运行ActionTween,updateTweenAction方法将会被调用。
*/
class CC_DLL ActionTweenDelegate
{
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ActionTweenDelegate() {}

    /**
    @brief @~english The callback function when ActionTween is running.
     * @~chinese ActionTween运行时的回调函数。
    @param value @~english The new value of the specified key.
     * @~chinese 指定键的新值。
    @param key @~english The key of property which should be updated.
     * @~chinese 应该被更新的键属性。
    */
    virtual void updateTweenAction(float value, const std::string& key) = 0;
};

/** @~english ActionTween

 ActionTween is an action that lets you update any property of an object.
 For example, if you want to modify the "width" property of a target from 200 to 300 in 2 seconds, then:

 * @~chinese ActionTween
 * 
 * ActionTween是一个让你可以更新对象的任意属性的动作。
 * 例如,如果您想要在2秒内修改的“宽度”属性值，从200到300，可以这么做:
 * 
 @code
     auto modifyWidth = ActionTween::create(2, "width", 200, 300);
     target->runAction(modifyWidth);
 @endcode

 @~english Another example: ScaleTo action could be rewritten using PropertyAction:
 @~chinese 另一个例子：使用PropertyAction可以重写ScaleTo运动

 @code
     // scaleA and scaleB are equivalents
     auto scaleA = ScaleTo::create(2, 3);                 // (duration, to)
     auto scaleB = ActionTween::create(2, "scale", 1, 3); // (duration, key, from, to)
 @endcode

 @since v0.99.2
 */
class CC_DLL ActionTween : public ActionInterval
{
public:
    /** 
     * @brief @~english Create and initializes the action with the property name (key), and the from and to parameters.
     * @~chinese 使用属性名称(键值)和起始起始参数来创建和初始化运动。
     * @param duration @~english The duration of the ActionTween. It's a value in seconds.
     * @~chinese ActionTween的持续时间。这是一个以秒为单位的值。
     * @param key @~english The key of property which should be updated.
     * @~chinese 应该被更新属性键。
     * @param from @~english The value of the specified property when the action begin.
     * @~chinese 运动开始时指定属性的值。
     * @param to @~english The value of the specified property when the action end.
     * @~chinese 运动结束时指定属性的值。
     * @return @~english If the creation success, return a pointer of ActionTween; otherwise, return nil.
     * @~chinese 如果创建成功,返回一个指向ActionTween的指针;否则,返回空。
     */
    static ActionTween* create(float duration, const std::string& key, float from, float to);

    // Overrides
    void startWithTarget(Node *target) override;
    void update(float dt) override;
    ActionTween* reverse() const override;
	ActionTween *clone() const override;
    
CC_CONSTRUCTOR_ACCESS:
    /** 
     * @brief @~english Initializes the action with the property name (key), and the from and to parameters.
     * @~chinese 使用属性名称(键值)和起始起始参数来初始化运动。
     * @param duration @~english The duration of the ActionTween. It's a value in seconds.
     * @~chinese ActionTween的持续时间。这是一个以秒为单位的值。
     * @param key @~english The key of property which should be updated.
     * @~chinese 应该被更新属性键。
     * @param from @~english The value of the specified property when the action begin.
     * @~chinese 运动开始时指定属性的值。
     * @param to @~english The value of the specified property when the action end.
     * @~chinese 运动结束时指定属性的值。
     * @return @~english If the initialization success, return true; otherwise, return false.
     * @~chinese 如果初始化成功,返回true,否则返回false。
     */
    bool initWithDuration(float duration, const std::string& key, float from, float to);

protected:
    std::string       _key;
    float            _from, _to;
    float            _delta;
};

// end of actions group
/// @}

NS_CC_END

#endif /* __CCACTIONTWEEN_H__ */


