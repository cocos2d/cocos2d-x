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

#ifndef MATH_VEC3_H
#define MATH_VEC3_H

#include "math/CCMathBase.h"

/**
 * @addtogroup base
 * @{
 */

NS_CC_MATH_BEGIN

class Mat4;
class Quaternion;

/**@~english
 * Defines a 3-element floating point vector.
 *
 * When using a vector to represent a surface normal,
 * the vector should typically be normalized.
 * Other uses of directional vectors may wish to leave
 * the magnitude of the vector intact. When used as a point,
 * the elements of the vector represent a position in 3D space.
 *
 * @~chinese 
 * 定义了一个三元浮点向量。
 * 
 * 当用作表面法向量时，该向量应该归一化。
 * 用作方向向量的时候可能会保持原向量的大小不变。 
 * 当用作点时，代表了3d空间的一个位置。
 */
class CC_DLL Vec3
{
public:

    /** @~english The x-coordinate. @~chinese x坐标。*/
    float x;

    /** @~english The y-coordinate. @~chinese y坐标。*/
    float y;

    /** @~english The z-coordinate. @~chinese z坐标。*/
    float z;

    /** 
     * @~english Constructs a new vector initialized to all zeros.
     * @~chinese 构造一个新的向量，所有成员属性初始化为零。
     */
    Vec3();

    /** 
     * @~english Constructs a new vector initialized to the specified values.
     * @~chinese 构造一个新的向量，并初始化成员属性为指定的值。
     * 
     * @param xx @~english The x coordinate. @~chinese x坐标。
     * @param yy @~english The y coordinate. @~chinese y坐标。
     * @param zz @~english The z coordinate. @~chinese z坐标。
     */
    Vec3(float xx, float yy, float zz);

    /**
     * @~english Constructs a new vector from the values in the specified array.
     * @~chinese 用给定数组中的值构造一个新的向量。
     * 
     * @param array @~english An array containing the elements of the vector in the order x，y，z.
     * @~chinese 一个依次包含x，y, z分量的数组。
     */
    Vec3(const float* array);

    /**
     * @~english Constructs a vector that describes the direction between the specified points.
     * @~chinese 构造一个点p1指向点p2的向量。
     * 
     * @param p1 @~english The first point. @~chinese 第一点。
     * @param p2 @~english The second point. @~chinese 第二点。
     */
    Vec3(const Vec3& p1, const Vec3& p2);

    /**
     * @~english Constructs a new vector that is a copy of the specified vector.
     * @~chinese 拷贝构造函数。
     * 
     * @param copy @~english The vector to copy. @~chinese 被拷贝的向量。
     */
    Vec3(const Vec3& copy);

    /**@~english
     * Creates a new vector from an integer interpreted as an RGB value.
     * E.g. 0xff0000 represents red or the vector (1, 0, 0).
     *
     * @~chinese 
     * 使用给定的一个表示RGB颜色的整数创建一个新的向量。
     * 例如：0xff0000代表红色或向量(1, 0, 0)。
     * 
     * @param color @~english The integer to interpret as an RGB value.
     * @~chinese 一个表示RGB颜色的整数。
     * 
     * @return @~english A vector corresponding to the interpreted RGB color.
     * @~chinese 一个表示RGB颜色值的对应向量。
     */
    static Vec3 fromColor(unsigned int color);

    /** @~english Destructor. @~chinese 析构函数。*/
    ~Vec3();

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
    static float angle(const Vec3& v1, const Vec3& v2);


    /**
     * @~english Adds the elements of the specified vector to this one.
     * @~chinese 将指定向量的值添加给这个向量。
     * 
     * @param v @~english The vector to add. @~chinese 添加的向量。
     */
    inline void add(const Vec3& v);


    /**
     * @~english Adds the elements of this vector to the specified values.
     * @~chinese 给本向量的各分量增加给定的对应值。
     * 
     * @param xx @~english The add x coordinate.
     * @~chinese x坐标加数。
     * @param yy @~english The add y coordinate.
     * @~chinese y坐标加数。
     * @param zz @~english The add z coordinate.
     * @~chinese z坐标加数。
     */
    inline void add(float xx, float yy, float zz);

    /**
     * @~english Adds the specified vectors and stores the result in dst.
     * @~chinese 将给定向量v1和向量v2相加，结果保存到向量dst。 
     * 
     * @param v1 @~english The first vector. @~chinese 第一个向量。
     * @param v2 @~english The second vector. @~chinese 第二个向量。
     * @param dst @~english A vector to store the result in. @~chinese 用以保存结果的向量。
     */
    static void add(const Vec3& v1, const Vec3& v2, Vec3* dst);

    /**
     * @~english Clamps this vector within the specified range.
     * @~chinese 将向量值限制在指定区间内。
     * 
     * @param min @~english The minimum value. @~chinese 最小值。 
     * @param max @~english The maximum value. @~chinese 最大值。 
     */
    void clamp(const Vec3& min, const Vec3& max);

    /**
     * @~english Clamps the specified vector within the specified range and returns it in dst.
     * @~chinese 将指定向量v限制在[min,max]区间内，并用dst保存结果。
     * 
     * @param v @~english The vector to clamp. @~chinese 将被限定的向量。
     * @param min @~english The minimum value. @~chinese 最小值。
     * @param max @~english The maximum value. @~chinese 最大值。
     * @param dst @~english A vector to store the result in. @~chinese 一个用以保存结果的向量。
     */
    static void clamp(const Vec3& v, const Vec3& min, const Vec3& max, Vec3* dst);

    /**
     * @~english Sets this vector to the cross product between itself and the specified vector.
     * @~chinese 计算本向量和给定向量的向量积，并把结果保存给本向量。
     * 
     * @param v @~english The vector to compute the cross product with.
     * @~chinese 用以计算向量积的给定向量。
     */
    void cross(const Vec3& v);

    /**
     * @~english Computes the cross product of the specified vectors and stores the result in dst.
     * @~chinese 计算向量v1和向量v2的向量积，计算结果保存给向量dst。 
     * 
     * @param v1 @~english The first vector.
     * @~chinese 第一个向量。
     * @param v2 @~english The second vector.
     * @~chinese 第二个向量。
     * @param dst @~english A vector to store the result in.
     * @~chinese 用以保存计算结果的向量。
     */
    static void cross(const Vec3& v1, const Vec3& v2, Vec3* dst);

    /**
     * @~english Returns the distance between this vector and v.
     * @~chinese 返回本向量与向量v的距离。
     * 
     * @param v @~english The other vector. @~chinese 另一个向量。
     * 
     * @return @~english The distance between this vector and v.
     * @~chinese 本向量到向量v的距离。
     * 
     * @see distanceSquared
     */
    float distance(const Vec3& v) const;

    /** @~english
     * Returns the squared distance between this vector and v.
     *
     * When it is not necessary to get the exact distance between
     * two vectors (for example, when simply comparing the
     * distance between different vectors), it is advised to use
     * this method instead of distance.
     *
     * @~chinese 返回本向量与向量v的距离的平方。
     * 如果不需要得到两个向量之间的准确距离， 例如只是比较不同向量之间的距离大小的时候， 
     * 建议使用这个函数来代替distance函数。
     * 
     * @param v @~english The other vector. @~chinese 另一个向量。
     * 
     * @return @~english The squared distance between this vector and v.
     * @~chinese 这个向量和v的距离的平方。
     * @see distance
     */
    float distanceSquared(const Vec3& v) const;

    /** 
     * @~english Returns the dot product of this vector and the specified vector.
     * @~chinese 返回本向量与指定向量v的点积
     * 
     * @param v @~english The vector to compute the dot product with.
     * @~chinese 用来计算点积的另一个向量
     * 
     * @return @~english The dot product. @~chinese 点积。
     */
    float dot(const Vec3& v) const;

    /**
     * @~english Returns the dot product between the specified vectors.
     * @~chinese 返回两个指定向量的点积。
     * 
     * @param v1 @~english The first vector. @~chinese 第一个向量。
     * @param v2 @~english The second vector. @~chinese 第二个向量。
     * 
     * @return @~english The dot product between the vectors. @~chinese 向量的点积。
     */
    static float dot(const Vec3& v1, const Vec3& v2);

    /**
     * @~english Computes the length of this vector.
     * @~chinese 计算这个向量的长度。
     * 
     * @return @~english The length of the vector. @~chinese 这个向量的长度。
     * @see lengthSquared
     */
    inline float length() const;

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
     * This method normalizes this Vec3 so that it is of
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
    Vec3 getNormalized() const;

    /** 
     * @~english Scales all elements of this vector by the specified value.
     * @~chinese 用指定的缩放系数对向量的各分量进行缩放。
     * 
     * @param scalar @~english The scalar value. @~chinese 缩放系数。
     */
    inline void scale(float scalar);

    /**
     * @~english Sets the elements of this vector to the specified values.
     * @~chinese 设置向量的分量值为指定值。
     * 
     * @param xx @~english The new x coordinate. @~chinese 新的x坐标。 
     * @param yy @~english The new y coordinate. @~chinese 新的y坐标。
     * @param zz @~english The new z coordinate. @~chinese 新的z坐标。
     */
    inline void set(float xx, float yy, float zz);

    /**
     * @~english Sets the elements of this vector from the values in the specified array.
     * @~chinese 设置这个向量的分量为指定数组中的值。
     * 
     * @param array @~english An array containing the elements of the vector in the order x, y, z.
     * @~chinese 一个依次包含x，y，z分量的数组。
     */
    inline void set(const float* array);

    /**
     * @~english Sets the elements of this vector to those in the specified vector.
     * @~chinese 将指定向量的各分量值设置给本向量。
     * 
     * @param v @~english The vector to copy. @~chinese 被拷贝的向量。
     */
    inline void set(const Vec3& v);

    /**
     * @~english Sets this vector to the directional vector between the specified points.
     * @~chinese 设置向量值为两个指定点之间的向量。
     * 
     * @param p1 @~english The first point. @~chinese 第一点。
     * @param p2 @~english The second point. @~chinese 第二点。
     */
    inline void set(const Vec3& p1, const Vec3& p2);

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
     * @~chinese 向量减数。
     */
    inline void subtract(const Vec3& v);

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
    static void subtract(const Vec3& v1, const Vec3& v2, Vec3* dst);

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
    void smooth(const Vec3& target, float elapsedTime, float responseTime);

    /**
     * @~english Linear interpolation between two vectors A and B by alpha which is in the range [0,1]
     * @~chinese 使用本向量和另一向量做线性插值，其中插值系数alpha的取值范围为[0,1]。 
     *
     * @param other @~english The vector to compute the linear interpolation with. 
     * @~chinese 用以计算线性插值的另一向量。
     * @param alpha @~english the coefficient of linear interpolation. 
     * @~chinese 线性插值系数。
     *
     * @return @~english The result of the linear interpolation.
     * @~chinese 线性插值结果。
     */
    inline Vec3 lerp(const Vec3& other, float alpha) const;

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
    inline const Vec3 operator+(const Vec3& v) const;

    /**
     * @~english Adds the given vector to this vector.
     * @~chinese 向量加法，求向量与给定向量v的和，将结果保存在该向量中并返回。
     * 
     * @param v @~english The vector to add. @~chinese 被加的向量。
     * 
     * @return @~english This vector, after the addition occurs.
     * @~chinese 向量和。
     */
    inline Vec3& operator+=(const Vec3& v);

    /**
     * @~english Calculates the difference of this vector with the given vector.
     * Note: this does not modify this vector.
     * @~chinese 向量减法，求向量与给定向量v的差
     * 注意:这并不修改原向量的值。
     * 
     * @param v @~english The vector to minus. @~chinese 向量减数。
     *
     * @return @~english The vector difference. @~chinese 向量差。
     */
    inline const Vec3 operator-(const Vec3& v) const;

    /**
     * @~english Subtracts the given vector from this vector.
     * @~chinese 向量减法，求向量与给定向量v的差，将结果保存在该向量中并返回。
     * 
     * @param v @~english The vector to subtract. @~chinese 向量减数。
     * 
     * @return @~english This vector, after the subtraction occurs. @~chinese 向量差。
     */
    inline Vec3& operator-=(const Vec3& v);

    /**@~english
     * Calculates the negation of this vector.
     * Note: this does not modify this vector.
     * @~chinese 求负向量。
     * 注意:这并不修改原向量的值。
     * 
     * @return @~english The negation of this vector. @~chinese 负向量。
     */
    inline const Vec3 operator-() const;

    /** @~english
     * Calculates the scalar product of this vector with the given value.
     * Note: this does not modify this vector.
     * @~chinese 求向量乘以给定缩放系数后的向量。
     * 注意:这并不修改原向量的值。
     * 
     * @param s @~english The value to scale by. @~chinese 缩放系数。
     * 
     * @return @~english The scaled vector. @~chinese 缩放后的向量。
     */
    inline const Vec3 operator*(float s) const;

    /**@~english
     * Scales this vector by the given value. 
     * @~chinese  求向量乘以给定缩放系数后的向量，并将结果保存到本向量。
     * 
     * @param s @~english The value to scale by. @~chinese 缩放系数。
     * 
     * @return @~english This vector, after the scale occurs. @~chinese 缩放后的向量。
     */
    inline Vec3& operator*=(float s);
    
    /**@~english
     * Returns the components of this vector divided by the given constant
     * Note: this does not modify this vector.
     * @~chinese 求向量除以给定除数的商。
     * 注意:这并不修改原向量的值。
     * 
     * @param s @~english the constant to divide this vector with
     * @~chinese 向量要除的常数。
     * @return @~english the result is this vector divided by the given constant.
     * @~chinese 除后的向量结果。
     */
    inline const Vec3 operator/(float s) const;

    /**
     * @~english Determines if this vector is less than the given vector.
     * @~chinese 判断该向量是否小于给定向量rhs。
     * 
     * @param rhs @~english The vector to compare against. @~chinese 要比较的向量。
     * 
     * @return @~english True if this vector is less than the given vector, false otherwise.
     * @~chinese 如果本向量小于给定的向量返回true，否则返回false。
     */
    inline bool operator < (const Vec3& rhs) const
    {
        if (x < rhs.x && y < rhs.y && z < rhs.z)
            return true;
        return false;
    }

    /**
     * @~english Determines if this vector is greater than the given vector.
     * @~chinese 判断该向量是否大于给定向量rhs。
     * 
     * @param rhs @~english The vector to compare against. @~chinese 要比较的向量。
     * 
     * @return @~english True if this vector is greater than the given vector, false otherwise.
     * @~chinese 如果本向量大于给定的向量返回true，否则返回false。
     */
    inline bool operator >(const Vec3& rhs) const
    {
        if (x > rhs.x && y > rhs.y && z > rhs.z)
            return true;
        return false;
    }

    /**
     * @~english Determines if this vector is equal to the given vector.
     * @~chinese 判断该向量是否等于给定向量v。
     * 
     * @param v @~english The vector to compare against. @~chinese 要比较的向量。
     * 
     * @return @~english True if this vector is equal to the given vector, false otherwise.
     * @~chinese 如果本向量等于给定的向量返回true，否则返回false。
     */
    inline bool operator==(const Vec3& v) const;

    /**
     * @~english Determines if this vector is not equal to the given vector.
     * @~chinese 判断该向量是否不等于给定向量v。
     * 
     * @param v @~english The vector to compare against. @~chinese 要比较的向量。
     * 
     * @return @~english True if this vector is not equal to the given vector, false otherwise.
     * @~chinese 如果本向量不等于给定的向量返回true，否则返回false。
     */
    inline bool operator!=(const Vec3& v) const;
    
    /** @~english equals to Vec3(0,0,0)  @~chinese 等于Vec3(0,0,0)*/
    static const Vec3 ZERO;
    /** @~english equals to Vec3(1,1,1)  @~chinese 等于Vec3(1,1,1)*/
    static const Vec3 ONE;
    /** @~english equals to Vec3(1,0,0)  @~chinese 等于Vec3(0,0)*/
    static const Vec3 UNIT_X;
    /** @~english equals to Vec3(0,1,0)  @~chinese 等于Vec3(0,1,0)*/
    static const Vec3 UNIT_Y;
    /** @~english equals to Vec3(0,0,1)  @~chinese 等于Vec3(0,0,1)*/
    static const Vec3 UNIT_Z;
};

/**
 * @~english Calculates the scalar product of the given vector with the given value.
 * @~chinese 计算给定向量与给定缩放系数相乘后的缩放向量。
 * 
 * @param x @~english The value to scale by. @~chinese 缩放系数。
 * @param v @~english The vector to scale. @~chinese 被缩放的向量。
 * 
 * @return @~english The scaled vector. @~chinese 缩放后的向量。
 */
inline const Vec3 operator*(float x, const Vec3& v);

NS_CC_MATH_END

// end of base group
/// @}

#include "Vec3.inl"

#endif // MATH_VEC3_H
