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

#ifndef MATH_MAT4_H
#define MATH_MAT4_H

#include "base/ccMacros.h"

#include "math/Vec3.h"
#include "math/Vec4.h"

#ifdef __SSE__
#include <xmmintrin.h>
#endif

/**
 * @addtogroup base
 * @{
 */

NS_CC_MATH_BEGIN

//class Plane;

/**
@class Mat4
@brief
@~english
 * Defines a 4 x 4 floating point matrix representing a 3D transformation.
 *
 * Vectors are treated as columns, resulting in a matrix that is represented as follows,
 * where x, y and z are the translation components of the matrix:
 *
 *     1  0  0  x
 *     0  1  0  y
 *     0  0  1  z
 *     0  0  0  1
 *
 * This matrix class is directly compatible with OpenGL since its elements are
 * laid out in memory exactly as they are expected by OpenGL.
 * The matrix uses column-major format such that array indices increase down column first.
 * Since matrix multiplication is not commutative, multiplication must be done in the
 * correct order when combining transformations. Suppose we have a translation
 * matrix T and a rotation matrix R. To first rotate an object around the origin
 * and then translate it, you would multiply the two matrices as TR.
 *
 * Likewise, to first translate the object and then rotate it, you would do RT.
 * So generally, matrices must be multiplied in the reverse order in which you
 * want the transformations to take place (this also applies to
 * the scale, rotate, and translate methods below; these methods are convenience
 * methods for post-multiplying by a matrix representing a scale, rotation, or translation).
 *
 * @~chinese 
 * 该类定义了一个4×4浮点矩阵,可以用于表示一个3d转换。
 * 
 * 矩阵是按照列优先的方式进行组织的,所以，一个只包含平移(x,y,z)的矩阵是这样的:
 * 
 * 1 0 0 x
 * 0 1 0 y
 * 0 0 1 z
 * 0 0 0 1
 * 
 * 这个矩阵直接兼容openGL，因为其内存组织方式和openGL的矩阵组织方式相同。
 * 矩阵使用列优先的组织方式,起索引会优先按照列顺序。
 * 因为矩阵乘法中，矩阵顺序不可交换,所以其结果需要按照正确的顺序来计算
 * 假设我们有一个平移T和一个旋转矩阵R，如果需要首先旋转物体，然后再平移，那么复合矩阵应该是T*R
 * 
 * 同样,首先把对象平移,然后旋转,你需要做R*T的运算。
 * 所以一般来说,矩阵乘法的顺序和你对物体进行变换的顺序正好相反(这也适用于
 * 缩放、旋转和下面的平移函数,这些方法是便利函数
 * 其通过右乘矩阵来实现一个缩放,旋转,或平移)。
 * 
 */
class CC_DLL Mat4
{
public:
    // //temp add conversion
    // operator kmMat4() const
    // {
    //     kmMat4 result;
    //     kmMat4Fill(&result, m);
    //     return result;
    // }
    
    // Mat4(const kmMat4& mat)
    // {
    //     set(mat.mat);
    // }
    /**@~english
     * Stores the columns of this 4x4 matrix.
     * @~chinese 
     * 商店的4 x4矩阵的列。
     * */
#ifdef __SSE__
    union {
        __m128 col[4];
        float m[16];
    };
#else
    float m[16];
#endif

    /** @~english
     * Default constructor.
     * Constructs a matrix initialized to the identity matrix:
     *
     *     1  0  0  0
     *     0  1  0  0
     *     0  0  1  0
     *     0  0  0  1
     * @~chinese 
     * 默认构造函数。
     * 构造一个单位矩阵:
     * 
     * 1 0 0 0
     * 1 0 0 0
     * 1 0 0 0
     * 0 0 0 1
     */
    Mat4();

    /**@~english
     * Constructs a matrix initialized to the specified value.
     *
     * @~chinese 
     * 构造一个矩阵初始化为指定的值。
     * 
     * @param m11 @~english The first element of the first row.
     * @~chinese 第一行的第一个元素。
     * @param m12 @~english The second element of the first row.
     * @~chinese 第一行的第二个元素。
     * @param m13 @~english The third element of the first row.
     * @~chinese 第一行的第三个元素。
     * @param m14 @~english The fourth element of the first row.
     * @~chinese 第一行的第四个元素。
     * @param m21 @~english The first element of the second row.
     * @~chinese 第二行的第一个元素。
     * @param m22 @~english The second element of the second row.
     * @~chinese 第二行的第二个元素。
     * @param m23 @~english The third element of the second row.
     * @~chinese 第二行的第三个元素。
     * @param m24 @~english The fourth element of the second row.
     * @~chinese 第二行的第四个元素。
     * @param m31 @~english The first element of the third row.
     * @~chinese 第三行的第一个元素。
     * @param m32 @~english The second element of the third row.
     * @~chinese 第三行的第二个元素。
     * @param m33 @~english The third element of the third row.
     * @~chinese 第三行的第三个元素。
     * @param m34 @~english The fourth element of the third row.
     * @~chinese 第三行的第四个元素。
     * @param m41 @~english The first element of the fourth row.
     * @~chinese 第四行的第一个元素。
     * @param m42 @~english The second element of the fourth row.
     * @~chinese 第四行的第二个元素。
     * @param m43 @~english The third element of the fourth row.
     * @~chinese 第四行的第三个元素。
     * @param m44 @~english The fourth element of the fourth row.
     * @~chinese 第四行的第四个元素。
     */
    Mat4(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24,
           float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44);

    /**@~english
     * Creates a matrix initialized to the specified column-major array.
     *
     * The passed-in array is in column-major order, so the memory layout of the array is as follows:
     *
     *     0   4   8   12
     *     1   5   9   13
     *     2   6   10  14
     *     3   7   11  15
     *
     * @~chinese 
     * 创建一个矩阵，参数数组被视为列优先的组织方式。
     * 
     * 传入的数组被视为按照列优先方式组织,所以数组的内存布局如下:
     * 
     *    0   4   8   12
     *    1   5   9   13
     *    2   6   10  14
     *    3   7   11  15
     * 
     * @param mat @~english An array containing 16 elements in column-major order.
     * @~chinese 一个数组,其中包含16个元素，以列优先方式组织。
     */
    Mat4(const float* mat);

    /**@~english
     * Constructs a new matrix by copying the values from the specified matrix.
     *
     * @~chinese 
     * 拷贝构造函数。
     * 
     * @param copy @~english The matrix to copy.
     * @~chinese 要复制的矩阵。
     */
    Mat4(const Mat4& copy);

    /**@~english
     * Destructor.
     * @~chinese 
     * 析构函数。
     */
    ~Mat4();

    /**@~english
     * Creates a view matrix based on the specified input parameters.
     *
     * @~chinese 
     * 根据指定的输入参数创建一个视图矩阵。
     * 
     * @param eyePosition @~english The eye position.
     * @~chinese 视点的位置。
     * @param targetPosition @~english The target's center position.
     * @~chinese 目标的中心位置。
     * @param up @~english The up vector.
     * @~chinese up的向量。
     * @param dst @~english A matrix to store the result in.
     * @~chinese 返回的结果矩阵。
     */
    static void createLookAt(const Vec3& eyePosition, const Vec3& targetPosition, const Vec3& up, Mat4* dst);

    /**@~english
     * Creates a view matrix based on the specified input parameters.
     *
     * @~chinese 
     * 创建一个视图矩阵根据指定的输入参数。
     * 
     * @param eyePositionX @~english The eye x-coordinate position.
     * @~chinese 视点的x坐标。
     * @param eyePositionY @~english The eye y-coordinate position.
     * @~chinese 视点的y坐标。
     * @param eyePositionZ @~english The eye z-coordinate position.
     * @~chinese 视点的z坐标。
     * @param targetCenterX @~english The target's center x-coordinate position.
     * @~chinese 目标中心的x坐标。
     * @param targetCenterY @~english The target's center y-coordinate position.
     * @~chinese 目标中心的y坐标。
     * @param targetCenterZ @~english The target's center z-coordinate position.
     * @~chinese 目标的中心z坐标。
     * @param upX @~english The up vector x-coordinate value.
     * @~chinese up向量x坐标的值。
     * @param upY @~english The up vector y-coordinate value.
     * @~chinese up向量y坐标的值。
     * @param upZ @~english The up vector z-coordinate value.
     * @~chinese up向量z坐标的值。
     * @param dst @~english A matrix to store the result in.
     * @~chinese 返回的结果矩阵。
     */
    static void createLookAt(float eyePositionX, float eyePositionY, float eyePositionZ,
                             float targetCenterX, float targetCenterY, float targetCenterZ,
                             float upX, float upY, float upZ, Mat4* dst);

    /**@~english
     * Builds a perspective projection matrix based on a field of view and returns by value.
     *
     * Projection space refers to the space after applying projection transformation from view space.
     * After the projection transformation, visible content has x- and y-coordinates ranging from -1 to 1,
     * and a z-coordinate ranging from 0 to 1. 
     * @~chinese 
     * 基于Fov来构建一个投影矩阵。
     * 
     * 投影空间指的是空间从视点空间应用投影变换后的空间。
     * 投影变换后,可见内容的x和y的坐标值位于－1到1之前，Z位于0到1之间,
     * 
     * @param fieldOfView @~english The field of view in the y direction (in degrees).
     * @~chinese 在y轴方向的FOV。
     * @param aspectRatio @~english The aspect ratio, defined as view space width divided by height.
     * @~chinese 宽高比,定义为视图空间宽度除以高度。
     * @param zNearPlane @~english The distance to the near view plane.
     * @~chinese 到近裁减面的距离。
     * @param zFarPlane @~english The distance to the far view plane.
     * @~chinese 到远裁减面的距离。
     * @param dst @~english A matrix to store the result in.
     * @~chinese 存储投影矩阵。
     */
    static void createPerspective(float fieldOfView, float aspectRatio, float zNearPlane, float zFarPlane, Mat4* dst);

    /**@~english
     * Creates an orthographic projection matrix.
     *
     * @~chinese 
     * 创建一个正射投影矩阵。
     * 
     * @param width @~english The width of the view.
     * @~chinese 视图的宽度。
     * @param height @~english The height of the view.
     * @~chinese 视图的高度。
     * @param zNearPlane @~english The minimum z-value of the view volume.
     * @~chinese 到近裁减面的距离。
     * @param zFarPlane @~english The maximum z-value of the view volume.
     * @~chinese 到远裁减面的距离。
     * @param dst @~english A matrix to store the result in.
     * @~chinese 存储投影矩阵。
     */
    static void createOrthographic(float width, float height, float zNearPlane, float zFarPlane, Mat4* dst);

    /**@~english
     * Creates an orthographic projection matrix.
     * 
     * @~chinese 
     * 创建一个正交投影矩阵。
     * 
     * @param left @~english The minimum x-value of the view volume.
     * @~chinese 视点坐标系下最小可见的X值。
     * @param right @~english The maximum x-value of the view volume.
     * @~chinese 视点坐标系下最大可见的X值。
     * @param bottom @~english The minimum y-value of the view volume.
     * @~chinese 视点坐标系下最小可见的Y值。
     * @param top @~english The maximum y-value of the view volume.
     * @~chinese 视点坐标系下最大可见的Y值。
     * @param zNearPlane @~english The minimum z-value of the view volume.
     * @~chinese 到近裁减面的距离。
     * @param zFarPlane @~english The maximum z-value of the view volume.
     * @~chinese 到远裁减面的距离。
     * @param dst @~english A matrix to store the result in.
     * @~chinese 存储投影矩阵。
     */
    static void createOrthographicOffCenter(float left, float right, float bottom, float top,
                                            float zNearPlane, float zFarPlane, Mat4* dst);

    /**@~english
     * Creates a spherical billboard that rotates around a specified object position.
     *
     * This method computes the facing direction of the billboard from the object position
     * and camera position. When the object and camera positions are too close, the matrix
     * will not be accurate. To avoid this problem, this method defaults to the identity
     * rotation if the positions are too close. (See the other overload of createBillboard
     * for an alternative approach).
     *
     * @~chinese 
     * 创建一个球形Billborad，该bilboard会绕着某一个点旋转。
     * 
     * 该方法会利用物体位置和摄像机位置来计算Billborad的朝向，如果物体和摄像机太近，矩阵可能不准确，
     * 为了避免这个问题，当两者太近时，会利用单位矩阵作为旋转也计算朝向。
     * 
     * @param objectPosition @~english The position of the object the billboard will rotate around.
     * @~chinese billboard旋转的中心。
     * @param cameraPosition @~english The position of the camera.
     * @~chinese 摄像机的位置。
     * @param cameraUpVector @~english The up vector of the camera.
     * @~chinese 相机的up向量。
     * @param dst @~english A matrix to store the result in.
     * @~chinese 存储结果矩阵。
     */
    static void createBillboard(const Vec3& objectPosition, const Vec3& cameraPosition,
                                const Vec3& cameraUpVector, Mat4* dst);

    /**@~english
     * Creates a spherical billboard that rotates around a specified object position with
     * provision for a safe default orientation.
     *
     * This method computes the facing direction of the billboard from the object position
     * and camera position. When the object and camera positions are too close, the matrix
     * will not be accurate. To avoid this problem, this method uses the specified camera
     * forward vector if the positions are too close. (See the other overload of createBillboard
     * for an alternative approach).
     *
     * @~chinese 
     * 创建一个球形Billborad，该bilboard会绕着某一个点旋转。
     * 
     * 该方法会利用物体位置和摄像机位置来计算Billborad的朝向，如果物体和摄像机太近，矩阵可能不准确，
     * 为了避免这个问题，当两者太近时，会利用摄像机的forward来计算朝向
     * 
     * @param objectPosition @~english The position of the object the billboard will rotate around.
     * @~chinese billboard旋转的中心。
     * @param cameraPosition @~english The position of the camera.
     * @~chinese 摄像机的位置。
     * @param cameraUpVector @~english The up vector of the camera.
     * @~chinese 相机的up向量。
     * @param cameraForwardVector @~english The forward vector of the camera, used if the positions are too close.
     * @~chinese 相机的forward向量,。
     * @param dst @~english A matrix to store the result in.
     * @~chinese 存储结果矩阵。
     */
    static void createBillboard(const Vec3& objectPosition, const Vec3& cameraPosition,
                                const Vec3& cameraUpVector, const Vec3& cameraForwardVector,
                                Mat4* dst);

    //Fills in an existing Mat4 so that it reflects the coordinate system about a specified Plane.
    //plane The Plane about which to create a reflection.
    //dst A matrix to store the result in.
    //static void createReflection(const Plane& plane, Mat4* dst);

    /**@~english
     * Creates a scale matrix.
     *
     * @~chinese 
     * 通过缩放创建一个矩阵。
     * 
     * @param scale @~english The amount to scale.
     * @~chinese 缩放值。
     * @param dst @~english A matrix to store the result in.
     * @~chinese 存储结果矩阵。
     */
    static void createScale(const Vec3& scale, Mat4* dst);

    /**@~english
     * Creates a scale matrix.
     *
     * @~chinese 
     * 基于缩放创建一个矩阵。
     * 
     * @param xScale @~english The amount to scale along the x-axis.
     * @~chinese 沿着x轴的缩放。
     * @param yScale @~english The amount to scale along the y-axis.
     * @~chinese 沿着y轴的缩放。
     * @param zScale @~english The amount to scale along the z-axis.
     * @~chinese 沿着z轴的缩放。
     * @param dst @~english A matrix to store the result in.
     * @~chinese 存储结果矩阵。
     */
    static void createScale(float xScale, float yScale, float zScale, Mat4* dst);

    /**@~english
     * Creates a rotation matrix from the specified quaternion.
     *
     * @~chinese 
     * 基于四元数旋转来创建一个矩阵。
     * 
     * @param quat @~english A quaternion describing a 3D orientation.
     * @~chinese 一个用于描述3D旋转的四元数。
     * @param dst @~english A matrix to store the result in.
     * @~chinese 存储结果矩阵。
     */
    static void createRotation(const Quaternion& quat, Mat4* dst);

    /**@~english
     * Creates a rotation matrix from the specified axis and angle.
     *
     * @~chinese 
     * 通过绕轴旋转来创建一个变换矩阵。
     * 
     * @param axis @~english A vector describing the axis to rotate about.
     * @~chinese 旋转的轴。
     * @param angle @~english The angle (in radians).
     * @~chinese 旋转的角度(弧度)。
     * @param dst @~english A matrix to store the result in.
     * @~chinese 存储结果矩阵。
     */
    static void createRotation(const Vec3& axis, float angle, Mat4* dst);

    /**@~english
     * Creates a matrix describing a rotation around the x-axis.
     *
     * @~chinese 
     * 绕X轴旋转来创建一个变换矩阵。
     * 
     * @param angle @~english The angle of rotation (in radians).
     * @~chinese 绕X轴旋转的角度(弧度)。
     * @param dst @~english A matrix to store the result in.
     * @~chinese 存储结果矩阵。
     */
    static void createRotationX(float angle, Mat4* dst);

    /**@~english
     * Creates a matrix describing a rotation around the y-axis.
     *
     * @~chinese 
     * 绕Y轴旋转来创建一个变换矩阵。
     * 
     * @param angle @~english The angle of rotation (in radians).
     * @~chinese 绕Y轴旋转的角度(弧度)。
     * @param dst @~english A matrix to store the result in.
     * @~chinese 存储结果矩阵。
     */
    static void createRotationY(float angle, Mat4* dst);

    /**@~english
     * Creates a matrix describing a rotation around the z-axis.
     *
     * @~chinese 
     * 绕Z轴旋转来创建一个变换矩阵。
     * 
     * @param angle @~english The angle of rotation (in radians).
     * @~chinese 绕Z轴旋转的角度(弧度)。
     * @param dst @~english A matrix to store the result in.
     * @~chinese 存储结果矩阵。
     */
    static void createRotationZ(float angle, Mat4* dst);

    /**@~english
     * Creates a translation matrix.
     *
     * @~chinese 
     * 基于平移创建一个变换矩阵。
     * 
     * @param translation @~english The translation.
     * @~chinese 平移。
     * @param dst @~english A matrix to store the result in.
     * @~chinese 存储结果矩阵。
     */
    static void createTranslation(const Vec3& translation, Mat4* dst);

    /**@~english
     * Creates a translation matrix.
     *
     * @~chinese 
     * 基于平移创建一个变换矩阵。
     * 
     * @param xTranslation @~english The translation on the x-axis.
     * @~chinese 在x轴上的平移。
     * @param yTranslation @~english The translation on the y-axis.
     * @~chinese 在y轴上的平移。
     * @param zTranslation @~english The translation on the z-axis.
     * @~chinese 在z轴上的平移。
     * @param dst @~english A matrix to store the result in.
     * @~chinese 存储结果矩阵。
     */
    static void createTranslation(float xTranslation, float yTranslation, float zTranslation, Mat4* dst);

    /**@~english
     * Adds a scalar value to each component of this matrix.
     *
     * @~chinese 
     * 对矩阵的每一个元素加上scalar，然后保存到this中
     * 
     * @param scalar @~english The scalar to add.
     * @~chinese 要加上的scalar值。
     */
    void add(float scalar);

    /**@~english
     * Adds a scalar value to each component of this matrix and stores the result in dst.
     *
     * @~chinese 
     * 对矩阵的每一个元素加上scalar，然后保存到dst中。
     * 
     * @param scalar @~english The scalar value to add.
     * @~chinese 要加上的scalar值。
     * @param dst @~english A matrix to store the result in.
     * @~chinese 用于储存计算结果。
     */
    void add(float scalar, Mat4* dst);

    /**@~english
     * Adds the specified matrix to this matrix.
     *
     * @~chinese 
     * 用this矩阵加上一个给定的矩阵。
     * 
     * @param mat @~english The matrix to add.
     * @~chinese 要加上的矩阵。
     */
    void add(const Mat4& mat);

    /**@~english
     * Adds the specified matrices and stores the result in dst.
     *
     * @~chinese 
     * 计算两个矩阵的和。
     * 
     * @param m1 @~english The first matrix.
     * @~chinese 第一个矩阵。
     * @param m2 @~english The second matrix.
     * @~chinese 第二个矩阵。
     * @param dst @~english The destination matrix to add to.
     * @~chinese 存储计算结果。
     */
    static void add(const Mat4& m1, const Mat4& m2, Mat4* dst);

    /**@~english
     * Decomposes the scale, rotation and translation components of this matrix.
     *
     * @~chinese 
     * 将矩阵分解为平移，旋转和缩放分量。
     * 
     * @param scale @~english The scale.
     * @~chinese 缩放分量。
     * @param rotation @~english The rotation.
     * @~chinese 旋转分量。
     * @param translation @~english The translation.
     * @~chinese 平移分量。
     */
    bool decompose(Vec3* scale, Quaternion* rotation, Vec3* translation) const;

    /**@~english
     * Computes the determinant of this matrix.
     *
     * @~chinese 
     * 计算矩阵的行列式的秩。
     * 
     * @return @~english The determinant.
     * @~chinese 矩阵的行列式的秩。
     */
    float determinant() const;

    /**@~english
     * Gets the scalar component of this matrix in the specified vector.
     *
     * If the scalar component of this matrix has negative parts,
     * it is not possible to always extract the exact scalar component;
     * instead, a scale vector that is mathematically equivalent to the
     * original scale vector is extracted and returned.
     *
     * @~chinese 
     * 得到这个矩阵的缩放分量。
     * 
     * 如果这个矩阵有负缩放部分，那么不可能准确得到原始的缩放分量，
     * 返回的几个分量的结果
     * 
     * @param scale @~english A vector to receive the scale.
     * @~chinese 用于保存缩放分量。
     */
    void getScale(Vec3* scale) const;

    /**@~english
     * Gets the rotational component of this matrix in the specified quaternion.
     *
     * @~chinese 
     * 得到矩阵的旋转分量。
     * 
     * @param rotation @~english A quaternion to receive the rotation.
     * 
     * @~chinese 接收旋转四元数。
     * 
     * @return @~english true if the rotation is successfully extracted, false otherwise.
     * @~chinese 如果成功提取旋转，返回真,否则返回假。
     */
    bool getRotation(Quaternion* rotation) const;

    /**@~english
     * Gets the translational component of this matrix in the specified vector.
     *
     * @~chinese 
     * 得到这个矩阵的平移分量。
     * 
     * @param translation @~english A vector to receive the translation.
     * @~chinese 用于存储平移分量
     */
    void getTranslation(Vec3* translation) const;

    /**@~english
     * Gets the up vector of this matrix.
     *
     * @~chinese 
     * 得到向上的向量，相当于变换Vec3(0,1,0)。
     * 
     * @param dst @~english The destination vector.
     * @~chinese 用于存储目标向量。
     */
    void getUpVector(Vec3* dst) const;

    /**@~english
     * Gets the down vector of this matrix.
     *
     * @~chinese 
     * 得到向下的向量，相当于变换Vec3(0,-1,0)。
     * 
     * @param dst @~english The destination vector.
     * @~chinese 用于存储目标向量。
     */
    void getDownVector(Vec3* dst) const;

    /**@~english
     * Gets the left vector of this matrix.
     *
     * @~chinese 
     * 得到向左的向量，相当于变换Vec3(－1,0,0)。
     * 
     * @param dst @~english The destination vector.
     * @~chinese 用于存储目标向量。
     */
    void getLeftVector(Vec3* dst) const;

    /**@~english
     * Gets the right vector of this matrix.
     *
     * @~chinese 
     * 得到向右的向量，相当于变换Vec3(1,0,0)。
     * 
     * @param dst @~english The destination vector.
     * @~chinese 用于存储目标向量。
     */
    void getRightVector(Vec3* dst) const;

    /**@~english
     * Gets the forward vector of this matrix.
     *
     * @~chinese 
     * 得到向前的向量,相当于变换Vec3(0,0,－1)。
     * 
     * @param dst @~english The destination vector.
     * @~chinese 用于存储目标向量。
     */
    void getForwardVector(Vec3* dst) const;

    /**@~english
     * Gets the backward vector of this matrix.
     *
     * @~chinese 
     * 得到向后的向量,相当于变换Vec3(0,0,1)。
     * 
     * @param dst @~english The destination vector.
     * @~chinese 用于存储目标向量。
     */
    void getBackVector(Vec3* dst) const;

    /**@~english
     * Inverts this matrix.
     *
     * @~chinese 
     * 对这个矩阵求逆，保存在this中。
     * 
     * @return @~english true if the the matrix can be inverted, false otherwise.
     * @~chinese 如果矩阵可以求逆，返回真,否则返回假。
     */
    bool inverse();

    /**@~english
     * Get the inversed matrix.
     * @~chinese 
     * 得到逆矩阵m(m*this = this *m = IDENTITY)。
     */
    Mat4 getInversed() const;

    /**@~english
     * Determines if this matrix is equal to the identity matrix.
     *
     * @~chinese 
     * 确定是否这个矩阵等于单位矩阵。
     * 
     * @return @~english true if the matrix is an identity matrix, false otherwise.
     * @~chinese 如果矩阵是一个单位矩阵,则返回真，否则返回假。
     */
    bool isIdentity() const;

    /**@~english
     * Multiplies the components of this matrix by the specified scalar.
     *
     * @~chinese 
     * 对矩阵的每一个元素乘以scalar，保存在this中。
     * 
     * @param scalar @~english The scalar value.
     * @~chinese 标量值。
     */
    void multiply(float scalar);

    /**@~english
     * Multiplies the components of this matrix by a scalar and stores the result in dst.
     *
     * @~chinese 
     * 对矩阵的每一个元素乘以scalar，保存在dst中.
     * 
     * @param scalar @~english The scalar value.
     * @~chinese 标量值。
     * @param dst @~english A matrix to store the result in.
     * @~chinese 保存计算的结果。
     */
    void multiply(float scalar, Mat4* dst) const;

    /**@~english
     * Multiplies the components of the specified matrix by a scalar and stores the result in dst.
     *
     * @~chinese 
     * 对矩阵mat的每一个元素乘以scalar，保存在dst中.
     * 
     * @param mat @~english The matrix.
     * @~chinese 矩阵。
     * @param scalar @~english The scalar value.
     * @~chinese 标量值。
     * @param dst @~english A matrix to store the result in.
     * @~chinese 保存计算的结果。
     */
    static void multiply(const Mat4& mat, float scalar, Mat4* dst);

    /**@~english
     * Multiplies this matrix by the specified one.
     *
     * @~chinese 
     * 右乘矩阵并且保存在this中。
     * 
     * @param mat @~english The matrix to multiply.
     * @~chinese 要右乘的矩阵。
     */
    void multiply(const Mat4& mat);

    /**@~english
     * Multiplies m1 by m2 and stores the result in dst.
     *
     * @~chinese 
     * 计算矩阵m1*m2。
     * 
     * @param m1 @~english The first matrix to multiply.
     * @~chinese 第一个矩阵m1。
     * @param m2 @~english The second matrix to multiply.
     * @~chinese 第二个矩阵m2。
     * @param dst @~english A matrix to store the result in.
     * @~chinese 保存计算的结果。
     */
    static void multiply(const Mat4& m1, const Mat4& m2, Mat4* dst);

    /**@~english
     * Negates this matrix.
     * @~chinese 
     * 将矩阵求反(对每一个元素乘以－1)，并保存在this中。
     */
    void negate();

    /**@~english
     Get the Negated matrix.
     * @~chinese 
     * 得到反矩阵(对每一个元素乘以－1)。
     */
    Mat4 getNegated() const;

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified quaternion rotation.
     *
     * @~chinese 
     * 按照旋转计算出矩阵，并且将该矩阵右乘this，结果存储到this中。
     * 
     * @param q @~english The quaternion to rotate by.
     * @~chinese 旋转的四元数。
     */
    void rotate(const Quaternion& q);

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified quaternion rotation and stores the result in dst.
     *
     * @~chinese 
     * 按照旋转计算出矩阵，并且将该矩阵右乘this，结果存储到dst中。
     * 
     * @param q @~english The quaternion to rotate by.
     * @~chinese 旋转的四元数。
     * @param dst @~english A matrix to store the result in.
     * @~chinese 存储计算的结果。
     */
    void rotate(const Quaternion& q, Mat4* dst) const;

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified rotation about the specified axis.
     *
     * @~chinese 
     * 按照旋转计算出矩阵，并且将该矩阵右乘this，结果存储到this中。
     * 
     * @param axis @~english The axis to rotate about.
     * @~chinese 旋转的轴。
     * @param angle @~english The angle (in radians).
     * @~chinese 旋转的角度(弧度)。
     */
    void rotate(const Vec3& axis, float angle);

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the specified
     * rotation about the specified axis and stores the result in dst.
     *
     * @~chinese 
     * 按照旋转计算出矩阵，并且将该矩阵右乘this，结果存储到dst中。
     * 
     * @param axis @~english The axis to rotate about.
     * @~chinese 旋转的轴。
     * @param angle @~english The angle (in radians).
     * @~chinese 旋转的角度(弧度)。
     * @param dst @~english A matrix to store the result in.
     * @~chinese 存储计算的结果。
     */
    void rotate(const Vec3& axis, float angle, Mat4* dst) const;

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified rotation around the x-axis.
     *
     * @~chinese 
     * 按照旋转计算出矩阵，并且将该矩阵右乘this，结果存储到this中。
     * 
     * @param angle @~english The angle (in radians).
     * @~chinese 绕X轴旋转的角度(弧度)。
     */
    void rotateX(float angle);

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified rotation around the x-axis and stores the result in dst.
     *
     * @~chinese 
     * 按照旋转计算出矩阵，并且将该矩阵右乘this，结果存储到dst中。
     * 
     * @param angle @~english The angle (in radians).
     * @~chinese 绕X轴旋转的角度(弧度)。
     * @param dst @~english A matrix to store the result in.
     * @~chinese 存储计算的结果。
     */
    void rotateX(float angle, Mat4* dst) const;

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified rotation around the y-axis.
     *
     * @~chinese 
     * 按照旋转计算出矩阵，并且将该矩阵右乘this，结果存储到this中。
     * 
     * @param angle @~english The angle (in radians).
     * @~chinese 绕Y轴旋转的角度(弧度)。
     */
    void rotateY(float angle);

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified rotation around the y-axis and stores the result in dst.
     *
     * @~chinese 
     * 按照旋转计算出矩阵，并且将该矩阵右乘this，结果存储到dst中。
     * 
     * @param angle @~english The angle (in radians).
     * @~chinese 绕Y轴旋转的角度(弧度)。
     * @param dst @~english A matrix to store the result in.
     * @~chinese 存储计算的结果。
     */
    void rotateY(float angle, Mat4* dst) const;

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified rotation around the z-axis.
     *
     * @~chinese 
     * 按照旋转计算出矩阵，并且将该矩阵右乘this，结果存储到this中。
     * 
     * @param angle @~english The angle (in radians).
     * @~chinese 绕Z轴旋转的角度(弧度)。
     */
    void rotateZ(float angle);

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified rotation around the z-axis and stores the result in dst.
     *
     * @~chinese 
     * 按照旋转计算出矩阵，并且将该矩阵右乘this，结果存储到dst中。
     * 
     * @param angle @~english The angle (in radians).
     * @~chinese 绕Z轴旋转的角度(弧度)。
     * @param dst @~english A matrix to store the result in.
     * @~chinese 存储计算的结果。
     */
    void rotateZ(float angle, Mat4* dst) const;

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified scale transformation.
     *
     * @~chinese 
     * 按照scale计算出矩阵，并且将该矩阵右乘this，结果存储到this中。
     * 
     * @param value @~english The amount to scale along all axes.
     * @~chinese 等比缩放值。
     */
    void scale(float value);

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified scale transformation and stores the result in dst.
     *
     * @~chinese 
     * 按照scale计算出矩阵，并且将该矩阵右乘this，结果存储到dst中。
     * 
     * @param value @~english The amount to scale along all axes.
     * @~chinese 等比缩放值。
     * @param dst @~english A matrix to store the result in.
     * @~chinese 存储计算的结果。
     */
    void scale(float value, Mat4* dst) const;

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified scale transformation.
     *
     * @~chinese 
     * 按照scale计算出矩阵，并且将该矩阵右乘this，结果存储到this中。
     * 
     * @param xScale @~english The amount to scale along the x-axis.
     * @~chinese 沿着x轴的缩放。
     * @param yScale @~english The amount to scale along the y-axis.
     * @~chinese 沿着y轴的缩放。
     * @param zScale @~english The amount to scale along the z-axis.
     * @~chinese 沿着z轴的缩放。
     */
    void scale(float xScale, float yScale, float zScale);

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified scale transformation and stores the result in dst.
     *
     * @~chinese 
     * 按照scale计算出矩阵，并且将该矩阵右乘this，结果存储到dst中。
     * 
     * @param xScale @~english The amount to scale along the x-axis.
     * @~chinese 沿着x轴的缩放。
     * @param yScale @~english The amount to scale along the y-axis.
     * @~chinese 沿着y轴的缩放。
     * @param zScale @~english The amount to scale along the z-axis.
     * @~chinese 沿着z轴的缩放。
     * @param dst @~english A matrix to store the result in.
     * @~chinese 存储计算的结果。
     */
    void scale(float xScale, float yScale, float zScale, Mat4* dst) const;

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified scale transformation.
     *
     * @~chinese 
    * 按照scale计算出矩阵，并且将该矩阵右乘this，结果存储到this中。
     * 
     * @param s @~english The scale values along the x, y and z axes.
     * @~chinese 缩放值。
     */
    void scale(const Vec3& s);

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified scale transformation and stores the result in dst.
     *
     * @~chinese 
     * 按照scale计算出矩阵，并且将该矩阵右乘this，结果存储到dst中。
     * 
     * @param s @~english The scale values along the x, y and z axes.
     * @~chinese 缩放值。
     * @param dst @~english A matrix to store the result in.
     * @~chinese 存储计算的结果。
     */
    void scale(const Vec3& s, Mat4* dst) const;

    /**@~english
     * Sets the values of this matrix.
     *
     * @~chinese 
     * 设置矩阵的值。
     * 
     * @param m11 @~english The first element of the first row.
     * @~chinese 第一行的第一个元素。
     * @param m12 @~english The second element of the first row.
     * @~chinese 第一行的第二个元素。
     * @param m13 @~english The third element of the first row.
     * @~chinese 第一行的第三个元素。
     * @param m14 @~english The fourth element of the first row.
     * @~chinese 第一行第四元素。
     * @param m21 @~english The first element of the second row.
     * @~chinese 第二行的第一个元素。
     * @param m22 @~english The second element of the second row.
     * @~chinese 第二行的第二个元素。
     * @param m23 @~english The third element of the second row.
     * @~chinese 第二行的第三个元素。
     * @param m24 @~english The fourth element of the second row.
     * @~chinese 第二行的第四个元素。
     * @param m31 @~english The first element of the third row.
     * @~chinese 第三行的第一个元素。
     * @param m32 @~english The second element of the third row.
     * @~chinese 第三行的第二个元素。
     * @param m33 @~english The third element of the third row.
     * @~chinese 第三行的第三个元素。
     * @param m34 @~english The fourth element of the third row.
     * @~chinese 第三行的第四个元素。
     * @param m41 @~english The first element of the fourth row.
     * @~chinese 第四行的第一个元素。
     * @param m42 @~english The second element of the fourth row.
     * @~chinese 第四行的第二个元素。
     * @param m43 @~english The third element of the fourth row.
     * @~chinese 第四行的第三个元素。
     * @param m44 @~english The fourth element of the fourth row.
     * @~chinese 第四行的第四个元素。
     */
    void set(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24,
             float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44);

    /**@~english
     * Sets the values of this matrix to those in the specified column-major array.
     *
     * @~chinese 
     * 这个矩阵的值设置为一个列优先数组的数据。
     * 
     * @param mat @~english An array containing 16 elements in column-major format.
     * @~chinese 列优先的数组。
     */
    void set(const float* mat);

    /**@~english
     * Sets the values of this matrix to those of the specified matrix.
     *
     * @~chinese 
     * 这个矩阵的值设置为指定的矩阵。
     * 
     * @param mat @~english The source matrix.
     * @~chinese 源矩阵。
     */
    void set(const Mat4& mat);

    /**@~english
     * Sets this matrix to the identity matrix.
     * @~chinese 
     * 这个矩阵设置为单位矩阵。
     */
    void setIdentity();

    /**@~english
     * Sets all elements of the current matrix to zero.
     * @~chinese 
     * 当前矩阵的所有元素设置为零。
     */
    void setZero();

    /**@~english
     * Subtracts the specified matrix from the current matrix.
     *
     * @~chinese 
     * 从当前矩阵减去一个矩阵
     * 
     * @param mat @~english The matrix to subtract.
     * @~chinese 要减去的矩阵。
     */
    void subtract(const Mat4& mat);

    /**@~english
     * Subtracts the specified matrix from the current matrix.
     *
     * @~chinese 
     * 两个矩阵相减
     * 
     * @param m1 @~english The first matrix.
     * @~chinese 第一个矩阵。
     * @param m2 @~english The second matrix.
     * @~chinese 第二个矩阵。
     * @param dst @~english A matrix to store the result in.
     * @~chinese 相减的结果。
     */
    static void subtract(const Mat4& m1, const Mat4& m2, Mat4* dst);

    /**@~english
     * Transforms the specified point by this matrix.
     *
     * The result of the transformation is stored directly into point.
     *
     * @~chinese 
     * 变换一个点，结果存储到要变换的点中
     * 
     * 
     * @param point @~english The point to transform and also a vector to hold the result in.
     * @~chinese 要变换的点。
     */
    inline void transformPoint(Vec3* point) const { GP_ASSERT(point); transformVector(point->x, point->y, point->z, 1.0f, point); }

    /**@~english
     * Transforms the specified point by this matrix, and stores
     * the result in dst.
     *
     * @~chinese 
     * 变换一个点，结果存储到dst中
     * 
     * @param point @~english The point to transform.
     * @~chinese 要变换的点。
     * @param dst @~english A vector to store the transformed point in.
     * @~chinese 变换后的结果。
     */
    inline void transformPoint(const Vec3& point, Vec3* dst) const { GP_ASSERT(dst); transformVector(point.x, point.y, point.z, 1.0f, dst); }

    /**@~english
     * Transforms the specified vector by this matrix by
     * treating the fourth (w) coordinate as zero.
     *
     * The result of the transformation is stored directly into vector.
     *
     * @~chinese 
     * 变换一个向量，第四个参数w被当作是0，结果直接存储到要变换的向量中
     * 
     * @param vector @~english The vector to transform and also a vector to hold the result in.
     * @~chinese 要变换的向量。
     */
    void transformVector(Vec3* vector) const;

    /**@~english
     * Transforms the specified vector by this matrix by
     * treating the fourth (w) coordinate as zero, and stores the
     * result in dst.
     *
     * @~chinese 
     * 变换一个向量，第四个参数w被当作是0，变换的结果存储在dst中
     * 
     * @param vector @~english The vector to transform.
     * @~chinese 要变换的向量。
     * @param dst @~english A vector to store the transformed vector in.
     * @~chinese 变换后的结果。
     */
    void transformVector(const Vec3& vector, Vec3* dst) const;

    /**@~english
     * Transforms the specified vector by this matrix.
     *
     * @~chinese 
     * 变换一个向量
     * 
     * @param x @~english The vector x-coordinate to transform by.
     * @~chinese 要变换向量的x坐标。
     * @param y @~english The vector y-coordinate to transform by.
     * @~chinese 要变换向量的y坐标。
     * @param z @~english The vector z-coordinate to transform by.
     * @~chinese 要变换向量的z坐标。
     * @param w @~english The vector w-coordinate to transform by.
     * @~chinese 要变换向量的w坐标。
     * @param dst @~english A vector to store the transformed point in.
     * @~chinese 变换后的结果。
     */
    void transformVector(float x, float y, float z, float w, Vec3* dst) const;

    /**@~english
     * Transforms the specified vector by this matrix.
     *
     * The result of the transformation is stored directly into vector.
     *
     * @~chinese 
     * 变换一个向量，变换结果直接保存在参数vector中
     * 
     * 
     * @param vector @~english The vector to transform.
     * @~chinese 要变换的向量。
     */
    void transformVector(Vec4* vector) const;

    /**@~english
     * Transforms the specified vector by this matrix.
     *
     * @~chinese 
     * 变换一个向量。
     * 
     * @param vector @~english The vector to transform.
     * @~chinese 要变换的向量。
     * @param dst @~english A vector to store the transformed point in.
     * @~chinese 变换后的结果。
     */
    void transformVector(const Vec4& vector, Vec4* dst) const;

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified translation.
     *
     * @~chinese 
     * 按照平移构建矩阵，并且将this与其右乘，结果存储到this中。
     * 
     * @param x @~english The amount to translate along the x-axis.
     * @~chinese 将沿着x轴的平移。
     * @param y @~english The amount to translate along the y-axis.
     * @~chinese 将沿着y轴的平移。
     * @param z @~english The amount to translate along the z-axis.
     * @~chinese 将沿着z轴的平移。
     */
    void translate(float x, float y, float z);

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified translation and stores the result in dst.
     *
     * @~chinese 
     * 按照平移构建矩阵，并且将其与this的右乘结果存储到dst中。
     * 
     * @param x @~english The amount to translate along the x-axis.
     * @~chinese 将沿着x轴的平移。
     * @param y @~english The amount to translate along the y-axis.
     * @~chinese 将沿着y轴的平移。
     * @param z @~english The amount to translate along the z-axis.
     * @~chinese 将沿着z轴的平移。
     * @param dst @~english A matrix to store the result in.
     * @~chinese 返回的结果。
     */
    void translate(float x, float y, float z, Mat4* dst) const;

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified translation.
     *
     * @~chinese 
     * 按照平移构建矩阵，并且将this与其右乘，结果存储到this中。
     * 
     * @param t @~english The translation values along the x, y and z axes.
     * @~chinese 沿x,y和z轴的平移。
     */
    void translate(const Vec3& t);

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified translation and stores the result in dst.
     *
     * @~chinese 
     * 按照平移构建矩阵，并且将其与this的右乘结果存储到dst中。
     * 
     * @param t @~english The translation values along the x, y and z axes.
     * @~chinese 沿x,y和z轴的平移。
     * @param dst @~english A matrix to store the result in.
     * @~chinese 返回的结果。
     */
    void translate(const Vec3& t, Mat4* dst) const;

    /**@~english
     * Transposes this matrix.
     * @~chinese 
     * 转置自己(行列互换)。
     */
    void transpose();

    /**@~english
     * Get the Transposed matrix.
     * @~chinese 
     * 得到转置矩阵(行列互换)。
     */
    Mat4 getTransposed() const;

    /**@~english
     * Calculates the sum of this matrix with the given matrix.
     * 
     * Note: this does not modify this matrix.
     * 
     * @~chinese 
     * 计算这个矩阵与给定的矩阵的相加。
     * 
     * 注意:这并不修改这个矩阵。
     * 
     * @param mat @~english The matrix to add.
     * @~chinese 要加的矩阵。
     * @return @~english The matrix sum.
     * @~chinese 两个矩阵之和。
     */
    inline const Mat4 operator+(const Mat4& mat) const;
    
    /**@~english
     * Adds the given matrix to this matrix.
     * 
     * @~chinese 
     * this矩阵加上给定的矩阵。
     * 
     * @param mat @~english The matrix to add.
     * @~chinese 要加的矩阵。
     * @return @~english This matrix, after the addition occurs.
     * @~chinese this矩阵加上之后，返回结果。
     */
    inline Mat4& operator+=(const Mat4& mat);

    /**@~english
     * Calculates the difference of this matrix with the given matrix.
     * 
     * Note: this does not modify this matrix.
     * 
     * @~chinese 
     * 计算这个矩阵的与给定的矩阵的相减。
     * 
     * 注意:这并不修改这个矩阵。
     * 
     * @param mat @~english The matrix to subtract.
     * @~chinese 要减去的矩阵。
     * @return @~english The matrix difference.
     * @~chinese 相减的结果。
     */
    inline const Mat4 operator-(const Mat4& mat) const;

    /**@~english
     * Subtracts the given matrix from this matrix.
     * 
     * @~chinese 
     * 从这个矩阵减去给定的矩阵。
     * 
     * @param mat @~english The matrix to subtract.
     * @~chinese 要减去的矩阵。
     * @return @~english This matrix, after the subtraction occurs.
     * @~chinese this矩阵减完后，返回减完后的矩阵
     */
    inline Mat4& operator-=(const Mat4& mat);

    /**@~english
     * Calculates the negation of this matrix.
     * 
     * Note: this does not modify this matrix.
     * 
     * @~chinese 
     * 对矩阵的求反，相当于乘以－1。
     * 
     * 注意:这并不修改这个矩阵。
     * 
     * @return @~english The negation of this matrix.
     * @~chinese 这个矩阵的反矩阵。
     */
    inline const Mat4 operator-() const;

    /**@~english
     * Calculates the matrix product of this matrix with the given matrix.
     * 
     * Note: this does not modify this matrix.
     * 
     * @~chinese 
     * 计算this矩阵左乘给定的矩阵的乘积。
     * 
     * 注意:这并不修改这个矩阵。
     * 
     * @param mat @~english The matrix to multiply by.
     * @~chinese 要被左乘的矩阵。
     * @return @~english The matrix product.
     * @~chinese 乘积结果。
     */
    inline const Mat4 operator*(const Mat4& mat) const;

    /**@~english
     * Right-multiplies this matrix by the given matrix.
     * 
     * @~chinese 
     * 用给定矩阵右乘自己
     * 
     * @param mat @~english The matrix to multiply by.
     * @~chinese 右乘的矩阵。
     * @return @~english This matrix, after the multiplication occurs.
     * @~chinese 右乘自己之后，返回结果
     */
    inline Mat4& operator*=(const Mat4& mat);

    /** @~english equals to a matrix full of zeros.  @~chinese 全零矩阵。*/
    static const Mat4 ZERO;
    /** @~english equals to the identity matrix.  @~chinese 单位矩阵。*/
    static const Mat4 IDENTITY;

private:

    static void createBillboardHelper(const Vec3& objectPosition, const Vec3& cameraPosition,
                                      const Vec3& cameraUpVector, const Vec3* cameraForwardVector,
                                      Mat4* dst);
};

/**@~english
 * Transforms the given vector by the given matrix.
 * 
 * Note: this treats the given vector as a vector and not as a point.
 * 
 * @~chinese 
 * 用给定的矩阵去变换一个向量。
 * 
 * 注:这对给定的向量作为一个向量,而不是一个点。
 * 
 * @param v @~english The vector to transform.
 * @~chinese 要变换的向量。
 * @param m @~english The matrix to transform by.
 * @~chinese 变换矩阵。
 * @return @~english This vector, after the transformation occurs.
 * @~chinese 返回变换后的向量。
 */
inline Vec3& operator*=(Vec3& v, const Mat4& m);

/**@~english
 * Transforms the given vector by the given matrix.
 * 
 * Note: this treats the given vector as a vector and not as a point.
 * 
 * @~chinese 
 * 用给定的矩阵去变换一个向量。
 * 
 * 注:这对给定的向量作为一个向量,而不是一个点。
 * 
 * @param m @~english The matrix to transform by.
 * @~chinese 变换矩阵。
 * @param v @~english The vector to transform.
 * @~chinese 要变换的向量。
 * @return @~english The resulting transformed vector.
 * @~chinese 返回变换后的向量。
 */
inline const Vec3 operator*(const Mat4& m, const Vec3& v);

/**@~english
 * Transforms the given vector by the given matrix.
 * 
 * Note: this treats the given vector as a vector and not as a point.
 * 
 * @~chinese 
 * 用给定的矩阵去变换一个向量。
 * 
 * 注:这对给定的向量作为一个向量,而不是一个点。
 * 
 * @param v @~english The vector to transform.
 * @~chinese 要变换的向量。
 * @param m @~english The matrix to transform by.
 * @~chinese 变换矩阵。
 * @return @~english This vector, after the transformation occurs.
 * @~chinese 返回变换后的向量。
 */
inline Vec4& operator*=(Vec4& v, const Mat4& m);

/**@~english
 * Transforms the given vector by the given matrix.
 * 
 * Note: this treats the given vector as a vector and not as a point.
 * 
 * @~chinese 
 * 用给定的矩阵去变换一个向量。
 * 
 * 注:这对给定的向量作为一个向量,而不是一个点。
 * 
 * @param m @~english The matrix to transform by.
 * @~chinese 变换矩阵。
 * @param v @~english The vector to transform.
 * @~chinese 要变换的向量。
 * @return @~english The resulting transformed vector.
 * @~chinese 返回变换后的向量。
 */
inline const Vec4 operator*(const Mat4& m, const Vec4& v);

NS_CC_MATH_END
/**
 end of base group
 @}
 */
#include "math/Mat4.inl"

#endif // MATH_MAT4_H
