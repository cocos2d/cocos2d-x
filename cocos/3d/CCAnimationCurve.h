/****************************************************************************
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
#ifndef __CCANIMATIONCURVE_H__
#define __CCANIMATIONCURVE_H__

#include <functional>

#include "platform/CCPlatformMacros.h"
#include "base/CCRef.h"
#include "math/CCMath.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#undef NEAR
#endif

NS_CC_BEGIN

/**
 * @addtogroup _3d
 * @{
 */

/**
 * @enum Evaluate Type
 * @brief @~english The evalute type for the curve evaluation(interpolation).
 * @~chinese 曲线求解(插值)类型
 */
enum class EvaluateType
{
    /**
     * linear interpolation
     * @~chinese 简单线性插值
     **/
    INT_LINEAR, 
    /**
     * Nearest neighbor interpolation
     * @~chinese 最近点插值
     */
    INT_NEAR,
    /**
     * Quaternion spherical linear interpolation
     * @~chinese 球面线性插值(slerp)
     **/
    INT_QUAT_SLERP,
    /**
     * User defined interpolation.
     * @~chinese 用户自定义插值方法
     */
    INT_USER_FUNCTION,
};

/**
 * @class AnimationCurve
 * @brief @~english Curve of bone's position, rotation or scale
 * @~chinese 骨骼曲线，用以表示骨骼动画中平移、旋转或者是缩放的曲线
 * @lua NA
 */
template <int componentSize>
class AnimationCurve: public Ref
{
public:
    
    /**
     * @~english Create animation curve.
     * @~chinese 创建动画的曲线
     * @param @~english Keytime the key time value.
     * @~chinese 每个关键帧对应的时间点数组
     * @param value @~english The value.
     * @~chinese 每个关键帧时曲线的值的数组
     * @~chinese 关键帧数组大小
     **/
    static AnimationCurve* create(float* keytime, float* value, int count);
    
    /**
     * @~english Evalute value of time
     * @~chinese 求解（插值）给定时间时的曲线的值
     * @param time @~english Time to be estimated
     * @~chinese 给定的时间点
     * @param dst @~english Estimated value of that time
     * @~chinese 该点时间求解出的估算值的指针
     * @param type @~english EvaluateType
     * @~chinese 求解时的方法类型
     */
    void evaluate(float time, float* dst, EvaluateType type) const;
    
    /**
     * @~english Set evaluate function, allow the user use own function.
     * @~chinese 设置求解（插值）函数，允许用户使用自己的插值函数
     * @param fun @~english The callback function
     * @~chinese 插值的用户回调函数
     */
    void setEvaluateFun(std::function<void(float time, float* dst)> fun);
    
    /**
     * @~english Get start time
     * @~chinese 获取起始时间
     * @return @~english The start time
     * @~chinese 起始时间
     */
    float getStartTime() const;
    
    /**
     * @~english Get the end time.
     * @~chinese 获取结束时间
     * @return @~english The end time.
     * @~chinese 结束时间
     */
    float getEndTime() const;
    
CC_CONSTRUCTOR_ACCESS:

    /**
     * Constructor
     */
    AnimationCurve();

    /**
     * Destructor
     */
    virtual ~AnimationCurve();
    
    /**
     * @~english Determine index by time.
     * @~chinese 获取给定时间点的关键帧索引
     * @param time @~english The specified time
     * @~chinese 给定的某一时间点
     * @return @~english The index.
     * @~chinese 关键帧索引
     */
    int determineIndex(float time) const;
    
protected:
    
    float* _value;   //
    float* _keytime; //key time(0 - 1), start time _keytime[0], end time _keytime[_count - 1]
    int _count;
    int _componentSizeByte; //component size in byte, position and scale 3 * sizeof(float), rotation 4 * sizeof(float)
    
    std::function<void(float time, float* dst)> _evaluateFun; //user defined function
};

// end of 3d group
/// @}

NS_CC_END

#include "CCAnimationCurve.inl"

#endif
