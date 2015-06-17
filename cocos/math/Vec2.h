/**
 Copyright 2013 BlackBerry Inc.
 Copyright (c) 2014-2015 Chukong Technologies

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.

 Original file from GamePlay3D: http://gameplay3d.org

 This file was modified to fit the cocos2d-x project
 */

#ifndef MATH_VEC2_H
#define MATH_VEC2_H

#include <algorithm>
#include <functional>
#include <math.h>
#include "math/CCMathBase.h"

/**
 * @addtogroup base
 * @{
 */

NS_CC_MATH_BEGIN

/** @~english Clamp a value between from and to.
 * @~chinese 基于给定的限制范围计算给定数值的限制值，最终数值将在[min_inclusive, max_inclusive]区间内。
 *
 * @param value @~english A value to clamp. @~chinese 要限制的值。
 * @param min_inclusive @~english The specified minimum range. @~chinese 限制范围下限。
 * @param max_inclusive @~english The specified maximum range. @~chinese 限制范围上限。
 *
 * @return @~english The clamped value for the value parameter.@~chinese 参数value的限制值。
 */

inline float clampf(float value, float min_inclusive, float max_inclusive)
{
    if (min_inclusive > max_inclusive) {
        std::swap(min_inclusive, max_inclusive);
    }
    return value < min_inclusive ? min_inclusive : (value < max_inclusive? value : max_inclusive);
}

class Mat4;

/** @~english Defines a 2-element floating point vector.
 * @~chinese 定义了一个二维浮点向量。
 */
class CC_DLL Vec2
{
public:

    /** @~english The x coordinate.
     * @~chinese x坐标。
     */
    float x;

    /** @~english The y coordinate.
     * @~chinese y坐标。
     */
    float y;

    /** 
     * @~english Constructs a new vector initialized to all zeros.
     * @~chinese 构造一个新的向量，所有成员属性初始化为零。
     */
    Vec2();

    /** 
     * @~english Constructs a new vector initialized to the specified values.
     * @~chinese 构造一个新的向量，并初始化成员属性为指定的值。
     * 
     * @param xx @~english The x coordinate. @~chinese x坐标。
     * @param yy @~english The y coordinate. @~chinese y坐标。
     */
    Vec2(float xx, float yy);

    /**
     * @~english Constructs a new vector from the values in the specified array.
     * @~chinese 用给定数组中的值构造一个新的向量。
     * 
     * @param array @~english An array containing the elements of the vector in the order x, y.
     * @~chinese 一个依次包含x，y分量的数组。
     */
    Vec2(const float* array);

    /**
     * @~english Constructs a vector that describes the direction between the specified points.
     * @~chinese 构造一个点p1指向点p2的向量。
     * 
     * @param p1 @~english The first point. @~chinese 第一点。
     * @param p2 @~english The second point. @~chinese 第二点。
     */
    Vec2(const Vec2& p1, const Vec2& p2);

    /**
     * @~english Constructs a new vector that is a copy of the specified vector.
     * @~chinese 拷贝构造函数。
     * 
     * @param copy @~english The vector to copy. @~chinese 被拷贝的向量。
     */
    Vec2(const Vec2& copy);

    /** @~english Destructor. @~chinese 析构函数。*/
    ~Vec2();

    /** 
     * @~english Indicates whether this vector contains all zeros.
     * @~chinese 向量的所有分量值是否均为0.0f。
     * 
     * @return @~english true if this vector contains all zeros, false otherwise.
     * @~chinese 如果向量的所有分量值都为0.0f则返回true，否则返回false。
     */
    inline bool isZero() const;

    /**
     * @~english Indicates whether this vector contains all ones.
     * @~chinese 向量的所有分量值是否均为1.0f。
     * 
     * @return @~english true if this vector contains all ones, false otherwise.
     * @~chinese 如果向量的所有分量值均为1.0f，则返回true，否则返回false。
     */
    inline bool isOne() const;

    /**
     * @~english Returns the angle (in radians) between the specified vectors.
     * @~chinese 返回给定的两个向量之间的角度(弧度)。
     * 
     * @param v1 @~english The first vector. @~chinese 第一个向量。
     * @param v2 @~english The second vector. @~chinese 第二个向量。
     *
     * @return @~english The angle between the two vectors (in radians).
     * @~chinese 两个向量之间的角度(弧度)。
     */
    static float angle(const Vec2& v1, const Vec2& v2);

    /**
     * @~english Adds the elements of the specified vector to this one.
     * @~chinese 将指定向量的值添加给这个向量。
     * 
     * @param v @~english The vector to add. @~chinese 添加的向量。
     */
    inline void add(const Vec2& v);

    /**
     * @~english Adds the specified vectors and stores the result in dst.
     * @~chinese 将给定向量v1和向量v2相加，结果保存到向量dst。 
     * 
     * @param v1 @~english The first vector. @~chinese 第一个向量。
     * @param v2 @~english The second vector. @~chinese 第二个向量。
     * @param dst @~english A vector to store the result in. @~chinese 用以保存结果的向量。
     */
    static void add(const Vec2& v1, const Vec2& v2, Vec2* dst);

    /**
     * @~english Clamps this vector within the specified range.
     * @~chinese 将向量值限制在指定区间内。
     * 
     * @param min @~english The minimum value. @~chinese 最小值。 
     * @param max @~english The maximum value. @~chinese 最大值。 
     */
    void clamp(const Vec2& min, const Vec2& max);

    /**
     * @~english Clamps the specified vector within the specified range and returns it in dst.
     * @~chinese 将指定向量v限制在[min,max]区间内，并用dst保存结果。
     * 
     * @param v @~english The vector to clamp. @~chinese 将被限定的向量。
     * @param min @~english The minimum value. @~chinese 最小值。
     * @param max @~english The maximum value. @~chinese 最大值。
     * @param dst @~english A vector to store the result in. @~chinese 一个用以保存结果的向量。
     */
    static void clamp(const Vec2& v, const Vec2& min, const Vec2& max, Vec2* dst);

    /**
     * @~english Returns the distance between this point and v.
     * @~chinese 返回这个点与目标点的距离。
     * 
     * @param v @~english The other point. @~chinese 另一个点。
     * 
     * @return @~english The distance between this point and v.
     * @~chinese 这个点与目标点v的距离。
     * 
     * @see distanceSquared
     */
    float distance(const Vec2& v) const;

    /** @~english
     * Returns the squared distance between this point and v.
     *
     * When it is not necessary to get the exact distance between
     * two points (for example, when simply comparing the
     * distance between different points), it is advised to use
     * this method instead of distance.
     *
     * @~chinese 返回本这个点与目标点v的距离的平方。
     * 如果不需要得到两个点之间的准确距离， 例如只是比较两点之间的距离大小的时候， 
     * 建议使用这个函数来代替distance函数。
     * 
     * @param v @~english The other point. @~chinese 另一个点。
     * 
     * @return @~english The squared distance between this point and v.
     * @~chinese 这个这个点与目标点v的距离的平方。
     * @see distance
     */
    inline float distanceSquared(const Vec2& v) const;

    /** 
     * @~english Returns the dot product of this vector and the specified vector.
     * @~chinese 返回本向量与指定向量v的点积
     * 
     * @param v @~english The vector to compute the dot product with.
     * @~chinese 用来计算点积的另一个向量
     * 
     * @return @~english The dot product. @~chinese 点积。
     */
    inline float dot(const Vec2& v) const;

    /**
     * @~english Returns the dot product between the specified vectors.
     * @~chinese 返回两个指定向量的点积。
     * 
     * @param v1 @~english The first vector. @~chinese 第一个向量。
     * @param v2 @~english The second vector. @~chinese 第二个向量。
     * 
     * @return @~english The dot product between the vectors. @~chinese 向量的点积。
     */
    static float dot(const Vec2& v1, const Vec2& v2);

    /**
     * @~english Computes the length of this vector.
     * @~chinese 计算这个向量的长度。
     * 
     * @return @~english The length of the vector. @~chinese 这个向量的长度。
     * @see lengthSquared
     */
    float length() const;

    /** @~english
     * Returns the squared length of this vector.
     *
     * When it is not necessary to get the exact length of a
     * vector (for example, when simply comparing the lengths of
     * different vectors), it is advised to use this method
     * instead of length.
     *
     * @~chinese 当不需要获取准确的向量长度时， 例如只是简单比较不同向量之间的长度大小， 
     * 可以使用本方法代替length。
     * 
     * @return @~english The squared length of the vector.
     * @~chinese 向量的长度的平方。
     * @see length
     */
    inline float lengthSquared() const;

    /** @~english Negates this vector. @~chinese 向量求负。*/
    inline void negate();

    /** @~english
     * Normalizes this vector.
     *
     * This method normalizes this Vec2 so that it is of
     * unit length (in other words, the length of the vector
     * after calling this method will be 1.0f). If the vector
     * already has unit length or if the length of the vector
     * is zero, this method does nothing.
     * 
     * @~chinese 
     * 使这个向量归一化为单位长度（调用这个方法后向量长度为1.0f）。 
     * 如果向量已经是单位长度或者长度为零， 这个方法不起任何作用。
     */
    void normalize();

    /** @~english Get the normalized vector. @~chinese 得到归一化向量。*/
    Vec2 getNormalized() const;

    /** 
     * @~english Scales all elements of this vector by the specified value.
     * @~chinese 用指定的缩放系数对向量的各分量进行缩放。
     * 
     * @param scalar @~english The scalar value. @~chinese 缩放系数。
     */
    inline void scale(float scalar);

    /** @~english
     * Scales each element of this vector by the matching component of scale.
     *
     * @~chinese 
     * 用scale向量的x分量来缩放本向量的x分量，用scale向量的y分量来缩放本向量的y分量。
     * 
     * @param scale @~english The vector to scale by. @~chinese 缩放因子。 
     */
    inline void scale(const Vec2& scale);

    /** 
     * @~english Rotates this vector by angle (specified in radians) around the given point.
     * @~chinese 向量绕指定点point旋转angle度，其中angle的单位为弧度
     * 
     * @param point @~english The point to rotate around. @~chinese 旋转锚点。
     * @param angle @~english The angle to rotate by (in radians). @~chinese 旋转角度(单位：弧度)。 
     */
    void rotate(const Vec2& point, float angle);

    /**
     * @~english Sets the elements of this vector to the specified values.
     * @~chinese 设置向量的分量值为指定值。
     * 
     * @param xx @~english The new x coordinate. @~chinese 新的x坐标。 
     * @param yy @~english The new y coordinate. @~chinese 新的y坐标。
     */
    inline void set(float xx, float yy);

    /**
     * @~english Sets the elements of this vector from the values in the specified array.
     * @~chinese 设置这个向量的分量为指定数组中的值。
     * 
     * @param array @~english An array containing the elements of the vector in the order x, y.
     * @~chinese 一个依次包含x，y分量的数组。
     */
    void set(const float* array);

    /**
     * @~english Sets the elements of this vector to those in the specified vector.
     * @~chinese 将指定向量的各分量值设置给本向量。
     * 
     * @param v @~english The vector to copy. @~chinese 被拷贝的向量。
     */
    inline void set(const Vec2& v);

    /**
     * @~english Sets this vector to the directional vector between the specified points.
     * @~chinese 设置向量值为两个指定点之间的向量。
     * 
     * @param p1 @~english The first point. @~chinese 第一点。
     * @param p2 @~english The second point. @~chinese 第二点。
     */
    inline void set(const Vec2& p1, const Vec2& p2);

    /**
     * @~english Sets the elements of this vector to zero.
     * @~chinese 这个向量的各分量设置为零。
     */
    inline void setZero();

    /** @~english
     * Subtracts this vector and the specified vector as (this - v)
     * and stores the result in this vector.
     *
     * @~chinese 将本向量的各分量减指定向量的对应分量值并保存。
     * 
     * @param v @~english The vector to subtract.
     * @~chinese 用于减去的向量。
     */
    inline void subtract(const Vec2& v);

    /**@~english
     * Subtracts the specified vectors and stores the result in dst.
     * The resulting vector is computed as (v1 - v2).
     *
     * @~chinese 
     * 计算向量v1减去v2，把结果保存在向量dst
     * 
     * @param v1 @~english The first vector.
     * @~chinese 第一个向量。
     * @param v2 @~english The second vector.
     * @~chinese 第二个向量。
     * @param dst @~english The destination vector.
     * @~chinese 向量差。
     */
    static void subtract(const Vec2& v1, const Vec2& v2, Vec2* dst);

    /** @~english
     * Updates this vector towards the given target using a smoothing function.
     * The given response time determines the amount of smoothing (lag). A longer
     * response time yields a smoother result and more lag. To force this vector to
     * follow the target closely, provide a response time that is very small relative
     * to the given elapsed time.
     *
     * @~chinese 
     * 平滑更新向量的当前位置，指向目标向量。
     * responseTime定义了平滑时间量，该值越大结果越平滑， 相应的延迟时间越长。
     * 如果希望向量紧跟target向量， 提供一个相对elapsedTime小很多的responseTime值即可。
     * 
     * @param target @~english target value.
     * @~chinese 目标向量。
     * @param elapsedTime @~english elapsed time between calls.
     * @~chinese 消逝时间。
     * @param responseTime @~english response time (in the same units as elapsedTime).
     * @~chinese 响应时间(时间单位和elapsedTime一致)。
     */
    inline void smooth(const Vec2& target, float elapsedTime, float responseTime);

    /** @~english
     * Calculates the sum of this vector with the given vector.
     * Note: this does not modify this vector.
     * 
     * @~chinese 向量加法，求向量与给定向量v的和
     * 注意:这并不修改原向量的值。
     * 
     * @param v @~english The vector to add. @~chinese 被加的向量。
     * @return @~english The vector sum. @~chinese 向量和。 
     */
    inline const Vec2 operator+(const Vec2& v) const;

    /**
     * @~english Adds the given vector to this vector.
     * @~chinese 向量加法，求向量与给定向量v的和，将结果保存在该向量中并返回。
     * 
     * @param v @~english The vector to add. @~chinese 被加的向量。
     * 
     * @return @~english This vector, after the addition occurs.
     * @~chinese 向量和。
     */
    inline Vec2& operator+=(const Vec2& v);

    /**
     * @~english Calculates the difference of this vector with the given vector.
     * Note: this does not modify this vector.
     * @~chinese 向量减法，求向量与给定向量v的差
     * 注意:这并不修改原向量的值。
     * 
     * @param v @~english The vector to minus. @~chinese 用于减去的向量。
     *
     * @return @~english The vector difference. @~chinese 结果向量。
     */
    inline const Vec2 operator-(const Vec2& v) const;

    /**
     * @~english Subtracts the given vector from this vector.
     * @~chinese 向量减法，求向量与给定向量v的差，将结果保存在该向量中并返回。
     * 
     * @param v @~english The vector to subtract. @~chinese 用于减去的向量。
     * 
     * @return @~english This vector, after the subtraction occurs. @~chinese 结果向量。
     */
    inline Vec2& operator-=(const Vec2& v);

    /**@~english
     * Calculates the negation of this vector.
     * Note: this does not modify this vector.
     * @~chinese 求负向量。
     * 注意:这并不修改原向量的值。
     * 
     * @return @~english The negation of this vector. @~chinese 负向量。
     */
    inline const Vec2 operator-() const;

    /** @~english
     * Calculates the scalar product of this vector with the given value.
     * Note: this does not modify this vector.
     * @~chinese 求向量与给定缩放系数的乘积。
     * 注意:这并不修改原向量的值。
     * 
     * @param s @~english The value to scale by. @~chinese 缩放系数。
     * 
     * @return @~english The scaled vector. @~chinese 缩放后的向量。
     */
    inline const Vec2 operator*(float s) const;

    /**@~english
     * Scales this vector by the given value. 
     * @~chinese  求向量与给定缩放系数的乘积，并将结果保存到本向量。
     * 
     * @param s @~english The value to scale by. @~chinese 缩放系数。
     * 
     * @return @~english This vector, after the scale occurs. @~chinese 缩放后的向量。
     */
    inline Vec2& operator*=(float s);
    
    /**@~english
     * Returns the components of this vector divided by the given constant
     * Note: this does not modify this vector.
     * @~chinese 求向量与给定除数的商。
     * 注意:这并不修改原向量的值。
     * 
     * @param s @~english the constant to divide this vector with
     * @~chinese 向量要除的常数。
     * @return @~english the result is this vector divided by the given constant.
     * @~chinese 除后的向量结果。
     */
    inline const Vec2 operator/(float s) const;

    /**
     * @~english Determines if this vector is less than the given vector.
     * @~chinese 判断该向量是否小于给定向量v。
     * 
     * @param v @~english The vector to compare against. @~chinese 要比较的向量。
     * 
     * @return @~english True if this vector is less than the given vector, false otherwise.
     * @~chinese 如果本向量小于给定的向量返回true，否则返回false。
     */
    inline bool operator<(const Vec2& v) const;
    
    /**
     * @~english Determines if this vector is greater than the given vector.
     * @~chinese 判断该向量是否大于给定向量v。
     * 
     * @param v @~english The vector to compare against. @~chinese 要比较的向量。
     * 
     * @return @~english True if this vector is greater than the given vector, false otherwise.
     * @~chinese 如果本向量大于给定的向量返回true，否则返回false。
     */
    inline bool operator>(const Vec2& v) const;

    /**
     * @~english Determines if this vector is equal to the given vector.
     * @~chinese 判断该向量是否等于给定向量v。
     * 
     * @param v @~english The vector to compare against. @~chinese 要比较的向量。
     * 
     * @return @~english True if this vector is equal to the given vector, false otherwise.
     * @~chinese 如果本向量等于给定的向量返回true，否则返回false。
     */
    inline bool operator==(const Vec2& v) const;

    /**
     * @~english Determines if this vector is not equal to the given vector.
     * @~chinese 判断该向量是否不等于给定向量v。
     * 
     * @param v @~english The vector to compare against. @~chinese 要比较的向量。
     * 
     * @return @~english True if this vector is not equal to the given vector, false otherwise.
     * @~chinese 如果本向量不等于给定的向量返回true，否则返回false。
     */
    inline bool operator!=(const Vec2& v) const;

    //code added compatible for Point
public:
    /**
     * @~english Sets the elements of this point to the specified values.
     * @~chinese 设置该点的坐标值为指定值。
     * 
     * @param xx @~english The new x coordinate. @~chinese 新的x坐标。
     * @param yy @~english The new y coordinate. @~chinese 新的y坐标。
     * @js NA
     * @lua NA
     */
    inline void setPoint(float xx, float yy);

    /**
     * @~english Determines if this point is equal to the given point.
     * @~chinese 判断该点是否等于目标点。
     * 
     * @param target @~english The point to compare against. @~chinese 要比较的向量。
     * 
     * @return @~english True if this point is equal to the given point, false otherwise.
     * @~chinese 如果本向量等于给定的向量返回true，否则返回false。
     * @js NA
     */
    bool equals(const Vec2& target) const;
    
    /** @returns @~english if points have fuzzy equality which means equal with some degree of variance.
     * @~chinese 判断点是否在目标点一定偏差范围内。
     * @since v2.1.4
     * @js NA
     * @lua NA
     */
    bool fuzzyEquals(const Vec2& target, float variance) const;

    /** @~english Calculates distance between point an origin.
     * @~chinese 计算该点到原点的距离。
     *
     * @return @~english distance between two points. @~chinese 两点距离。
     * @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline float getLength() const {
        return sqrtf(x*x + y*y);
    };

    /** @~english Calculates the square length of a Vec2 (not calling sqrt() )
     * @~chinese 计算该点到原点距离的平方。
     *
     * @return @~english the square of distance. @~chinese 距离的平方。
     * @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline float getLengthSq() const {
        return dot(*this); //x*x + y*y;
    };

    /** @~english Calculates the square distance between two points (not calling sqrt() )
     * @~chinese 计算该点到给定点距离的平方。
     *
     * @return @~english the square of distance. @~chinese 距离的平方。
     * @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline float getDistanceSq(const Vec2& other) const {
        return (*this - other).getLengthSq();
    };

    /** @~english Calculates the distance between two points
     * @~chinese 计算该点到给定点的距离。
     *
     * @return @~english distance between two points. @~chinese 两点距离。
     * @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline float getDistance(const Vec2& other) const {
        return (*this - other).getLength();
    };

    /** @returns @~english the angle in radians between this vector and the x axis
     * @~chinese 获取该向量和x轴的夹角（弧度）。
     * @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline float getAngle() const {
        return atan2f(y, x);
    };

    /** @returns @~english the angle in radians between two vector directions
     * @~chinese 获取该向量与给定向量的夹角（弧度）。
     * @since v2.1.4
     * @js NA
     * @lua NA
     */
    float getAngle(const Vec2& other) const;

    /** @~english Calculates cross product of two vectors.
     * @~chinese 计算该向量与给定向量的向量积。
     *
     * @return @~english the cross product. @~chinese 向量积。
     * @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline float cross(const Vec2& other) const {
        return x*other.y - y*other.x;
    };

    /** @~english Calculates perpendicular of v, rotated 90 degrees counter-clockwise -- cross(v, perp(v)) >= 0
     * @~chinese 计算该向量逆时针旋转90度的新向量。
     * @return @~english new vector. @~chinese 新向量。
     * @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline Vec2 getPerp() const {
        return Vec2(-y, x);
    };
    
    /** @~english Calculates midpoint between two points.
     * @~chinese 计算两点之间的中心点。
     * @return @~english midpoint. @~chinese 中心点。
     * @since v3.0
     * @js NA
     * @lua NA
     */
    inline Vec2 getMidpoint(const Vec2& other) const
    {
        return Vec2((x + other.x) / 2.0f, (y + other.y) / 2.0f);
    }
    
    /** @~english Clamp a point between from and to.
     * @~chinese 获取给定点在限制范围内的限制点。
     * @since v3.0
     * @js NA
     * @lua NA
     */
    inline Vec2 getClampPoint(const Vec2& min_inclusive, const Vec2& max_inclusive) const
    {
        return Vec2(clampf(x,min_inclusive.x,max_inclusive.x), clampf(y, min_inclusive.y, max_inclusive.y));
    }
    
    /** @~english Run a math operation function on each point component
     * absf, fllorf, ceilf, roundf
     * any function that has the signature: float func(float);
     * For example: let's try to take the floor of x,y
     * p.compOp(floorf);
     *
     * @~chinese 对该点向量的各分量执行给定操作的运算，如：
     * absf、fllorf ceilf roundf
     * 例如:对x,y进行floor运算，则调用 p.compOp(floorf)
     * @since v3.0
     * @js NA
     * @lua NA
     */
    inline Vec2 compOp(std::function<float(float)> function) const
    {
        return Vec2(function(x), function(y));
    }

    /** @~english Calculates perpendicular of v, rotated 90 degrees clockwise -- cross(v, rperp(v)) <= 0
     * @~chinese 计算向量v顺时针旋转90度后的值。
     *
     * @return @~english Vec2 the result of rotated vector. @~chinese 旋转后的向量。
     * @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline Vec2 getRPerp() const {
        return Vec2(y, -x);
    };

    /** @~english Calculates the projection of this over other.
     * @~chinese 计算该向量在另一向量other上的投影。
     *
     * @param other @~english the other vector.  @~chinese 另一个向量。
     * @return @~english the projection. @~chinese 投影。
     * @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline Vec2 project(const Vec2& other) const {
        return other * (dot(other)/other.dot(other));
    };

    /** @~english Complex multiplication of two points ("rotates" two points).
     * @~chinese 计算该向量绕给定向量旋转所得的向量。
     *
     * @return @~english Vec2 vector with an angle of this.getAngle() + other.getAngle(),
     * and a length of this.getLength() * other.getLength().
     * @~chinese 旋转所得向量的角度等于：this.getAngle()+ other.getAngle(),
     * 长度等于：this.getLength长度()* other.getLength()。
     * @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline Vec2 rotate(const Vec2& other) const {
        return Vec2(x*other.x - y*other.y, x*other.y + y*other.x);
    };

    /** @~english Unrotates two points.
     * @~chinese 计算该向量绕给定向量旋转前的向量。
     *
     * @return @~english Vec2 vector with an angle of this.getAngle() - other.getAngle(),
     * and a length of this.getLength() * other.getLength().
     * @~chinese 旋转前向量的角度等于：this.getAngle()——other.getAngle(),
     * 长度等于：this.getLength长度()* other.getLength()。
     * @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline Vec2 unrotate(const Vec2& other) const {
        return Vec2(x*other.x + y*other.y, y*other.x - x*other.y);
    };

    /** @~english Linear Interpolation between two points a and b
     * @~chinese 计算两个点a和b之间的线性插值。
     *
     * @param other @~english The point to compute the linear interpolation with. 
     * @~chinese 用以计算线性插值的另一坐标。
     * @param alpha @~english the coefficient of linear interpolation. 
     * @~chinese 线性插值系数。
     *
     * @return @~english The result of the linear interpolation.
     * @~chinese 线性插值结果。
     * @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline Vec2 lerp(const Vec2& other, float alpha) const {
        return *this * (1.f - alpha) + other * alpha;
    };

    /** @~english Rotates a point counter clockwise by the angle around a pivot
     * @~chinese 计算以pivot为轴逆时针旋转angle度后的点。（单位为弧度）。
     *
     * @param pivot @~english is the pivot, naturally. @~chinese 轴。
     * @param angle @~english is the angle of rotation ccw in radians. @~chinese 旋转角度。
     *
     * @returns @~english the rotated point. @~chinese 旋转后的点。
     * @since v2.1.4
     * @js NA
     * @lua NA
     */
    Vec2 rotateByAngle(const Vec2& pivot, float angle) const;

    /**
     * @js NA
     * @lua NA
     */
    static inline Vec2 forAngle(const float a)
    {
        return Vec2(cosf(a), sinf(a));
    }
    
    /** @~english A general line-line intersection test
     * @~chinese 判断给定的两条线段是否相交。
     *
     * @param A   @~english the startpoint for the first line L1 = (A - B)
     * @~chinese 第一条线段的起始端点。
     * @param B   @~english the endpoint for the first line L1 = (A - B)
     * @~chinese 第一条线段的结束端点。
     * @param C   @~english the startpoint for the second line L2 = (C - D)
     * @~chinese 第二条线段的起始端点。
     * @param D   @~english the endpoint for the second line L2 = (C - D)
     * @~chinese 第二条线段的结束端点。
     * @param S   @~english the range for a hitpoint in L1 (p = A + S*(B - A))
     * @~chinese 相交点在线段L1的范围(p = A + S*(B - A))
     * @param T   @~english the range for a hitpoint in L2 (p = C + T*(D - C))
     * @~chinese 相交点在线段L2的范围(p = C + T*(D - C))
     *
     * @returns @~english  whether these two lines interects.
     *
     * Note that to truly test intersection for segments we have to make
     * sure that S & T lie within [0..1] and for rays, make sure S & T > 0
     * the hit point is        C + T * (D - C);
     * the hit point also is   A + S * (B - A);

     * @~chinese 返回两条线段是否相交。 
     * 注意, 判断线段是否相交应该确认返回值S和T的值都在区间[0,1]内；判断射线是否相交应该确认（S & T）的值大于0.
     * 相交点等于：C + T * (D - C); 也等于A + S * (B - A);
     * @since 3.0
     * @js NA
     * @lua NA
     */
    static bool isLineIntersect(const Vec2& A, const Vec2& B,
                                 const Vec2& C, const Vec2& D,
                                 float *S = nullptr, float *T = nullptr);
    
    /**@~english
     * returns true if Line A-B overlap with segment C-D
     * @~chinese 判断 线段A-B 与 线段C-D是否重叠。
     *
     * @param A   @~english the startpoint for the first line L1 = (A - B)
     * @~chinese 第一条线段的起始端点。
     * @param B   @~english the endpoint for the first line L1 = (A - B)
     * @~chinese 第一条线段的结束端点。
     * @param C   @~english the startpoint for the second line L2 = (C - D)
     * @~chinese 第二条线段的起始端点。
     * @param D   @~english the endpoint for the second line L2 = (C - D)
     * @~chinese 第二条线段的结束端点。
     *
     * @returns @~english  whether these two lines overlap. 
     * @~chinese 如果两线段重叠返回true，否则返回false。
     * @since v3.0
     * @js NA
     * @lua NA
     */
    static bool isLineOverlap(const Vec2& A, const Vec2& B,
                                const Vec2& C, const Vec2& D);
    
    /**@~english
     * returns true if Line A-B parallel with segment C-D
     * @~chinese 判断 线段A-B 与 线段C-D是否平行。
     *
     * @param A   @~english the startpoint for the first line L1 = (A - B)
     * @~chinese 第一条线段的起始端点。
     * @param B   @~english the endpoint for the first line L1 = (A - B)
     * @~chinese 第一条线段的结束端点。
     * @param C   @~english the startpoint for the second line L2 = (C - D)
     * @~chinese 第二条线段的起始端点。
     * @param D   @~english the endpoint for the second line L2 = (C - D)
     * @~chinese 第二条线段的结束端点。
     *
     * @returns @~english  whether these two lines is parallel. 
     * @~chinese 如果两线段平行返回true，否则返回false。
     * @since v3.0
     * @js NA
     * @lua NA
     */
    static bool isLineParallel(const Vec2& A, const Vec2& B,
                   const Vec2& C, const Vec2& D);
    
    /**@~english
     * returns true if Segment A-B overlap with segment C-D
     * @~chinese 判断 线段A-B 与 线段C-D是否重叠。
     *
     * @param A   @~english the startpoint for the first line L1 = (A - B)
     * @~chinese 第一条线段的起始端点。
     * @param B   @~english the endpoint for the first line L1 = (A - B)
     * @~chinese 第一条线段的结束端点。
     * @param C   @~english the startpoint for the second line L2 = (C - D)
     * @~chinese 第二条线段的起始端点。
     * @param D   @~english the endpoint for the second line L2 = (C - D)
     * @~chinese 第二条线段的结束端点。
     * @param S   @~english the start point
     * @~chinese 起点。
     * @param E   @~english the endpoint
     * @~chinese 端点。
     *
     * @returns @~english  whether these two lines overlap. 
     * @~chinese 如果两线段重叠返回true，否则返回false。
     * @since v3.0
     * @js NA
     * @lua NA
     */
    static bool isSegmentOverlap(const Vec2& A, const Vec2& B,
                                 const Vec2& C, const Vec2& D,
                                 Vec2* S = nullptr, Vec2* E = nullptr);
    
    /**@~english
     * returns true if Segment A-B intersects with segment C-D
     * @~chinese 判断给定的两条线段是否相交。
     *
     * @param A   @~english the startpoint for the first line L1 = (A - B)
     * @~chinese 第一条线段的起始端点。
     * @param B   @~english the endpoint for the first line L1 = (A - B)
     * @~chinese 第一条线段的结束端点。
     * @param C   @~english the startpoint for the second line L2 = (C - D)
     * @~chinese 第二条线段的起始端点。
     * @param D   @~english the endpoint for the second line L2 = (C - D)
     * @~chinese 第二条线段的结束端点。
     *
     * @returns @~english whether these two lines interects.
     * @~chinese 如果线段相交返回true，否则返回false。
     * @since v3.0
     * @js NA
     * @lua NA
     */
    static bool isSegmentIntersect(const Vec2& A, const Vec2& B, const Vec2& C, const Vec2& D);
    
    /**@~english
     * returns the intersection point of line A-B, C-D
     * @~chinese 获取两条线段的相交点。
     *
     * @param A   @~english the startpoint for the first line L1 = (A - B)
     * @~chinese 第一条线段的起始端点。
     * @param B   @~english the endpoint for the first line L1 = (A - B)
     * @~chinese 第一条线段的结束端点。
     * @param C   @~english the startpoint for the second line L2 = (C - D)
     * @~chinese 第二条线段的起始端点。
     * @param D   @~english the endpoint for the second line L2 = (C - D)
     * @~chinese 第二条线段的结束端点。
     *
     * @returns @~english the intersection point. @~chinese 相交点。
     * @since v3.0
     * @js NA
     * @lua NA
     */
    static Vec2 getIntersectPoint(const Vec2& A, const Vec2& B, const Vec2& C, const Vec2& D);
    
    /** @~english equals to Vec2(0,0)  @~chinese 等于Vec2(0,0)*/
    static const Vec2 ZERO;
    /** @~english equals to Vec2(1,1)  @~chinese 等于Vec2(1,1)*/
    static const Vec2 ONE;
    /** @~english equals to Vec2(1,0)  @~chinese 等于Vec2(0)*/
    static const Vec2 UNIT_X;
    /** @~english equals to Vec2(0,1)  @~chinese 等于Vec2(0,1)*/
    static const Vec2 UNIT_Y;
    /** @~english equals to Vec2(0.5, 0.5)  @~chinese 等于Vec2(0.5,0.5)*/
    static const Vec2 ANCHOR_MIDDLE;
    /** @~english equals to Vec2(0, 0)  @~chinese 等于Vec2(0,0)*/
    static const Vec2 ANCHOR_BOTTOM_LEFT;
    /** @~english equals to Vec2(0, 1)  @~chinese 等于Vec2(0,1)*/
    static const Vec2 ANCHOR_TOP_LEFT;
    /** @~english equals to Vec2(1, 0)  @~chinese equals to Vec2(1、0)*/
    static const Vec2 ANCHOR_BOTTOM_RIGHT;
    /** @~english equals to Vec2(1, 1)  @~chinese 等于Vec2(1,1)*/
    static const Vec2 ANCHOR_TOP_RIGHT;
    /** @~english equals to Vec2(1, 0.5)  @~chinese 等于Vec2(0.5)*/
    static const Vec2 ANCHOR_MIDDLE_RIGHT;
    /** @~english equals to Vec2(0, 0.5)  @~chinese 等于Vec2(0,- 0.5)*/
    static const Vec2 ANCHOR_MIDDLE_LEFT;
    /** @~english equals to Vec2(0.5, 1)  @~chinese 等于Vec2(0.5,1)*/
    static const Vec2 ANCHOR_MIDDLE_TOP;
    /** @~english equals to Vec2(0.5, 0)  @~chinese 等于Vec2(0.5,0)*/
    static const Vec2 ANCHOR_MIDDLE_BOTTOM;
};

/**
 * @~english Calculates the scalar product of the given vector with the given value.
 * @~chinese 计算给定向量与给定缩放系数相乘后的向量。
 * 
 * @param x @~english The value to scale by. @~chinese 缩放系数。
 * @param v @~english The vector to scale. @~chinese 被缩放的向量。
 * 
 * @return @~english The scaled vector. @~chinese 缩放后的向量。
 */
inline const Vec2 operator*(float x, const Vec2& v);

typedef Vec2 Point;

NS_CC_MATH_END


// end of base group
/// @}

#include "Vec2.inl"

#endif // MATH_VEC2_H
