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

#ifndef QUATERNION_H_
#define QUATERNION_H_

#include "math/Vec3.h"
#include "math/Mat4.h"
//#include "Plane.h"

/**
 * @addtogroup base
 * @{
 */

NS_CC_MATH_BEGIN

class Mat4;

/**
@class Quaternion
@brief
@~english
 * Defines a 4-element quaternion that represents the orientation of an object in space.
 *
 * Quaternions are typically used as a replacement for euler angles and rotation matrices as a way to achieve smooth interpolation and avoid gimbal lock.
 *
 * Note that this quaternion class does not automatically keep the quaternion normalized. Therefore, care must be taken to normalize the quaternion when necessary, by calling the normalize method.
 * This class provides three methods for doing quaternion interpolation: lerp, slerp, and squad.
 *
 * lerp (linear interpolation): the interpolation curve gives a straight line in quaternion space. It is simple and fast to compute. The only problem is that it does not provide constant angular velocity. Note that a constant velocity is not necessarily a requirement for a curve;
 * slerp (spherical linear interpolation): the interpolation curve forms a great arc on the quaternion unit sphere. Slerp provides constant angular velocity;
 * squad (spherical spline interpolation): interpolating between a series of rotations using slerp leads to the following problems:
 * - the curve is not smooth at the control points;
 * - the angular velocity is not constant;
 * - the angular velocity is not continuous at the control points.
 *
 * Since squad is continuously differentiable, it remedies the first and third problems mentioned above.
 * The slerp method provided here is intended for interpolation of principal rotations. It treats +q and -q as the same principal rotation and is at liberty to use the negative of either input. The resulting path is always the shorter arc.
 *
 * The lerp method provided here interpolates strictly in quaternion space. Note that the resulting path may pass through the origin if interpolating between a quaternion and its exact negative.
 *
 * As an example, consider the following quaternions:
 *
 * q1 = (0.6, 0.8, 0.0, 0.0),
 * q2 = (0.0, 0.6, 0.8, 0.0),
 * q3 = (0.6, 0.0, 0.8, 0.0), and
 * q4 = (-0.8, 0.0, -0.6, 0.0).
 * For the point p = (1.0, 1.0, 1.0), the following figures show the trajectories of p using lerp, slerp, and squad.
 * @~chinese 
 * 该类是四元数的抽象，其封装了4个元素，用于表示空间中的3D旋转和3D朝向。
 * 
 * 四元数一半用来替代欧拉角和旋转矩阵，因为它可以实现平滑的差值，并且可以避免万向节锁。
 * 
 * 注意,四元数并不会自动的归一化，所以请在需要的时候通过调用对应的函数来对四元数归一化。
 * 这个类提供了三种方法来进行四元数的插值:lerp，slerp和squad方法。
 * 
 * lerp(线性插值):在四元数空间中，实现线性差值，它计算简单，性能高，代价是经过差值后，物体的旋转角速度不是恒定的。但是在曲线中，稳定的速度不是一个硬性需求。
 * 与其(球面线性插值):在单位四元数空间中，使用球面线性差值。它可以提供恒定的角速度;
 * 队(球面样条插值):在一系列的旋转控制点中进行差值过渡，在两个差值点之前仍然使用球面线性差值，其具有以下特点
 * ——在控制点曲线不平滑;
 * ——角速度不是常数;
 * ——角速度不是在控制点不是连续的。
 * 
 * 由于球面样条差值是连续可微的,它可以补救上面提到的第一个和第三个问题。
 * 球面线性差值主要用来进行两个主旋转中的差值，他把＋q和－q当作同一个旋转，所以在差值时，它会经过最短的圆弧进行差值。
 * 线性差值是在四元数空间中进行严格的线性差值。如果从旋转q差值到q的逆，差值的曲线会经过四元数空间的球心。
 * 
 * 
 */
class CC_DLL Quaternion
{
    friend class Curve;
    friend class Transform;

public:

    /**@~english
     * The x-value of the quaternion's vector component.
     * @~chinese 
     * 四元数的x值分量。
     */
    float x;
    /**@~english
     * The y-value of the quaternion's vector component.
     * @~chinese 
     * 四元数的y值分量。
     */
    float y;
    /**@~english
     * The z-value of the quaternion's vector component.
     * @~chinese 
     * 四元数的z值分量。
     */
    float z;
    /**@~english
     * The scalar component of the quaternion.
     * @~chinese 
     * 四元数的w值分量。
     */
    float w;

    /**@~english
     * Constructs a quaternion initialized to (0, 0, 0, 1).
     * @~chinese 
     * 构造一个四元数，初始化为(0,0,0,1)。
     */
    Quaternion();

    /**@~english
     * Constructs a quaternion.
     *
     * @~chinese 
     * 构造一个四元数。
     * 
     * @param xx @~english The x component of the quaternion.
     * @~chinese 四元数的x分量。
     * @param yy @~english The y component of the quaternion.
     * @~chinese 四元数的y分量。
     * @param zz @~english The z component of the quaternion.
     * @~chinese 四元数的z分量。
     * @param ww @~english The w component of the quaternion.
     * @~chinese 四元数的w分量。
     */
    Quaternion(float xx, float yy, float zz, float ww);

    /**@~english
     * Constructs a new quaternion from the values in the specified array.
     *
     * @~chinese 
     * 从数组中的值，构造一个新的四元数。
     * 
     * @param array @~english The values for the new quaternion.
     * @~chinese 新四元数的值。
     */
    Quaternion(float* array);

    /**@~english
     * Constructs a quaternion equal to the rotational part of the specified matrix.
     *
     * @~chinese 
     * 从矩阵中取得旋转，来构建一个四元数。
     * 
     * @param m @~english The matrix.
     * @~chinese 矩阵。
     */
    Quaternion(const Mat4& m);

    /**@~english
     * Constructs a quaternion equal to the rotation from the specified axis and angle.
     *
     * @~chinese 
     * 从指定的轴和角度旋转值去构造一个四元数。
     * 
     * @param axis @~english A vector describing the axis of rotation.
     * @~chinese 旋转轴。
     * @param angle @~english The angle of rotation (in radians).
     * @~chinese 旋转角度(弧度)。
     */
    Quaternion(const Vec3& axis, float angle);

    /**@~english
     * Constructs a new quaternion that is a copy of the specified one.
     *
     * @~chinese 
     * 拷贝构造函数
     * 
     */
    Quaternion(const Quaternion& copy);

    /**@~english
     * Destructor.
     * @~chinese 
     * 析构函数。
     */
    ~Quaternion();

    /**@~english
     * Returns the identity quaternion.
     *
     * @~chinese 
     * 返回单位四元数。
     * 
     * @return @~english The identity quaternion.
     * @~chinese 单位四元数。
     */
    static const Quaternion& identity();

    /**@~english
     * Returns the quaternion with all zeros.
     *
     * @~chinese 
     * 返回全零四元数。
     * 
     * @return @~english The quaternion.
     * @~chinese 全零四元数。
     */
    static const Quaternion& zero();

    /**@~english
     * Determines if this quaternion is equal to the identity quaternion.
     *
     * @~chinese 
     * 判断该四元数是否单位四元数
     * 
     * @return @~english true if it is the identity quaternion, false otherwise.
     * @~chinese 如果是单位四元数,返回真，否则返回假。
     */
    bool isIdentity() const;

    /**@~english
     * Determines if this quaternion is all zeros.
     *
     * @~chinese 
     * 判断四元数是否全零。
     * 
     * @return @~english true if this quaternion is all zeros, false otherwise.
     * @~chinese 如果是，返回真,否则返回假。
     */
    bool isZero() const;

    /**@~english
     * Creates a quaternion equal to the rotational part of the specified matrix
     * and stores the result in dst.
     *
     * @~chinese 
     * 从矩阵中提取旋转分量，来创建一个四元数，保存在dst中。
     * 
     * @param m @~english The matrix.
     * @~chinese 矩阵。
     * @param dst @~english A quaternion to save the result.
     * @~chinese 存储旋转四元数。
     */
    static void createFromRotationMatrix(const Mat4& m, Quaternion* dst);

    /**@~english
     * Creates this quaternion equal to the rotation from the specified axis and angle
     * and stores the result in dst.
     *
     * @~chinese 
     * 从旋转轴和旋转角度来创建一个四元数。
     * 
     * @param axis @~english A vector describing the axis of rotation.
     * @~chinese 旋转轴。
     * @param angle @~english The angle of rotation (in radians).
     * @~chinese 旋转角度(弧度)。
     * @param dst @~english A quaternion to save the result.
     * @~chinese 存储旋转四元数。
     */
    static void createFromAxisAngle(const Vec3& axis, float angle, Quaternion* dst);

    /**@~english
     * Sets this quaternion to the conjugate of itself.
     * @~chinese 
     * 将四元数设置为自己的共轭四元数。
     */
    void conjugate();

    /**@~english
     * Gets the conjugate of this quaternion.
     *
     * @~chinese 
     * 得到共轭四元数。
     * 
     */
    Quaternion getConjugated() const;

    /**@~english
     * Sets this quaternion to the inverse of itself.
     *
     * Note that the inverse of a quaternion is equal to its conjugate
     * when the quaternion is unit-length. For this reason, it is more
     * efficient to use the conjugate method directly when you know your
     * quaternion is already unit-length.
     *
     * @~chinese 
     * 将四元数的设置为自己的逆。
     * 
     * 注意,如果一个四元数的长度是1（已经归一化），那么其逆四元数等于他的共轭。
     * 所以，如果你知道四元数已经归一化，使用共轭四元数来作为逆，性能会更高。
     * 
     * @return @~english true if the inverse can be computed, false otherwise.
     * @~chinese 如果四元数可逆，则返回真，否则返回假。
     */
    bool inverse();

    /**@~english
     * Gets the inverse of this quaternion.
     *
     * Note that the inverse of a quaternion is equal to its conjugate
     * when the quaternion is unit-length. For this reason, it is more
     * efficient to use the conjugate method directly when you know your
     * quaternion is already unit-length.
     * @~chinese 
     * 得到逆四元数。
     * 
     * 注意,如果一个四元数的长度是1（已经归一化），那么其逆四元数等于他的共轭。
     * 所以，如果你知道四元数已经归一化，使用共轭四元数来作为逆，性能会更高。
     */
    Quaternion getInversed() const;

    /**@~english
     * Multiplies this quaternion by the specified one and stores the result in this quaternion.
     *
     * @~chinese 
     * 右乘四元数q，并且将结果存储在this中。
     * 
     * @param q @~english The quaternion to multiply.
     * @~chinese 要右乘的四元数。
     */
    void multiply(const Quaternion& q);

    /**@~english
     * Multiplies the specified quaternions and stores the result in dst.
     *
     * @~chinese 
     * 计算四元数q1*q2的乘积, 将结果存储到dst中。
     * 
     * @param q1 @~english The first quaternion.
     * @~chinese 第一个四元数。
     * @param q2 @~english The second quaternion.
     * @~chinese 第二个四元数。
     * @param dst @~english A quaternion to store the result in.
     * @~chinese 存储计算结果。
     */
    static void multiply(const Quaternion& q1, const Quaternion& q2, Quaternion* dst);

    /**@~english
     * Normalizes this quaternion to have unit length.
     *
     * If the quaternion already has unit length or if the length
     * of the quaternion is zero, this method does nothing.
     * @~chinese 
     * 归一化四元数
     * 
     * 如果四元数已经归一化或长度为0，那么该函数什么也不做。
     */
    void normalize();

    /**@~english
     * Get the normalized quaternion.
     *
     * If the quaternion already has unit length or if the length
     * of the quaternion is zero, this method simply copies
     * this vector.
     * @~chinese 
     * 得到四元数的归一化结果。
     * 
     * 如果四元数已经归一化或长度为0，那么该函数将返回自身。
     */
    Quaternion getNormalized() const;

    /**@~english
     * Sets the elements of the quaternion to the specified values.
     *
     * @~chinese 
     * 将四元数的元素设置为指定的值。
     * 
     * @param xx @~english The new x-value.
     * @~chinese 新的x值。
     * @param yy @~english The new y-value.
     * @~chinese 新的y值。
     * @param zz @~english The new z-value.
     * @~chinese 新的z值。
     * @param ww @~english The new w-value.
     * @~chinese 新的w值。
     */
    void set(float xx, float yy, float zz, float ww);

    /**@~english
     * Sets the elements of the quaternion from the values in the specified array.
     *
     * @~chinese 
     * 将四元数的元素设置为指定值。
     * 
     * @param array @~english An array containing the elements of the quaternion in the order x, y, z, w.
     * @~chinese 一个数组,其中包含的元素按顺序分别对应四元数x,y,z,w分量。
     */
    void set(float* array);

    /**@~english
     * Sets the quaternion equal to the rotational part of the specified matrix.
     *
     * @~chinese 
     * 从矩阵中得到旋转四元数，将四元数设置为该值。
     * 
     * @param m @~english The matrix.
     * @~chinese 矩阵。
     */
    void set(const Mat4& m);

    /**@~english
     * Sets the quaternion equal to the rotation from the specified axis and angle.
     * 
     * @~chinese 
     * 从旋转轴和旋转角度中得到旋转四元数，将四元数设置为该值。
     * 
     * @param axis @~english The axis of rotation.
     * @~chinese 旋转轴。
     * @param angle @~english The angle of rotation (in radians).
     * @~chinese 旋转角度(弧度)。
     */
    void set(const Vec3& axis, float angle);

    /**@~english
     * Sets the elements of this quaternion to a copy of the specified quaternion.
     *
     * @~chinese 
     * 将四元数设置为指定的四元数。
     * 
     * @param q @~english The quaternion to copy.
     * @~chinese 要复制的四元数。
     */
    void set(const Quaternion& q);

    /**@~english
     * Sets this quaternion to be equal to the identity quaternion.
     * @~chinese 
     * 将四元数设置为单位四元数。
     */
    void setIdentity();

    /**@~english
     * Converts this Quaternion to axis-angle notation. The axis is normalized.
     *
     * @~chinese 
     * 将四元数转换为旋转轴和旋转角度，得到的旋转轴已经被归一化了。
     * 
     * @param e @~english The Vec3f which stores the axis.
     * 
     * @~chinese 得到的旋转轴。
     * 
     * @return @~english The angle (in radians).
     * @~chinese 旋转的角度(弧度)。
     */
    float toAxisAngle(Vec3* e) const;

    /**@~english
     * Interpolates between two quaternions using linear interpolation.
     *
     * The interpolation curve for linear interpolation between
     * quaternions gives a straight line in quaternion space.
     *
     * @~chinese 
     * 对两个四元数进行线性插值。
     * 其差值曲线在四元数空间中是一条直线
     * 
     * @param q1 @~english The first quaternion.
     * @~chinese 第一个四元数。
     * @param q2 @~english The second quaternion.
     * @~chinese 第二个四元数。
     * @param t @~english The interpolation coefficient.
     * @~chinese 差值系数。
     * @param dst @~english A quaternion to store the result in.
     * @~chinese 存储差值结果。
     */
    static void lerp(const Quaternion& q1, const Quaternion& q2, float t, Quaternion* dst);
    
    /**@~english
     * Interpolates between two quaternions using spherical linear interpolation.
     *
     * Spherical linear interpolation provides smooth transitions between different
     * orientations and is often useful for animating models or cameras in 3D.
     *
     * Note: For accurate interpolation, the input quaternions must be at (or close to) unit length.
     * This method does not automatically normalize the input quaternions, so it is up to the
     * caller to ensure they call normalize beforehand, if necessary.
     *
     * @~chinese 
     * 在两个四元数间使用球面线性差值。
     * 
     * 球形线性插值能在不同的旋转姿态中进行平滑过渡，通常用于物体和摄像机的3D动画
     * 
     * 注意:要想准确插值,输入四元数的长度比如是1（或者接近1）。
     * 这个方法不会自动归一化输入的四元数,所以请在计算之前请自行归一化。
     * 
     * @param q1 @~english The first quaternion.
     * @~chinese 第一个四元数。
     * @param q2 @~english The second quaternion.
     * @~chinese 第二个四元数。
     * @param t @~english The interpolation coefficient.
     * @~chinese 插法系数。
     * @param dst @~english A quaternion to store the result in.
     * @~chinese 存储插值结果。
     */
    static void slerp(const Quaternion& q1, const Quaternion& q2, float t, Quaternion* dst);
    
    /**@~english
     * Interpolates over a series of quaternions using spherical spline interpolation.
     *
     * Spherical spline interpolation provides smooth transitions between different
     * orientations and is often useful for animating models or cameras in 3D.
     *
     * Note: For accurate interpolation, the input quaternions must be unit.
     * This method does not automatically normalize the input quaternions,
     * so it is up to the caller to ensure they call normalize beforehand, if necessary.
     *
     * @~chinese 
     * 在一系列的四元数中，使用球面样条插值。
     * 
     * 球形样条插值能在不同的旋转姿态中进行平滑过渡，通常用于物体和摄像机的3D动画
     * 
     * 注意:要想准确插值,输入四元数的长度比如是1（或者接近1）。
     * 这个方法不会自动归一化输入的四元数,所以请在计算之前请自行归一化。
     * 
     * @param q1 @~english The first quaternion.
     * @~chinese 第一个四元数。
     * @param q2 @~english The second quaternion.
     * @~chinese 第二个四元数。
     * @param s1 @~english The first control point.
     * @~chinese 第一个控制点。
     * @param s2 @~english The second control point.
     * @~chinese 第二个控制点。
     * @param t @~english The interpolation coefficient.
     * @~chinese 插法系数。
     * @param dst @~english A quaternion to store the result in.
     * @~chinese 存储插值结果。
     */
    static void squad(const Quaternion& q1, const Quaternion& q2, const Quaternion& s1, const Quaternion& s2, float t, Quaternion* dst);

    /**@~english
     * Calculates the quaternion product of this quaternion with the given quaternion.
     * 
     * Note: this does not modify this quaternion.
     * 
     * @~chinese 
     * 计算该四元数和另一个四元数q的右乘乘积。
     * 
     * 注意:这并不修改该四元数。
     * 
     * @param q @~english The quaternion to multiply.
     * @~chinese 要右乘的四元数。
     * @return @~english The quaternion product.
     * @~chinese 乘积结果。
     */
    inline const Quaternion operator*(const Quaternion& q) const;

    /**@~english
     * Calculates the quaternion product of this quaternion with the given vec3.
     * @~chinese 
     * 使用该四元数变换一个向量。
     * @param v @~english The vec3 to multiply.
     * @~chinese 要变换的向量。
     * @return @~english The vec3 product.
     * @~chinese 变换后的向量。
     */
    inline Vec3 operator*(const Vec3& v) const;

    /**@~english
     * Multiplies this quaternion with the given quaternion.
     * 
     * @~chinese 
     * 将该四元数右乘另一个四元数q，结果保存在this中。
     * 
     * @param q @~english The quaternion to multiply.
     * @~chinese 要右乘的四元数。
     * @return @~english This quaternion, after the multiplication occurs.
     * @~chinese 右乘计算的结果。
     */
    inline Quaternion& operator*=(const Quaternion& q);
    
    /** @~english equals to Quaternion(0,0,0, 0)  @~chinese 等于四元数(0,0,0,0)*/
    static const Quaternion ZERO;

private:

    /**
     * Interpolates between two quaternions using spherical linear interpolation.
     *
     * Spherical linear interpolation provides smooth transitions between different
     * orientations and is often useful for animating models or cameras in 3D.
     *
     * Note: For accurate interpolation, the input quaternions must be at (or close to) unit length.
     * This method does not automatically normalize the input quaternions, so it is up to the
     * caller to ensure they call normalize beforehand, if necessary.
     *
     * @param q1x The x component of the first quaternion.
     * @param q1y The y component of the first quaternion.
     * @param q1z The z component of the first quaternion.
     * @param q1w The w component of the first quaternion.
     * @param q2x The x component of the second quaternion.
     * @param q2y The y component of the second quaternion.
     * @param q2z The z component of the second quaternion.
     * @param q2w The w component of the second quaternion.
     * @param t The interpolation coefficient.
     * @param dstx A pointer to store the x component of the slerp in.
     * @param dsty A pointer to store the y component of the slerp in.
     * @param dstz A pointer to store the z component of the slerp in.
     * @param dstw A pointer to store the w component of the slerp in.
     */
    static void slerp(float q1x, float q1y, float q1z, float q1w, float q2x, float q2y, float q2z, float q2w, float t, float* dstx, float* dsty, float* dstz, float* dstw);

    static void slerpForSquad(const Quaternion& q1, const Quaternion& q2, float t, Quaternion* dst);
};

NS_CC_MATH_END
/**
 end of base group
 @}
 */
#include "Quaternion.inl"

#endif
