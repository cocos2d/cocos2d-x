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

class CC_DLL ActionTweenDelegate
{
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ActionTweenDelegate() {}
    virtual void updateTweenAction(float value, const std::string& key) = 0;
};

/** ActionTween

 ActionTween 是一个可以让你更新的某个对象(Object)属性的动作.
 例如, 如果你想要让某个目标对象(target)的宽度属性(width)在2秒内从200变成300, 代码可以这样写: 
 
 @code
     auto modifyWidth = ActionTween::create(2, "width", 200, 300);
     target->runAction(modifyWidth);
 @endcode

 再一个例子: ScaleTo 动作(一个改变对象大小的动作)可以通过 ActionTween 重写.
 注: 原注释中 ActionTween 为 PropertyAction, 但 PropertyAction 在整个cocos2d-x中仅在此处注释中
 出现了一次, 个人翻译为ActionTween.
 
 @code
     // scaleA 和 scaleB 是等价的动作实现
     // 以下两行注释为相应动作的构造参数说明, 不翻译. 
     auto scaleA = ScaleTo::create(2, 3);                 // (duration, to)
     auto scaleB = ActionTween::create(2, "scale", 1, 3); // (duration, key, from, to)
 @endcode

 @since v0.99.2
 */
class CC_DLL ActionTween : public ActionInterval
{
public:
    /** 用持续时间(duration), 属性名称(key), from 和 to 参数创建并初始化动作(指ActionTween).
    */
    static ActionTween* create(float duration, const std::string& key, float from, float to);

    // 重写的四个方法.
    void startWithTarget(Node *target) override;
    void update(float dt) override;
    ActionTween* reverse() const override;
	ActionTween *clone() const override;
    
CC_CONSTRUCTOR_ACCESS:
    /** 用持续时间(duration), 属性名称(key), from 和 to 参数初始化动作(指ActionTween). */
    bool initWithDuration(float duration, const std::string& key, float from, float to);

protected:
    std::string        _key;
    float            _from, _to;
    float            _delta;
};

// end of actions group
/// @}

NS_CC_END

#endif /* __CCACTIONTWEEN_H__ */


