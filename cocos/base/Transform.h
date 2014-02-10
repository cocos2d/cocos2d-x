#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include <list>

#include "../math/Vector3.h"
#include "../math/C3DQuaternion.h"
#include "../math/C3DMatrix.h"


namespace cocos2d
{

/**
 * Defines a 3-dimensional transformation.
 *
 * When using the scale, rotate, and translate methods, only the
 * transform's corresponding scale, rotation, or translation
 * component is updated (it is not as if the scale, rotate, or translate
 * is applied to the transform's matrix).
 *
 * Note: To construct a Transform from a transformation matrix stored as a Matrix,
 * first decompose the Matrix into its separate translation, scale, and rotation
 * components using matrix.decompose(Vector3, Quaternion, Vector3) and then pass
 * those arguments to the appropriate constructor or set methods of Transform.
 */
class  Transform
{
public:   
       

    /**
     * Constructs the identity transform.
     */
    Transform();

    /**
     * Constructs a new transform from the specified values.
     *
     * @param scale The scale vector.
     * @param rotation The rotation quaternion.
     * @param translation The translation vector.
     */
    Transform(const Vector3& scale, const Quaternion& rotation, const Vector3& translation);

    /**
     * Constructs a new transform from the specified values.
     *
     * @param scale The scale vector.
     * @param rotation The rotation matrix.
     * @param translation The translation vector.
     */
    Transform(const Vector3& scale, const Matrix& rotation, const Vector3& translation);

    /**
     * Constructs a new transform from the given transform.
     *
     * @param copy The transform to copy.
     */
    Transform(const Transform& copy);

    /**
     * Destructor.
     */
    virtual ~Transform();

    /**
     * Gets the matrix corresponding to this transform.
     *
     * The matrix returned from this method is mathematically equivalent
     * to this transform only as long as this transform is not changed
     * (i.e. by calling set(), setScale(), translate(), rotateX(), etc.).
     * Once the transform has been changed, the user must call getMatrix()
     * again to get the updated matrix. Also note that changing the matrix
     * returned from this method does not change this transform.
     *
     * @return The matrix of this transform.
     */
    const Matrix& getMatrix() const;

    /**
     * Returns the scale for this transform.
     */
    const Vector3& getScale() const;
    

    /**
     * Gets the scale factor along the x-axis of this transform.
     *
     * @return The scale factor along the x-axis.
     */
    float getScaleX() const;

    /**
     * Gets the scale factor along the y-axis of this transform.
     *
     * @return The scale factor along the y-axis.
     */
    float getScaleY() const;

    /**
     * Gets the scale factor along the z-axis of this transform.
     *
     * @return The scale factor along the z-axis.
     */
    float getScaleZ() const;

    /**
     * Returns the rotation for this transform.
     */
    const Quaternion& getRotation() const;

    
    /**
     * Gets the rotation component of this transform in the specified matrix.
     *
     * @param rotation The matrix to store the rotation in.
     */
    void getRotation(Matrix* rotation) const;

    /**
     * Gets the angle of rotation, and stores the axis of rotation
     * of this transform in the specified Vector3.
     *
     * @param axis The vector to store the axis of rotation.
     * 
     * @return The angle of rotation.
     */
    float getRotation(Vector3* axis) const;

    /**
     * Returns the translation for this transform.
     */
    const Vector3& getPosition() const;
    

    /**
     * Gets the translation factor along the x-axis of this transform.
     *
     * @return The translation factor along the x-axis.
     */
    float getPositionX() const;

    /**
     * Gets the translation factor along the y-axis of this transform.
     *
     * @return The translation factor along the y-axis.
     */
    float getPositionY() const;

    /**
     * Gets the translation factor along the z-axis of this transform.
     *
     * @return The translation factor along the z-axis.
     */
    float getPositionZ() const;
    
    /**
     * Returns the forward vector for this Transform.
     */
    Vector3 getForwardVector() const;

    /**
     * Returns the forward vector for this Transform.
     * 
     * @param dst The vector to store the result in.
     */
    void getForwardVector(Vector3* dst) const;
    

    /**
     * Returns the up vector for this Transform.
     */
    Vector3 getUpVector() const;

    /**
     * Returns the up vector for this Transform.
     * 
     * @param dst The vector to store the result in.
     */
    void getUpVector(Vector3* dst) const;


    /**
     * Returns the right vector for this transform.
     */
    Vector3 getRightVector() const;

    /**
     * Returns the right vector for this Transform.
     *
     * @param dst The vector to store the result in.
     */
    void getRightVector(Vector3* dst) const;
        

    /**
     * Rotates this transform's rotation component by the given rotation.
     *
     * @param qx The quaternion x value.
     * @param qy The quaternion y value.
     * @param qz The quaternion z value.
     * @param qw The quaternion w value.
     */
    void rotate(float qx, float qy, float qz, float qw);

    /**
     * Rotates this transform's rotation component by the given rotation.
     *
     * @param rotation The rotation to rotate by (as a quaternion).
     */
    void rotate(const Quaternion& rotation);

    /**
     * Rotates this transform's rotation component by the given rotation
     * (defined as an axis angle rotation).
     *
     * @param axis The axis to rotate about.
     * @param angle The axis to rotate about (in radians).
     */
    void rotate(const Vector3& axis, float angle);

    /**
     * Rotates this transform's rotation component by the given rotation.
     *
     * @param rotation The rotation to rotate by (as a matrix).
     */
    void rotate(const Matrix& rotation);

    /**
     * Rotates this transform's rotation component by the given angle
     * about the x-axis.
     *
     * @param angle The angle to rotate by about the x-axis (in radians).
     */
    void rotateX(float angle);

    /**
     * Rotates this transform's rotation component by the given angle
     * about the y-axis.
     *
     * @param angle The angle to rotate by about the y-axis (in radians).
     */
    void rotateY(float angle);

    /**
     * Rotates this transform's rotation component by the given angle
     * about the z-axis.
     *
     * @param angle The angle to rotate by about the z-axis (in radians).
     */
    void rotateZ(float angle);

    /**
     * Scales this transform's scale component by the given factor along all axes.
     *
     * @param scale The factor to scale by along all axis.
     */
    void scale(float scale);

    /**
     * Scales this transform's scale component by the given factors along each axis.
     *
     * @param sx The factor to scale by in the x direction.
     * @param sy The factor to scale by in the y direction.
     * @param sz The factor to scale by in the z direction.
     */
    void scale(float sx, float sy, float sz);

    /**
     * Scales this transform's scale component by the given scale vector.
     *
     * @param scale The vector to scale by.
     */
    virtual void scale(const Vector3& scale);

    /**
     * Scales this transform's scale component by the given scale
     * factor along the x axis.
     *
     * @param sx The scale factor along the x axis.
     */
    void scaleX(float sx);

    /**
     * Scales this transform's scale component by the given scale
     * factor along the y axis.
     *
     * @param sy The scale factor along the y axis.
     */
    void scaleY(float sy);

    /**
     * Scales this transform's scale component by the given scale
     * factor along the z axis.
     *
     * @param sz The scale factor along the z axis.
     */
    void scaleZ(float sz);

    /**
     * Sets the transform to the specified values.
     *
     * @param scale The scale vector.
     * @param rotation The rotation quaternion.
     * @param translation The translation vector.
     */
    void set(const Vector3& scale, const Quaternion& rotation, const Vector3& translation);

    /**
     * Sets the transform to the specified values.
     *
     * @param scale The scale vector.
     * @param rotation The rotation matrix.
     * @param translation The translation vector.
     */
    void set(const Vector3& scale, const Matrix& rotation, const Vector3& translation);

    /**
     * Sets the transform to the specified values.
     *
     * @param scale The scale vector.
     * @param axis The axis of rotation.
     * @param angle The angle of rotation (in radians).
     * @param translation The translation vector.
     */
    void set(const Vector3& scale, const Vector3& axis, float angle, const Vector3& translation);

    /**
     * Sets this transform to the specified transform.
     *
     * @param transform The transform to set this transform to.
     */
    void set(const Transform& transform);

    /**
     * Sets this transform to the identity transform.
     */
    void setIdentity();

    /**
     * Sets the scale factor along all axes for this transform
     * to the specified value.
     *
     * @param scale The scale factor along all axes.
     */
    void setScale(float scale);

    /**
     * Sets the scale component of this transform to the
     * specified values.
     *
     * @param sx The scale factor along the x axis.
     * @param sy The scale factor along the y axis.
     * @param sz The scale factor along the z axis.
     */
    void setScale(float sx, float sy, float sz);

    /**
     * Sets the scale component of this transform to the
     * specified scale vector.
     *
     * @param scale The scale vector.
     */
    void setScale(const Vector3& scale);

    /**
     * Sets the scale factor along the x-axis for this transform
     * to the specified value.
     *
     * @param sx The scale factor along the x-axis.
     */
    void setScaleX(float sx);

    /**
     * Sets the scale factor along the y-axis for this transform
     * to the specified value.
     *
     * @param sy The scale factor along the y-axis.
     */
    void setScaleY(float sy);

    /**
     * Sets the scale factor along the z-axis for this transform
     * to the specified value.
     *
     * @param sz The scale factor along the z-axis.
     */
    void setScaleZ(float sz);

    /**
     * Sets the rotation component for this transform to the
     * specified values.
     *
     * @param qx The quaternion x value.
     * @param qy The quaternion y value.
     * @param qz The quaternion z value.
     * @param qw The quaternion w value.
     */
    void setRotation(float qx, float qy, float qz, float qw);

    /**
     * Sets the rotation component for this transform to the
     * specified values.
     *
     * @param rotation The rotation as a quaternion.
     */
    void setRotation(const Quaternion& rotation);

    /**
     * Sets the rotation component for this transform to the
     * specified values.
     *
     * @param rotation The rotation as a matrix.
     */
    void setRotation(const Matrix& rotation);

    /**
     * Sets the rotation component for this transform to the rotation from the specified axis and angle.
     *
     * @param axis The axis of rotation.
     * @param angle The angle of rotation (in radians).
     */
    void setRotation(const Vector3& axis, float angle);

    void setRotationX(float angle);
    void setRotationY(float angle);
    void setRotationZ(float angle);

    /**
     * Sets the translation component for this transform to the
     * specified translation vector.
     *
     * @param translation The translation vector.
     */
    void setPosition(const Vector3& translation);

    /**
     * Sets the translation component for this transform
     * to the specified values.
     *
     * @param tx The translation amount in the x direction.
     * @param ty The translation amount in the y direction.
     * @param tz The translation amount in the z direction.
     */
    void setPosition(float tx, float ty, float tz);

    /**
     * Sets the translation factor along the x-axis for this
     * transform to the specified value.
     *
     * @param tx The translation factor along the x-axis.
     */
    void setPositionX(float tx);

    /**
     * Sets the translation factor along the y-axis for this
     * transform to the specified value.
     *
     * @param ty The translation factor along the y-axis.
     */
    void setPositionY(float ty);

    /**
     * Sets the translation factor along the z-axis for this
     * transform to the specified value.
     *
     * @param tz The translation factor along the z-axis.
     */
    void setPositionZ(float tz);

    /**
     * Translates this transform's translation component by the
     * given values along each axis.
     *
     * @param tx The amount to translate along the x axis.
     * @param ty The amount to translate along the y axis.
     * @param tz The amount to translate along the z axis.
     */
    void translate(float tx, float ty, float tz);

    /**
     * Translates this transform's translation component by the
     * given translation vector.
     *
     * @param translation The amount to translate.
     */
    void translate(const Vector3& translation);

    /**
     * Translates this transform's translation component by the
     * given value along the x axis.
     *
     * @param tx The amount to translate along the x axis.
     */
    void translateX(float tx);

    /**
     * Translates this transform's translation component by the
     * given value along the y axis.
     *
     * @param ty The amount to translate along the y axis.
     */
    void translateY(float ty);

    /**
     * Translates this transform's translation component by the
     * given value along the z axis.
     *
     * @param tz The amount to translate along the z axis.
     */
    void translateZ(float tz);

    /**
     * Translates the camera right by the specified amount in the x-axis.
     *
     * @param amount The amount to translate.
     */
    void translateRight(float amount);

    /**
     * Translates the camera up by the specified amount in the y-axis.
     *
     * @param amount The amount to translate.
     */
    void translateUp(float amount);

    /**
     * Translates the camera foward by the specified amount in the z-axis.
     *
     * @param amount The amount to translate.
     */
    void translateForward(float amount);

    /**
     * Transforms the specified point and stores the
     * result in the original point.
     *
     * @param point The point to transform.
     */
    void transformPoint(Vector3* point);

    /**
     * Transforms the specified point and stores the
     * result in the specified destination point.
     *
     * @param point The point to transform.
     * @param dst The point to store the result in.
     */
    void transformPoint(const Vector3& point, Vector3* dst);

    /**
     * Transforms the specified vector and stores the
     * result in the original vector.
     *
     * @param vector The vector to transform.
     */
    void transformVector(Vector3* vector);

    /**
     * Transforms the specified vector and stores the result
     * in the original vector.
     *
     * @param transformVector The vector to transform.
     * @param dst The vector to store the result in.
     */
    void transformVector(const Vector3& transformVector, Vector3* dst);

    /**
     * Transforms the specified vector and stores the result
     * in the specified destination vector.
     *
     * @param x The x factor to transform.
     * @param y The y factor to transform.
     * @param z The z factor to transform.
     * @param w The w factor to transform.
     * @param dst The vector to store the result in.
     */
    void transformVector(float x, float y, float z, float w, Vector3* dst);

    /**
     * 
     *
     */
    void lookAt(const Vector3& position, const Vector3& up, const Vector3& target);
    
    /**
     * Set position and rotation as rotating along a specific line
     * @param point a point at the line
     * @param axis direction of the line
     * @param angle angle to rotate
     */
    void setRotationAlong(const Vector3& point, const Vector3& axis, float angle);

    /**
     * Rotate along a specific line
     * @param point a point at the line
     * @param axis direction of the line
     * @param angle angle to rotate
     */
    void rotateAlong(const Vector3& point, const Vector3& axis, float angle);

protected:

   

    /**
     * Defines the matrix dirty bits for marking the translation, scale and rotation
     * components of the Transform.
     */
    enum MatrixDirtyBits
    {
        DIRTY_TRANSLATION = 0x01,
        DIRTY_SCALE = 0x02,
        DIRTY_ROTATION = 0x04,
    };

    /**
     * Marks this transform as dirty and fires transformChanged().
     */
    void dirty(char matrixDirtyBits);

    /**
     * Called when the transform changes.
     */
    virtual void transformChanged(){};

    virtual void copyFrom(const Transform* other);

    /**
     * The scale component of the Transform.
     */
    Vector3 _scale;

    /** 
     * The rotation component of the Transform.
     */
    Quaternion _rotation;
    
    /** 
     * The translation component of the Transform.
     */
    Vector3 _position;
    
    /** 
     * The Matrix representation of the Transform.
     */
    mutable Matrix _matrix;
    
    /** 
     * Matrix dirty bits flag.
     */
    mutable char _matrixDirtyBits;
    

private:


};

}

#endif
