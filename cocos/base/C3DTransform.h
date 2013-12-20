#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include <list>

#include "C3DMath.h"


namespace cocos3d
{


/**
 * Defines a 3-dimensional transformation.
 *
 * When using the scale, rotate, and translate methods, only the
 * transform's corresponding scale, rotation, or translation
 * component is updated (it is not as if the scale, rotate, or translate
 * is applied to the transform's matrix).
 *
 * Note: To construct a C3DTransform from a transformation matrix stored as a C3DMatrix,
 * first decompose the C3DMatrix into its separate translation, scale, and rotation
 * components using matrix.decompose(C3DVector3, C3DQuaternion, C3DVector3) and then pass
 * those arguments to the appropriate constructor or set methods of C3DTransform.
 */
class  C3DTransform
{
public:   

    /**
     * Listener interface for C3DTransform events.
     */
    class  Listener
    {
    public:

        virtual ~Listener() { }

        /**
         * Handles when an transform has changed.
         *
         * @param transform The C3DTransform object that was changed.
         * @param cookie Cookie value that was specified when the listener was registered.
         */
        virtual void transformChanged(C3DTransform* transform, long cookie) = 0;
    };

    /**
     * Constructs the identity transform.
     */
    C3DTransform();

    /**
     * Constructs a new transform from the specified values.
     *
     * @param scale The scale vector.
     * @param rotation The rotation quaternion.
     * @param translation The translation vector.
     */
    C3DTransform(const C3DVector3& scale, const C3DQuaternion& rotation, const C3DVector3& translation);

    /**
     * Constructs a new transform from the specified values.
     *
     * @param scale The scale vector.
     * @param rotation The rotation matrix.
     * @param translation The translation vector.
     */
    C3DTransform(const C3DVector3& scale, const C3DMatrix& rotation, const C3DVector3& translation);

    /**
     * Constructs a new transform from the given transform.
     *
     * @param copy The transform to copy.
     */
    C3DTransform(const C3DTransform& copy);

    /**
     * Destructor.
     */
    virtual ~C3DTransform();

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
    const C3DMatrix& getMatrix() const;

    /**
     * Returns the scale for this transform.
     */
    const C3DVector3& getScale() const;

    /**
     * Gets the scale component of this transform in the specified vector.
     *
     * @param scale The vector to store the scale in.
     */
    void getScale(C3DVector3* scale) const;

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
    const C3DQuaternion& getRotation() const;

    /**
     * Gets the rotation component of this transform in the specified quaternion.
     *
     * @param rotation The quaternion to store the rotation in.
     */
    void getRotation(C3DQuaternion* rotation) const;

    /**
     * Gets the rotation component of this transform in the specified matrix.
     *
     * @param rotation The matrix to store the rotation in.
     */
    void getRotation(C3DMatrix* rotation) const;

    /**
     * Gets the angle of rotation, and stores the axis of rotation
     * of this transform in the specified C3DVector3.
     *
     * @param axis The vector to store the axis of rotation.
     * 
     * @return The angle of rotation.
     */
    float getRotation(C3DVector3* axis) const;

    /**
     * Returns the translation for this transform.
     */
    const C3DVector3& getPosition() const;

    /**
     * Gets the translation component of this transform in the specified vector.
     *
     * @param translation The vector to store the translation in.
     */
    void getPosition(C3DVector3* translation) const;

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
     * Returns the forward vector for this C3DTransform.
     */
    C3DVector3 getForwardVector() const;

    /**
     * Returns the forward vector for this C3DTransform.
     * 
     * @param dst The vector to store the result in.
     */
    void getForwardVector(C3DVector3* dst) const;
	

    /**
     * Returns the up vector for this C3DTransform.
     */
    C3DVector3 getUpVector() const;

    /**
     * Returns the up vector for this C3DTransform.
     * 
     * @param dst The vector to store the result in.
     */
    void getUpVector(C3DVector3* dst) const;


    /**
     * Returns the right vector for this transform.
     */
    C3DVector3 getRightVector() const;

    /**
     * Returns the right vector for this C3DTransform.
     *
     * @param dst The vector to store the result in.
     */
    void getRightVector(C3DVector3* dst) const;

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
    void rotate(const C3DQuaternion& rotation);

    /**
     * Rotates this transform's rotation component by the given rotation
     * (defined as an axis angle rotation).
     *
     * @param axis The axis to rotate about.
     * @param angle The axis to rotate about (in radians).
     */
    void rotate(const C3DVector3& axis, float angle);

    /**
     * Rotates this transform's rotation component by the given rotation.
     *
     * @param rotation The rotation to rotate by (as a matrix).
     */
    void rotate(const C3DMatrix& rotation);

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
    virtual void scale(const C3DVector3& scale);

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
    void set(const C3DVector3& scale, const C3DQuaternion& rotation, const C3DVector3& translation);

    /**
     * Sets the transform to the specified values.
     *
     * @param scale The scale vector.
     * @param rotation The rotation matrix.
     * @param translation The translation vector.
     */
    void set(const C3DVector3& scale, const C3DMatrix& rotation, const C3DVector3& translation);

    /**
     * Sets the transform to the specified values.
     *
     * @param scale The scale vector.
     * @param axis The axis of rotation.
     * @param angle The angle of rotation (in radians).
     * @param translation The translation vector.
     */
    void set(const C3DVector3& scale, const C3DVector3& axis, float angle, const C3DVector3& translation);

    /**
     * Sets this transform to the specified transform.
     *
     * @param transform The transform to set this transform to.
     */
    void set(const C3DTransform& transform);

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
    void setScale(const C3DVector3& scale);

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
    void setRotation(const C3DQuaternion& rotation);

    /**
     * Sets the rotation component for this transform to the
     * specified values.
     *
     * @param rotation The rotation as a matrix.
     */
    void setRotation(const C3DMatrix& rotation);

    /**
     * Sets the rotation component for this transform to the rotation from the specified axis and angle.
     *
     * @param axis The axis of rotation.
     * @param angle The angle of rotation (in radians).
     */
    void setRotation(const C3DVector3& axis, float angle);

	void setRotationX(float angle);
	void setRotationY(float angle);
	void setRotationZ(float angle);

    /**
     * Sets the translation component for this transform to the
     * specified translation vector.
     *
     * @param translation The translation vector.
     */
    void setPosition(const C3DVector3& translation);

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
    void translate(const C3DVector3& translation);

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
    void transformPoint(C3DVector3* point);

    /**
     * Transforms the specified point and stores the
     * result in the specified destination point.
     *
     * @param point The point to transform.
     * @param dst The point to store the result in.
     */
    void transformPoint(const C3DVector3& point, C3DVector3* dst);

    /**
     * Transforms the specified vector and stores the
     * result in the original vector.
     *
     * @param vector The vector to transform.
     */
    void transformVector(C3DVector3* vector);

    /**
     * Transforms the specified vector and stores the result
     * in the original vector.
     *
     * @param transformVector The vector to transform.
     * @param dst The vector to store the result in.
     */
    void transformVector(const C3DVector3& transformVector, C3DVector3* dst);

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
    void transformVector(float x, float y, float z, float w, C3DVector3* dst);

	/**
	 * 
	 *
	 */
	void lookAt(const C3DVector3& position, const C3DVector3& up, const C3DVector3& target);
    /**
     * Adds a transform listener.
     *
     * @param listener The listener to add.
     * @param cookie An optional long value that is passed to the specified listener when it is called.
     */
    void addListener(C3DTransform::Listener* listener, long cookie = 0);

    /**
     * Removes a transform listener.
     */
    void removeListener(C3DTransform::Listener* listener);

	//void setRotation(const C3DVector3& dir, const C3DVector3& up);

    /**
     * Set position and rotation as rotating along a specific line
     * @param point a point at the line
     * @param axis direction of the line
     * @param angle angle to rotate
     */
	void setRotationAlong(const C3DVector3& point, const C3DVector3& axis, float angle);

	/**
     * Rotate along a specific line
     * @param point a point at the line
     * @param axis direction of the line
     * @param angle angle to rotate
     */
	void rotateAlong(const C3DVector3& point, const C3DVector3& axis, float angle);

protected:

    /**
     * C3DTransform Listener.
     */
    struct TransformListener
    {
        /**
         * Listener for C3DTransform events.
         */
        Listener* listener;

        /**
         * An optional long value that is specified to the Listener's callback.
         */
        long cookie;
    };

    /**
     * Defines the matrix dirty bits for marking the translation, scale and rotation
     * components of the C3DTransform.
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
    virtual void transformChanged();

	virtual void copyFrom(const C3DTransform* other);

    /**
     * The scale component of the C3DTransform.
     */
    C3DVector3 _scale;

    /** 
     * The rotation component of the C3DTransform.
     */
    C3DQuaternion _rotation;
    
    /** 
     * The translation component of the C3DTransform.
     */
    C3DVector3 _position;
    
    /** 
     * The C3DMatrix representation of the C3DTransform.
     */
    mutable C3DMatrix _matrix;
    
    /** 
     * C3DMatrix dirty bits flag.
     */
    mutable char _matrixDirtyBits;
    
    /** 
     * List of TransformListener's on the C3DTransform.
     */
    std::list<TransformListener>* _listeners;

private:


};

}

#endif
