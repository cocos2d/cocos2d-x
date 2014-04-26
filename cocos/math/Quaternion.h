#ifndef QUATERNION_H_
#define QUATERNION_H_

#include "Vector3.h"
#include "Matrix.h"
//#include "Plane.h"

NS_CC_MATH_BEGIN

class Matrix;

/**
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
 */
class Quaternion
{
    friend class Curve;
    friend class Transform;

public:

    /**
     * The x-value of the quaternion's vector component.
     */
    float x;
    /**
     * The y-value of the quaternion's vector component.
     */
    float y;
    /**
     * The z-value of the quaternion's vector component.
     */
    float z;
    /**
     * The scalar component of the quaternion.
     */
    float w;

    /**
     * Constructs a quaternion initialized to (0, 0, 0, 1).
     */
    Quaternion();

    /**
     * Constructs a quaternion initialized to (0, 0, 0, 1).
     *
     * @param xx The x component of the quaternion.
     * @param yy The y component of the quaternion.
     * @param zz The z component of the quaternion.
     * @param ww The w component of the quaternion.
     */
    Quaternion(float xx, float yy, float zz, float ww);

    /**
     * Constructs a new quaternion from the values in the specified array.
     *
     * @param array The values for the new quaternion.
     */
    Quaternion(float* array);

    /**
     * Constructs a quaternion equal to the rotational part of the specified matrix.
     *
     * @param m The matrix.
     */
    Quaternion(const Matrix& m);

    /**
     * Constructs a quaternion equal to the rotation from the specified axis and angle.
     *
     * @param axis A vector describing the axis of rotation.
     * @param angle The angle of rotation (in radians).
     */
    Quaternion(const Vector3& axis, float angle);

    /**
     * Constructs a new quaternion that is a copy of the specified one.
     *
     * @param copy The quaternion to copy.
     */
    Quaternion(const Quaternion& copy);

    /**
     * Destructor.
     */
    ~Quaternion();

    /**
     * Returns the identity quaternion.
     *
     * @return The identity quaternion.
     */
    static const Quaternion& identity();

    /**
     * Returns the quaternion with all zeros.
     *
     * @return The quaternion.
     */
    static const Quaternion& zero();

    /**
     * Determines if this quaternion is equal to the identity quaternion.
     *
     * @return true if it is the identity quaternion, false otherwise.
     */
    bool isIdentity() const;

    /**
     * Determines if this quaternion is all zeros.
     *
     * @return true if this quaternion is all zeros, false otherwise.
     */
    bool isZero() const;

    /**
     * Creates a quaternion equal to the rotational part of the specified matrix
     * and stores the result in dst.
     *
     * @param m The matrix.
     * @param dst A quaternion to store the conjugate in.
     */
    static void createFromRotationMatrix(const Matrix& m, Quaternion* dst);

    /**
     * Creates this quaternion equal to the rotation from the specified axis and angle
     * and stores the result in dst.
     *
     * @param axis A vector describing the axis of rotation.
     * @param angle The angle of rotation (in radians).
     * @param dst A quaternion to store the conjugate in.
     */
    static void createFromAxisAngle(const Vector3& axis, float angle, Quaternion* dst);

    /**
     * Sets this quaternion to the conjugate of itself.
     */
    void conjugate();

    /**
     * Gets the conjugate of this quaternion in dst.
     *
     * @param dst A quaternion to store the conjugate in.
     */
    void conjugate(Quaternion* dst) const;

    /**
     * Sets this quaternion to the inverse of itself.
     *
     * Note that the inverse of a quaternion is equal to its conjugate
     * when the quaternion is unit-length. For this reason, it is more
     * efficient to use the conjugate method directly when you know your
     * quaternion is already unit-length.
     *
     * @return true if the inverse can be computed, false otherwise.
     */
    bool inverse();

    /**
     * Gets the inverse of this quaternion in dst.
     *
     * Note that the inverse of a quaternion is equal to its conjugate
     * when the quaternion is unit-length. For this reason, it is more
     * efficient to use the conjugate method directly when you know your
     * quaternion is already unit-length.
     *
     * @param dst A quaternion to store the inverse in.
     * 
     * @return true if the inverse can be computed, false otherwise.
     */
    bool inverse(Quaternion* dst) const;

    /**
     * Multiplies this quaternion by the specified one and stores the result in this quaternion.
     *
     * @param q The quaternion to multiply.
     */
    void multiply(const Quaternion& q);

    /**
     * Multiplies the specified quaternions and stores the result in dst.
     *
     * @param q1 The first quaternion.
     * @param q2 The second quaternion.
     * @param dst A quaternion to store the result in.
     */
    static void multiply(const Quaternion& q1, const Quaternion& q2, Quaternion* dst);

    /**
     * Normalizes this quaternion to have unit length.
     *
     * If the quaternion already has unit length or if the length
     * of the quaternion is zero, this method does nothing.
     */
    void normalize();

    /**
     * Normalizes this quaternion and stores the result in dst.
     *
     * If the quaternion already has unit length or if the length
     * of the quaternion is zero, this method simply copies
     * this vector into dst.
     *
     * @param dst A quaternion to store the result in.
     */
    void normalize(Quaternion* dst) const;

    /**
     * Sets the elements of the quaternion to the specified values.
     *
     * @param xx The new x-value.
     * @param yy The new y-value.
     * @param zz The new z-value.
     * @param ww The new w-value.
     */
    void set(float xx, float yy, float zz, float ww);

    /**
     * Sets the elements of the quaternion from the values in the specified array.
     *
     * @param array An array containing the elements of the quaternion in the order x, y, z, w.
     */
    void set(float* array);

    /**
     * Sets the quaternion equal to the rotational part of the specified matrix.
     *
     * @param m The matrix.
     */
    void set(const Matrix& m);

    /**
     * Sets the quaternion equal to the rotation from the specified axis and angle.
     * 
     * @param axis The axis of rotation.
     * @param angle The angle of rotation (in radians).
     */
    void set(const Vector3& axis, float angle);

    /**
     * Sets the elements of this quaternion to a copy of the specified quaternion.
     *
     * @param q The quaternion to copy.
     */
    void set(const Quaternion& q);

    /**
     * Sets this quaternion to be equal to the identity quaternion.
     */
    void setIdentity();

    /**
     * Converts this Quaternion4f to axis-angle notation. The axis is normalized.
     *
     * @param e The Vector3f which stores the axis.
     * 
     * @return The angle (in radians).
     */
    float toAxisAngle(Vector3* e) const;

    /**
     * Interpolates between two quaternions using linear interpolation.
     *
     * The interpolation curve for linear interpolation between
     * quaternions gives a straight line in quaternion space.
     *
     * @param q1 The first quaternion.
     * @param q2 The second quaternion.
     * @param t The interpolation coefficient.
     * @param dst A quaternion to store the result in.
     */
    static void lerp(const Quaternion& q1, const Quaternion& q2, float t, Quaternion* dst);
    
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
     * @param q1 The first quaternion.
     * @param q2 The second quaternion.
     * @param t The interpolation coefficient.
     * @param dst A quaternion to store the result in.
     */
    static void slerp(const Quaternion& q1, const Quaternion& q2, float t, Quaternion* dst);
    
    /**
     * Interpolates over a series of quaternions using spherical spline interpolation.
     *
     * Spherical spline interpolation provides smooth transitions between different
     * orientations and is often useful for animating models or cameras in 3D.
     *
     * Note: For accurate interpolation, the input quaternions must be unit.
     * This method does not automatically normalize the input quaternions,
     * so it is up to the caller to ensure they call normalize beforehand, if necessary.
     *
     * @param q1 The first quaternion.
     * @param q2 The second quaternion.
     * @param s1 The first control point.
     * @param s2 The second control point.
     * @param t The interpolation coefficient.
     * @param dst A quaternion to store the result in.
     */
    static void squad(const Quaternion& q1, const Quaternion& q2, const Quaternion& s1, const Quaternion& s2, float t, Quaternion* dst);

    /**
     * Calculates the quaternion product of this quaternion with the given quaternion.
     * 
     * Note: this does not modify this quaternion.
     * 
     * @param q The quaternion to multiply.
     * @return The quaternion product.
     */
    inline const Quaternion operator*(const Quaternion& q) const;

    /**
     * Multiplies this quaternion with the given quaternion.
     * 
     * @param q The quaternion to multiply.
     * @return This quaternion, after the multiplication occurs.
     */
    inline Quaternion& operator*=(const Quaternion& q);

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

#include "Quaternion.inl"

#endif
