#include "Transform.h"

namespace cocos2d
{

Transform::Transform()
    : _matrixDirtyBits(0)
{
    _scale.set(Vector3::one());
}

Transform::Transform(const Vector3& scale, const Quaternion& rotation, const Vector3& translation)
    : _matrixDirtyBits(0)
{
   
    set(scale, rotation, translation);
}

Transform::Transform(const Vector3& scale, const Matrix& rotation, const Vector3& translation)
    : _matrixDirtyBits(0)
{   
    set(scale, rotation, translation);
}

Transform::Transform(const Transform& copy)
    : _matrixDirtyBits(0)
{
   
    set(copy);
}

Transform::~Transform()
{
    
}

const Matrix& Transform::getMatrix() const
{
    if (_matrixDirtyBits)
    {
        bool hasTranslation = !_position.isZero();
        bool hasScale = !_scale.isOne();
        bool hasRotation = !_rotation.isIdentity();

        // Compose the matrix in TRS order since we use column-major matrices with column vectors and
        // multiply M*v (as opposed to XNA and DirectX that use row-major matrices with row vectors and multiply v*M).
        if (hasTranslation || (_matrixDirtyBits & DIRTY_TRANSLATION) == DIRTY_TRANSLATION)
        {
            Matrix::createTranslation(_position, &_matrix);
            if (hasRotation || (_matrixDirtyBits & DIRTY_ROTATION) == DIRTY_ROTATION)
            {
                _matrix.rotate(_rotation);
            }
            if (hasScale || (_matrixDirtyBits & DIRTY_SCALE) == DIRTY_SCALE)
            {
                _matrix.scale(_scale);
            }
        }
        else if (hasRotation || (_matrixDirtyBits & DIRTY_ROTATION) == DIRTY_ROTATION)
        {
            Matrix::createRotation(_rotation, &_matrix);
            if (hasScale || (_matrixDirtyBits & DIRTY_SCALE) == DIRTY_SCALE)
            {
                _matrix.scale(_scale);
            }
        }
        else if (hasScale || (_matrixDirtyBits & DIRTY_SCALE) == DIRTY_SCALE)
        {
            Matrix::createScale(_scale, &_matrix);
        }

        _matrixDirtyBits = 0;
    }

    return _matrix;
}

const Vector3& Transform::getScale() const
{
    return _scale;
}


float Transform::getScaleX() const
{
    return _scale.x;
}

float Transform::getScaleY() const
{
    return _scale.y;
}

float Transform::getScaleZ() const
{
    return _scale.z;
}

const Quaternion& Transform::getRotation() const
{
    return _rotation;
}


void Transform::getRotation(Matrix* rotation) const
{
    Matrix::createRotation(_rotation, rotation);
}

float Transform::getRotation(Vector3* axis) const
{
    return _rotation.toAxisAngle(axis);
}

const Vector3& Transform::getPosition() const
{
    return _position;
}


float Transform::getPositionX() const
{
    return _position.x;
}

float Transform::getPositionY() const
{
    return _position.y;
}

float Transform::getPositionZ() const
{
    return _position.z;
}

Vector3 Transform::getForwardVector() const
{
    Vector3 v;
    getForwardVector(&v);
    return v;
}

void Transform::getForwardVector(Vector3* dst) const
{
    getMatrix().getForwardVector(dst);
}


Vector3 Transform::getUpVector() const
{
    Vector3 v;
    getUpVector(&v);
    return v;
}

void Transform::getUpVector(Vector3* dst) const
{
    getMatrix().getUpVector(dst);
}


Vector3 Transform::getRightVector() const
{
    Vector3 v;
    getRightVector(&v);
    return v;
}

void Transform::getRightVector(Vector3* dst) const
{
    getMatrix().getRightVector(dst);
}

void Transform::rotate(float qx, float qy, float qz, float qw)
{
    Quaternion q(qx, qy, qz, qw);
    _rotation.multiply(q);
    dirty(DIRTY_ROTATION);
}

void Transform::rotate(const Quaternion& rotation)
{
    _rotation.multiply(rotation);
    dirty(DIRTY_ROTATION);
}

void Transform::rotate(const Vector3& axis, float angle)
{
    Quaternion rotationQuat;
    Quaternion::createFromAxisAngle(axis, angle, &rotationQuat);
    _rotation.multiply(rotationQuat);
    _rotation.normalize();
    dirty(DIRTY_ROTATION);
}

void Transform::rotate(const Matrix& rotation)
{
    Quaternion rotationQuat;
    Quaternion::createFromRotationMatrix(rotation, &rotationQuat);
    _rotation.multiply(rotationQuat);
    dirty(DIRTY_ROTATION);
}

void Transform::rotateX(float angle)
{
    Quaternion rotationQuat;
    Quaternion::createFromAxisAngle(Vector3::unitX(), angle, &rotationQuat);
    _rotation.multiply(rotationQuat);
    dirty(DIRTY_ROTATION);
}

void Transform::rotateY(float angle)
{
    Quaternion rotationQuat;
    Quaternion::createFromAxisAngle(Vector3::unitY(), angle, &rotationQuat);
    _rotation.multiply(rotationQuat);
    dirty(DIRTY_ROTATION);
}

void Transform::rotateZ(float angle)
{
    Quaternion rotationQuat;
    Quaternion::createFromAxisAngle(Vector3::unitZ(), angle, &rotationQuat);
    _rotation.multiply(rotationQuat);
    dirty(DIRTY_ROTATION);
}

void Transform::setRotationX(float angle)
{    
    Quaternion rotationQuat;
    Quaternion::createFromAxisAngle(Vector3::unitX(), angle, &rotationQuat);
    _rotation = rotationQuat;
    dirty(DIRTY_ROTATION);

}
void Transform::setRotationY(float angle)
{
    Quaternion rotationQuat;
    Quaternion::createFromAxisAngle(Vector3::unitY(), angle, &rotationQuat);
    _rotation = rotationQuat;
    dirty(DIRTY_ROTATION);
}


void Transform::setRotationZ(float angle)
{
    Quaternion rotationQuat;
    Quaternion::createFromAxisAngle(Vector3::unitZ(), angle, &rotationQuat);
    _rotation = rotationQuat;
    dirty(DIRTY_ROTATION);
}

void Transform::scale(float scale)
{
    _scale.scale(scale);
    dirty(DIRTY_SCALE);
}

void Transform::scale(float sx, float sy, float sz)
{
    _scale.x *= sx;
    _scale.y *= sy;
    _scale.z *= sz;
    dirty(DIRTY_SCALE);
}

void Transform::scale(const Vector3& scale)
{
    _scale.x *= scale.x;
    _scale.y *= scale.y;
    _scale.z *= scale.z;
    dirty(DIRTY_SCALE);
}

void Transform::scaleX(float sx)
{
    _scale.x *= sx;
    dirty(DIRTY_SCALE);
}

void Transform::scaleY(float sy)
{
    _scale.y *= sy;
    dirty(DIRTY_SCALE);
}

void Transform::scaleZ(float sz)
{
    _scale.z *= sz;
    dirty(DIRTY_SCALE);
}

void Transform::set(const Vector3& scale, const Quaternion& rotation, const Vector3& translation)
{
    _scale.set(scale);
    _rotation.set(rotation);
    _position.set(translation);
    dirty(DIRTY_TRANSLATION | DIRTY_ROTATION | DIRTY_SCALE);
}

void Transform::set(const Vector3& scale, const Matrix& rotation, const Vector3& translation)
{
    _scale.set(scale);
    Quaternion rotationQuat;
    Quaternion::createFromRotationMatrix(rotation, &rotationQuat);
    _rotation.set(rotationQuat);
    _position.set(translation);
    dirty(DIRTY_TRANSLATION | DIRTY_ROTATION | DIRTY_SCALE);
}

void Transform::set(const Vector3& scale, const Vector3& axis, float angle, const Vector3& translation)
{
    _scale.set(scale);
    _rotation.set(axis, angle);
    _position.set(translation);
    dirty(DIRTY_TRANSLATION | DIRTY_ROTATION | DIRTY_SCALE);
}

void Transform::set(const Transform& transform)
{
    _scale.set(transform._scale);
    _rotation.set(transform._rotation);
    _position.set(transform._position);
    dirty(DIRTY_TRANSLATION | DIRTY_ROTATION | DIRTY_SCALE);
}

void Transform::setIdentity()
{
    _scale.set(1.0f, 1.0f, 1.0f);
    _rotation.setIdentity();
    _position.set(0.0f, 0.0f, 0.0f);
    dirty(DIRTY_TRANSLATION | DIRTY_ROTATION | DIRTY_SCALE);
}

void Transform::setScale(float scale)
{
    _scale.set(scale, scale, scale);
    dirty(DIRTY_SCALE);
}

void Transform::setScale(float sx, float sy, float sz)
{
    _scale.set(sx, sy, sz);
    dirty(DIRTY_SCALE);
}

void Transform::setScale(const Vector3& scale)
{
    _scale.set(scale);
    dirty(DIRTY_SCALE);
}

void Transform::setScaleX(float sx)
{
    _scale.x = sx;
    dirty(DIRTY_SCALE);
}

void Transform::setScaleY(float sy)
{
    _scale.y = sy;
    dirty(DIRTY_SCALE);
}

void Transform::setScaleZ(float sz)
{
    _scale.z = sz;
    dirty(DIRTY_SCALE);
}

void Transform::setRotation(const Quaternion& rotation)
{
    _rotation.set(rotation);
    dirty(DIRTY_ROTATION);
}

void Transform::setRotation(float qx, float qy, float qz, float qw)
{
    _rotation.set(qx, qy, qz, qw);
    dirty(DIRTY_ROTATION);
}

void Transform::setRotation(const Matrix& rotation)
{
    Quaternion rotationQuat;
    Quaternion::createFromRotationMatrix(rotation, &rotationQuat);
    _rotation.set(rotationQuat);
    dirty(DIRTY_ROTATION);
}

void Transform::setRotation(const Vector3& axis, float angle)
{
    _rotation.set(axis, angle);
    dirty(DIRTY_ROTATION);
}

void Transform::setPosition(const Vector3& translation)
{
    _position.set(translation);
    dirty(DIRTY_TRANSLATION);
}

void Transform::setPosition(float tx, float ty, float tz)
{
    _position.set(tx, ty, tz);
    dirty(DIRTY_TRANSLATION);
}

void Transform::setPositionX(float tx)
{
    _position.x = tx;
    dirty(DIRTY_TRANSLATION);
}

void Transform::setPositionY(float ty)
{
    _position.y = ty;
    dirty(DIRTY_TRANSLATION);
}

void Transform::setPositionZ(float tz)
{
    _position.z = tz;
    dirty(DIRTY_TRANSLATION);
}

void Transform::translate(float tx, float ty, float tz)
{
    _position.x += tx;
    _position.y += ty;
    _position.z += tz;
    dirty(DIRTY_TRANSLATION);
}

void Transform::translate(const Vector3& translation)
{
    _position.x += translation.x;
    _position.y += translation.y;
    _position.z += translation.z;
    dirty(DIRTY_TRANSLATION);
}

void Transform::translateX(float tx)
{
    _position.x += tx;
    dirty(DIRTY_TRANSLATION);
}

void Transform::translateY(float ty)
{
    _position.y += ty;
    dirty(DIRTY_TRANSLATION);
}

void Transform::translateZ(float tz)
{
    _position.z += tz;
    dirty(DIRTY_TRANSLATION);
}

void Transform::translateRight(float amount)
{
    // Force the current transform matrix to be updated.
    getMatrix();

    Vector3 right;
    _matrix.getRightVector(&right);
    right.normalize();
    right.scale(amount);

    translate(right);
}

void Transform::translateUp(float amount)
{
    // Force the current transform matrix to be updated.
    getMatrix();

    Vector3 up;
    _matrix.getUpVector(&up);
    up.normalize();
    up.scale(amount);

    translate(up);
}

void Transform::translateForward(float amount)
{
    // Force the current transform matrix to be updated.
    getMatrix();

    Vector3 forward;
    _matrix.getForwardVector(&forward);
    forward.normalize();
    forward.scale(amount);

    translate(forward);
}

void Transform::transformPoint(Vector3* point)
{
    getMatrix();
    _matrix.transformPoint(point);
}

void Transform::transformPoint(const Vector3& point, Vector3* dst)
{
    getMatrix();
    _matrix.transformPoint(point, dst);
}

void Transform::transformVector(Vector3* normal)
{
    getMatrix();
    _matrix.transformVector(normal);
}

void Transform::transformVector(const Vector3& normal, Vector3* dst)
{
    getMatrix();
    _matrix.transformVector(normal, dst);
}

void Transform::transformVector(float x, float y, float z, float w, Vector3* dst)
{
    getMatrix();
    _matrix.transformVector(x, y, z, w, dst);
}


void Transform::dirty(char matrixDirtyBits)
{
    _matrixDirtyBits |= matrixDirtyBits;
    transformChanged();
}


void Transform::lookAt(const Vector3& position, const Vector3& up, const Vector3& target)
{

    Matrix matRotate;

    Vector3 upv = up;
    upv.normalize();

    Vector3 zaxis;
    Vector3::subtract(position, target, &zaxis);
    zaxis.normalize();

    Vector3 xaxis;
    Vector3::cross(upv, zaxis, &xaxis);
    xaxis.normalize();

    Vector3 yaxis;
    Vector3::cross(zaxis, xaxis, &yaxis);
    yaxis.normalize();

    matRotate.m[0] = xaxis.x;
    matRotate.m[1] = xaxis.y;
    matRotate.m[2] = xaxis.z;
    matRotate.m[3] = 0;

    matRotate.m[4] = yaxis.x;
    matRotate.m[5] = yaxis.y;
    matRotate.m[6] = yaxis.z;
    matRotate.m[7] = 0;

    matRotate.m[8] = zaxis.x;
    matRotate.m[9] = zaxis.y;
    matRotate.m[10] = zaxis.z;
    matRotate.m[11] = 0;

    setRotation(matRotate);
    setPosition(position);
}

void Transform::copyFrom(const Transform* other)
{
    _scale = other->_scale;
    _position = other->_position;
    _rotation = other->_rotation;
    _matrix = other->_matrix;
    _matrixDirtyBits = other->_matrixDirtyBits;

    transformChanged();
}

void Transform::setRotationAlong(const Vector3& point, const Vector3& axis, float angle)
{
    // p' = rot * (p - point) + point = rot * p - rot * point + point
    _rotation.set(axis, angle);
    _position = point - _rotation * point;
    dirty(DIRTY_TRANSLATION | DIRTY_ROTATION);
}

void Transform::rotateAlong(const Vector3& point, const Vector3& axis, float angle)
{
    Quaternion rot(axis, angle);

    // p' = rot0 * p + pos0
    // p'' = rot * (p' - point) + point
    //     = rot * rot0 * p + rot * (pos0 - point) + point  

    _rotation = rot * _rotation;
    _position = rot * (_position - point) + point; 
    dirty(DIRTY_TRANSLATION | DIRTY_ROTATION);
}


}
