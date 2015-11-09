/****************************************************************************
Copyright (C) 2010      Lam Pham
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
#ifndef __ACTION_CCPROGRESS_TIMER_H__
#define __ACTION_CCPROGRESS_TIMER_H__

#include "2d/CCActionInterval.h"

NS_CC_BEGIN

/**
 * @addtogroup actions
 * @{
 */

/**
@brief @~english Progress to percentage.
 * @~chinese 百分比进度条。
@details @~english This action show the target node from current percentage to the specified percentage.
        You should specify the destination percentage when creating the action.
 * @~chinese 这一动作显示了目标节点从当前百分比到指定的百分比。
 * 你应该在创建动作的时候指定目标百分比。
@since v0.99.1
*/
class CC_DLL ProgressTo : public ActionInterval
{
public:
    /** 
     * @brief @~english Create and initializes with a duration and a destination percentage.
     * @~chinese 使用持续时间和目标百分比来创建和初始化。
     * @param duration @~english Specify the duration of the ProgressTo action. It's a value in seconds.
     * @~chinese 指定ProgressTo动作的持续时间。这是一个以秒为单位的值。
     * @param percent @~english Specify the destination percentage.
     * @~chinese 指定目标百分比。
     * @return @~english If the creation sucess, return a pointer of ProgressTo action; otherwise, return nil.
     * @~chinese 如果创建成功,返回一个ProgressTo动作的指针;否则,返回空。
     */
    static ProgressTo* create(float duration, float percent);

    //
    // Overrides
    //
	virtual ProgressTo* clone() const override;
	virtual ProgressTo* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    ProgressTo() {}
    virtual ~ProgressTo() {}

    /** 
     * @brief @~english Initializes with a duration and destination percentage. 
     * @~chinese 使用持续时间和目标百分比来初始化。
     * @param duration @~english Specify the duration of the ProgressTo action. It's a value in seconds.
     * @~chinese 指定ProgressTo动作的持续时间。这是一个以秒为单位的值。
     * @param percent @~english Specify the destination percentage.
     * @~chinese 指定目标百分比。
     * @return @~english If the creation sucess, return true; otherwise, return false.
     * @~chinese 如果创建成功,返回true,否则返回false。
     */
    bool initWithDuration(float duration, float percent);

protected:
    float _to;
    float _from;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ProgressTo);
};

/**
@brief @~english Progress from a percentage to another percentage.
 * @~chinese 从一个百分比到另一个百分比的进度。
@since v0.99.1
*/
class CC_DLL ProgressFromTo : public ActionInterval
{
public:
    /** 
     * @brief @~english Create and initializes the action with a duration, a "from" percentage and a "to" percentage.
     * @~chinese 使用持续时间，“开始百分比”和“结束百分比”来创建和初始化。
     * @param duration @~english Specify the duration of the ProgressFromTo action. It's a value in seconds.
     * @~chinese 指定ProgressFromTo动作的持续时间。这是一个以秒为单位的值。
     * @param fromPercentage @~english Specify the source percentage.
     * @~chinese 指定开始百分比。
     * @param toPercentage @~english Specify the destination percentage.
     * @~chinese 指定结束百分比。
     * @return @~english If the creation sucess, return a pointer of ProgressFromTo action; otherwise, return nil.
     * @~chinese 如果创建成功，返回一个ProgressFromTo动作的指针，否则返回false。
     */
    static ProgressFromTo* create(float duration, float fromPercentage, float toPercentage);

    //
    // Overrides
    //
	virtual ProgressFromTo* clone() const override;
	virtual ProgressFromTo* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    ProgressFromTo() {}
    virtual ~ProgressFromTo() {}

    /**
     * @brief @~english Initializes the action with a duration, a "from" percentage and a "to" percentage.
     * @~chinese 使用持续时间，“开始百分比”和“结束百分比”来初始化。
     * @param duration @~english Specify the duration of the ProgressFromTo action. It's a value in seconds.
     * @~chinese 指定ProgressFromTo动作的持续时间。这是一个以秒为单位的值。
     * @param fromPercentage @~english Specify the source percentage.
     * @~chinese 指定开始百分比。
     * @param toPercentage @~english Specify the destination percentage.
     * @~chinese 指定结束百分比。
     * @return @~english If the creation sucess, return true; otherwise, return false.
     * @~chinese 如果创建成功,返回true,否则返回false。
     */
    bool initWithDuration(float duration, float fromPercentage, float toPercentage);

protected:
    float _to;
    float _from;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ProgressFromTo);
};

// end of actions group
/// @}

NS_CC_END

#endif // __ACTION_CCPROGRESS_TIMER_H__
