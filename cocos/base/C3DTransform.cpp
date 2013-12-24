#include "C3DTransform.h"

namespace cocos3d
{

C3DTransform::C3DTransform()
    : _matrixDirtyBits(0)
{
    _scale.set(C3DVector3::one());
}

C3DTransform::C3DTransform(const C3DVector3& scale, const C3DQuaternion& rotation, const C3DVector3& translation)
    : _matrixDirtyBits(0)
{
   
    set(scale, rotation, translation);
}

C3DTransform::C3DTransform(const C3DVector3& scale, const C3DMatrix& rotation, const C3DVector3& translation)
    : _matrixDirtyBits(0)
{   
    set(scale, rotation, translation);
}

C3DTransform::C3DTransform(const C3DTransform& copy)
    : _matrixDirtyBits(0)
{
   
    set(copy);
}

C3DTransform::~C3DTransform()
{
    
}

const C3DMatrix& C3DTransform::getMatrix() const
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
            C3DMatrix::createTranslation(_position, &_matrix);
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
            C3DMatrix::createRotation(_rotation, &_matrix);
            if (hasScale || (_matrixDirtyBits & DIRTY_SCALE) == DIRTY_SCALE)
            {
                _matrix.scale(_scale);
            }
        }
        else if (hasScale || (_matrixDirtyBits & DIRTY_SCALE) == DIRTY_SCALE)
        {
            C3DMatrix::createScale(_scale, &_matrix);
        }

        _matrixDirtyBits = 0;
    }

    return _matrix;
}

const C3DVector3& C3DTransform::getScale() const
{
    return _scale;
}

void C3DTransform::getScale(C3DVector3* scale) const
{
    scale->set(_scale);
}

float C3DTransform::getScaleX() const
{
    return _scale.x;
}

float C3DTransform::getScaleY() const
{
    return _scale.y;
}

float C3DTransform::getScaleZ() const
{
    return _scale.z;
}

const C3DQuaternion& C3DTransform::getRotation() const
{
    return _rotation;
}

void C3DTransform::getRotation(C3DQuaternion* rotation) const
{
	rotation->set(_rotation);
}

void C3DTransform::getRotation(C3DMatrix* rotation) const
{
    C3DMatrix::createRotation(_rotation, rotation);
}

float C3DTransform::getRotation(C3DVector3* axis) const
{
    return _rotation.toAxisAngle(axis);
}

const C3DVector3& C3DTransform::getPosition() const
{
    return _position;
}

void C3DTransform::getPosition(C3DVector3* translation) const
{
    translation->set(_position);
}

float C3DTransform::getPositionX() const
{
    return _position.x;
}

float C3DTransform::getPositionY() const
{
    return _position.y;
}

float C3DTransform::getPositionZ() const
{
    return _position.z;
}

C3DVector3 C3DTransform::getForwardVector() const
{
    C3DVector3 v;
    getForwardVector(&v);
    return v;
}

void C3DTransform::getForwardVector(C3DVector3* dst) const
{
    getMatrix().getForwardVector(dst);
}


C3DVector3 C3DTransform::getUpVector() const
{
    C3DVector3 v;
    getUpVector(&v);
    return v;
}

void C3DTransform::getUpVector(C3DVector3* dst) const
{
    getMatrix().getUpVector(dst);
}


C3DVector3 C3DTransform::getRightVector() const
{
    C3DVector3 v;
    getRightVector(&v);
    return v;
}

void C3DTransform::getRightVector(C3DVector3* dst) const
{
    getMatrix().getRightVector(dst);
}

void C3DTransform::rotate(float qx, float qy, float qz, float qw)
{
    C3DQuaternion q(qx, qy, qz, qw);
    _rotation.multiply(q);
    dirty(DIRTY_ROTATION);
}

void C3DTransform::rotate(const C3DQuaternion& rotation)
{
    _rotation.multiply(rotation);
    dirty(DIRTY_ROTATION);
}

void C3DTransform::rotate(const C3DVector3& axis, float angle)
{
    C3DQuaternion rotationQuat;
    C3DQuaternion::createFromAxisAngle(axis, angle, &rotationQuat);
    _rotation.multiply(rotationQuat);
    _rotation.normalize();
    dirty(DIRTY_ROTATION);
}

void C3DTransform::rotate(const C3DMatrix& rotation)
{
    C3DQuaternion rotationQuat;
    C3DQuaternion::createFromRotationMatrix(rotation, &rotationQuat);
    _rotation.multiply(rotationQuat);
    dirty(DIRTY_ROTATION);
}

void C3DTransform::rotateX(float angle)
{
    C3DQuaternion rotationQuat;
    C3DQuaternion::createFromAxisAngle(C3DVector3::unitX(), angle, &rotationQuat);
    _rotation.multiply(rotationQuat);
    dirty(DIRTY_ROTATION);
}

void C3DTransform::rotateY(float angle)
{
    C3DQuaternion rotationQuat;
    C3DQuaternion::createFromAxisAngle(C3DVector3::unitY(), angle, &rotationQuat);
    _rotation.multiply(rotationQuat);
    dirty(DIRTY_ROTATION);
}

void C3DTransform::rotateZ(float angle)
{
    C3DQuaternion rotationQuat;
    C3DQuaternion::createFromAxisAngle(C3DVector3::unitZ(), angle, &rotationQuat);
    _rotation.multiply(rotationQuat);
    dirty(DIRTY_ROTATION);
}

void C3DTransform::setRotationX(float angle)
{	
	C3DQuaternion rotationQuat;
    C3DQuaternion::createFromAxisAngle(C3DVector3::unitX(), angle, &rotationQuat);
	_rotation = rotationQuat;
	dirty(DIRTY_ROTATION);

}
void C3DTransform::setRotationY(float angle)
{
	C3DQuaternion rotationQuat;
    C3DQuaternion::createFromAxisAngle(C3DVector3::unitY(), angle, &rotationQuat);
	_rotation = rotationQuat;
	dirty(DIRTY_ROTATION);
}


void C3DTransform::setRotationZ(float angle)
{
	C3DQuaternion rotationQuat;
    C3DQuaternion::createFromAxisAngle(C3DVector3::unitZ(), angle, &rotationQuat);
	_rotation = rotationQuat;
	dirty(DIRTY_ROTATION);
}

void C3DTransform::scale(float scale)
{
    _scale.scale(scale);
    dirty(DIRTY_SCALE);
}

void C3DTransform::scale(float sx, float sy, float sz)
{
    _scale.x *= sx;
    _scale.y *= sy;
    _scale.z *= sz;
    dirty(DIRTY_SCALE);
}

void C3DTransform::scale(const C3DVector3& scale)
{
    _scale.x *= scale.x;
    _scale.y *= scale.y;
    _scale.z *= scale.z;
    dirty(DIRTY_SCALE);
}

void C3DTransform::scaleX(float sx)
{
    _scale.x *= sx;
    dirty(DIRTY_SCALE);
}

void C3DTransform::scaleY(float sy)
{
    _scale.y *= sy;
    dirty(DIRTY_SCALE);
}

void C3DTransform::scaleZ(float sz)
{
    _scale.z *= sz;
    dirty(DIRTY_SCALE);
}

void C3DTransform::set(const C3DVector3& scale, const C3DQuaternion& rotation, const C3DVector3& translation)
{
    _scale.set(scale);
    _rotation.set(rotation);
    _position.set(translation);
    dirty(DIRTY_TRANSLATION | DIRTY_ROTATION | DIRTY_SCALE);
}

void C3DTransform::set(const C3DVector3& scale, const C3DMatrix& rotation, const C3DVector3& translation)
{
    _scale.set(scale);
    C3DQuaternion rotationQuat;
    C3DQuaternion::createFromRotationMatrix(rotation, &rotationQuat);
    _rotation.set(rotationQuat);
    _position.set(translation);
    dirty(DIRTY_TRANSLATION | DIRTY_ROTATION | DIRTY_SCALE);
}

void C3DTransform::set(const C3DVector3& scale, const C3DVector3& axis, float angle, const C3DVector3& translation)
{
    _scale.set(scale);
    _rotation.set(axis, angle);
    _position.set(translation);
    dirty(DIRTY_TRANSLATION | DIRTY_ROTATION | DIRTY_SCALE);
}

void C3DTransform::set(const C3DTransform& transform)
{
    _scale.set(transform._scale);
    _rotation.set(transform._rotation);
    _position.set(transform._position);
    dirty(DIRTY_TRANSLATION | DIRTY_ROTATION | DIRTY_SCALE);
}

void C3DTransform::setIdentity()
{
    _scale.set(1.0f, 1.0f, 1.0f);
    _rotation.setIdentity();
    _position.set(0.0f, 0.0f, 0.0f);
    dirty(DIRTY_TRANSLATION | DIRTY_ROTATION | DIRTY_SCALE);
}

void C3DTransform::setScale(float scale)
{
    _scale.set(scale, scale, scale);
    dirty(DIRTY_SCALE);
}

void C3DTransform::setScale(float sx, float sy, float sz)
{
    _scale.set(sx, sy, sz);
    dirty(DIRTY_SCALE);
}

void C3DTransform::setScale(const C3DVector3& scale)
{
    _scale.set(scale);
    dirty(DIRTY_SCALE);
}

void C3DTransform::setScaleX(float sx)
{
    _scale.x = sx;
    dirty(DIRTY_SCALE);
}

void C3DTransform::setScaleY(float sy)
{
    _scale.y = sy;
    dirty(DIRTY_SCALE);
}

void C3DTransform::setScaleZ(float sz)
{
    _scale.z = sz;
    dirty(DIRTY_SCALE);
}

void C3DTransform::setRotation(const C3DQuaternion& rotation)
{
    _rotation.set(rotation);
    dirty(DIRTY_ROTATION);
}

void C3DTransform::setRotation(float qx, float qy, float qz, float qw)
{
    _rotation.set(qx, qy, qz, qw);
    dirty(DIRTY_ROTATION);
}

void C3DTransform::setRotation(const C3DMatrix& rotation)
{
    C3DQuaternion rotationQuat;
    C3DQuaternion::createFromRotationMatrix(rotation, &rotationQuat);
    _rotation.set(rotationQuat);
    dirty(DIRTY_ROTATION);
}

void C3DTransform::setRotation(const C3DVector3& axis, float angle)
{
    _rotation.set(axis, angle);
    dirty(DIRTY_ROTATION);
}

void C3DTransform::setPosition(const C3DVector3& translation)
{
    _position.set(translation);
    dirty(DIRTY_TRANSLATION);
}

void C3DTransform::setPosition(float tx, float ty, float tz)
{
    _position.set(tx, ty, tz);
    dirty(DIRTY_TRANSLATION);
}

void C3DTransform::setPositionX(float tx)
{
    _position.x = tx;
    dirty(DIRTY_TRANSLATION);
}

void C3DTransform::setPositionY(float ty)
{
    _position.y = ty;
    dirty(DIRTY_TRANSLATION);
}

void C3DTransform::setPositionZ(float tz)
{
    _position.z = tz;
    dirty(DIRTY_TRANSLATION);
}

void C3DTransform::translate(float tx, float ty, float tz)
{
    _position.x += tx;
    _position.y += ty;
    _position.z += tz;
    dirty(DIRTY_TRANSLATION);
}

void C3DTransform::translate(const C3DVector3& translation)
{
    _position.x += translation.x;
    _position.y += translation.y;
    _position.z += translation.z;
    dirty(DIRTY_TRANSLATION);
}

void C3DTransform::translateX(float tx)
{
    _position.x += tx;
    dirty(DIRTY_TRANSLATION);
}

void C3DTransform::translateY(float ty)
{
    _position.y += ty;
    dirty(DIRTY_TRANSLATION);
}

void C3DTransform::translateZ(float tz)
{
    _position.z += tz;
    dirty(DIRTY_TRANSLATION);
}

void C3DTransform::translateRight(float amount)
{
    // Force the current transform matrix to be updated.
    getMatrix();

    C3DVector3 right;
    _matrix.getRightVector(&right);
    right.normalize();
    right.scale(amount);

    translate(right);
}

void C3DTransform::translateUp(float amount)
{
    // Force the current transform matrix to be updated.
    getMatrix();

    C3DVector3 up;
    _matrix.getUpVector(&up);
    up.normalize();
    up.scale(amount);

    translate(up);
}

void C3DTransform::translateForward(float amount)
{
    // Force the current transform matrix to be updated.
    getMatrix();

    C3DVector3 forward;
    _matrix.getForwardVector(&forward);
    forward.normalize();
    forward.scale(amount);

    translate(forward);
}

void C3DTransform::transformPoint(C3DVector3* point)
{
    getMatrix();
    _matrix.transformPoint(point);
}

void C3DTransform::transformPoint(const C3DVector3& point, C3DVector3* dst)
{
    getMatrix();
    _matrix.transformPoint(point, dst);
}

void C3DTransform::transformVector(C3DVector3* normal)
{
    getMatrix();
    _matrix.transformVector(normal);
}

void C3DTransform::transformVector(const C3DVector3& normal, C3DVector3* dst)
{
    getMatrix();
    _matrix.transformVector(normal, dst);
}

void C3DTransform::transformVector(float x, float y, float z, float w, C3DVector3* dst)
{
    getMatrix();
    _matrix.transformVector(x, y, z, w, dst);
}


void C3DTransform::dirty(char matrixDirtyBits)
{
    _matrixDirtyBits |= matrixDirtyBits;
    transformChanged();
}


void C3DTransform::lookAt(const C3DVector3& position, const C3DVector3& up, const C3DVector3& target)
{

	C3DMatrix matRotate;

    C3DVector3 upv = up;
    upv.normalize();

    C3DVector3 zaxis;
    C3DVector3::subtract(position, target, &zaxis);
    zaxis.normalize();

    C3DVector3 xaxis;
    C3DVector3::cross(upv, zaxis, &xaxis);
    xaxis.normalize();

    C3DVector3 yaxis;
    C3DVector3::cross(zaxis, xaxis, &yaxis);
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

void C3DTransform::copyFrom(const C3DTransform* other)
{
	_scale = other->_scale;
	_position = other->_position;
	_rotation = other->_rotation;
	_matrix = other->_matrix;
	_matrixDirtyBits = other->_matrixDirtyBits;

	transformChanged();
}

void C3DTransform::setRotationAlong(const C3DVector3& point, const C3DVector3& axis, float angle)
{
    // p' = rot * (p - point) + point = rot * p - rot * point + point
	_rotation.set(axis, angle);
    _position = point - _rotation * point;
    dirty(DIRTY_TRANSLATION | DIRTY_ROTATION);
}

void C3DTransform::rotateAlong(const C3DVector3& point, const C3DVector3& axis, float angle)
{
    C3DQuaternion rot(axis, angle);

    // p' = rot0 * p + pos0
    // p'' = rot * (p' - point) + point
    //     = rot * rot0 * p + rot * (pos0 - point) + point  

    _rotation = rot * _rotation;
    _position = rot * (_position - point) + point; 
    dirty(DIRTY_TRANSLATION | DIRTY_ROTATION);
}


}
