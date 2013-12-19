#include "Base.h"
#include "C3DMatrix.h"
#include "C3DQuaternion.h"

#include "C3DUtilty.h"
#include "C3DVector3.h"

#define MATRIX_SIZE     ( sizeof(float) * 16 )

namespace cocos3d
{

static const float MATRIX_IDENTITY[16] =
{
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

C3DMatrix::C3DMatrix()
{
    *this = C3DMatrix::identity();
}

C3DMatrix::C3DMatrix(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44)
{
    set(m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44);
}

C3DMatrix::C3DMatrix(const float* m)
{
    if (m)
        set(m);
    else
        *this = C3DMatrix::identity();
}

C3DMatrix::C3DMatrix(const C3DMatrix& copy)
{
    memcpy(m, copy.m, MATRIX_SIZE);
}

C3DMatrix::~C3DMatrix()
{
}

const C3DMatrix& C3DMatrix::identity()
{
    static C3DMatrix m(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1 );
    return m;
}

const C3DMatrix& C3DMatrix::zero()
{
    static C3DMatrix m(
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0 );
    return m;
}

C3DMatrix C3DMatrix::createFromVectors(C3DVector3& vx, C3DVector3& vy, C3DVector3& vz, C3DVector3& pos)
{
	C3DMatrix mat;
	
	vx.normalize();
	vy.normalize();
	vz.normalize();

	mat.m[0] = vx.x;
	mat.m[1] = vx.y;
	mat.m[2] = vx.z;
	mat.m[3] = 0.0f;

	mat.m[4] = vy.x;
	mat.m[5] = vy.y;
	mat.m[6] = vy.z;
	mat.m[7] = 0.0f;

	mat.m[8]  = vz.x;
	mat.m[9]  = vz.y;
	mat.m[10] = vz.z;
	mat.m[11] = 0.0f;

	mat.m[12] = pos.x;
	mat.m[13] = pos.y;
	mat.m[14] = pos.z;
	mat.m[15] = 1.0f;

	return mat;

}

void C3DMatrix::createPitchYawRoll(float pitch, float yaw, float roll, C3DMatrix* dst)
{
    float cr = cos(pitch);
    float sr = sin(pitch);
    float cp = cos(yaw);
    float sp = sin(yaw);
    float cy = cos(roll);
    float sy = sin(roll);
    float srsp = sr * sp;
    float crsp = cr * sp;

    dst->m[0] = cp * cy;
    dst->m[4] = cp * sy;
    dst->m[8] = - sp;

    dst->m[1] =  srsp * cy - cr * sy;
    dst->m[5] =  srsp * sy + cr * cy;
    dst->m[9] =  sr * cp;

    dst->m[2] = crsp * cy + sr * sy;
    dst->m[6] = crsp * sy - sr * cy;
    dst->m[10] = cr * cp;

    dst->m[3] = dst->m[7] = dst->m[11] = 0.0;
    dst->m[15] = 1.0;

}

void C3DMatrix::createLookAt(const C3DVector3& eyePosition, const C3DVector3& targetPosition, const C3DVector3& up, C3DMatrix* dst)
{
    createLookAt(eyePosition.x, eyePosition.y, eyePosition.z, targetPosition.x, targetPosition.y, targetPosition.z, up.x, up.y, up.z, dst);
}

void C3DMatrix::createLookAt(float eyePositionX, float eyePositionY, float eyePositionZ,
                          float targetPositionX, float targetPositionY, float targetPositionZ,
                          float upX, float upY, float upZ, C3DMatrix* dst)
{
    assert(dst);

    C3DVector3 eye(eyePositionX, eyePositionY, eyePositionZ);
    C3DVector3 target(targetPositionX, targetPositionY, targetPositionZ);
    C3DVector3 up(upX, upY, upZ);
    up.normalize();

    C3DVector3 zaxis;
    C3DVector3::subtract(eye, target, &zaxis);
    zaxis.normalize();

    C3DVector3 xaxis;
    C3DVector3::cross(up, zaxis, &xaxis);
    xaxis.normalize();

    C3DVector3 yaxis;
    C3DVector3::cross(zaxis, xaxis, &yaxis);
    yaxis.normalize();

    dst->m[0] = xaxis.x;
    dst->m[1] = yaxis.x;
    dst->m[2] = zaxis.x;
    dst->m[3] = 0.0f;

    dst->m[4] = xaxis.y;
    dst->m[5] = yaxis.y;
    dst->m[6] = zaxis.y;
    dst->m[7] = 0.0f;

    dst->m[8] = xaxis.z;
    dst->m[9] = yaxis.z;
    dst->m[10] = zaxis.z;
    dst->m[11] = 0.0f;

    dst->m[12] = -C3DVector3::dot(xaxis, eye);
    dst->m[13] = -C3DVector3::dot(yaxis, eye);
    dst->m[14] = -C3DVector3::dot(zaxis, eye);
    dst->m[15] = 1.0f;
}
//
//void C3DMatrix::createAxis(C3DVector3& position, C3DVector3& xaxis, C3DVector3& yaxis, C3DVector3& zaxis, C3DMatrix* dst)
//{
//	zaxis.normalize();
//	xaxis.normalize();
//	yaxis.normalize();
//
//	dst->m[0] = xaxis.x;
//	dst->m[1] = yaxis.x;
//	dst->m[2] = zaxis.x;
//	dst->m[3] = 0.0f;
//
//	dst->m[4] = xaxis.y;
//	dst->m[5] = yaxis.y;
//	dst->m[6] = zaxis.y;
//	dst->m[7] = 0.0f;
//
//	dst->m[8] = xaxis.z;
//	dst->m[9] = yaxis.z;
//	dst->m[10] = zaxis.z;
//	dst->m[11] = 0.0f;
//
//	dst->m[12] = -C3DVector3::dot(xaxis, position);
//	dst->m[13] = -C3DVector3::dot(yaxis, position);
//	dst->m[14] = -C3DVector3::dot(zaxis, position);
//	dst->m[15] = 1.0f;
//}

void C3DMatrix::createPerspective(float fieldOfView, float aspectRatio,
                                     float zNearPlane, float zFarPlane, C3DMatrix* dst)
{
    assert(dst);

    float f_n = 1.0f / (zFarPlane - zNearPlane);
    float factor = 1.0f / tanf(MATH_DEG_TO_RAD(fieldOfView) * 0.5f);

    memset(dst, 0, MATRIX_SIZE);

    dst->m[0] = (1.0f / aspectRatio) * factor;
    dst->m[5] = factor;
    dst->m[10] = (-(zFarPlane + zNearPlane)) * f_n;
    dst->m[11] = -1.0f;
    dst->m[14] = -2.0f * zFarPlane * zNearPlane * f_n;
}

void C3DMatrix::createPerspectiveFOV(float width, float height, float zNear, float zFar, C3DMatrix* dst)
{
	float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;
	createPerspectiveOffCenter(-halfWidth, halfWidth, -halfHeight, halfHeight, zNear, zFar, dst);
}

void C3DMatrix::createPerspectiveOffCenter(float left, float right, float bottom, float top,
                                         float zNear, float zFar, C3DMatrix* dst)
{
    assert(dst);

    float r_l = 1.0f / (right - left);
    float t_b = 1.0f / (top - bottom);
    float f_n = 1.0f / (zFar - zNear);

    memset(dst, 0, MATRIX_SIZE);
    dst->m[0] = 2.0f * zNear * r_l;
    dst->m[5] = 2.0f * zNear * t_b;
	dst->m[8] = (right + left) * r_l;
	dst->m[9] = (top + bottom) * t_b;
	dst->m[10] = (-(zFar + zNear)) * f_n;
	dst->m[11] = -1.0f;
    dst->m[14] = -2.0f * zNear * zFar * f_n;
   
}


void C3DMatrix::createOrthographic(float width, float height, float zNearPlane, float zFarPlane, C3DMatrix* dst)
{
    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;
    createOrthographicOffCenter(-halfWidth, halfWidth, -halfHeight, halfHeight, zNearPlane, zFarPlane, dst);
}

void C3DMatrix::createOrthographicOffCenter(float left, float right, float bottom, float top,
                                         float zNearPlane, float zFarPlane, C3DMatrix* dst)
{
    assert(dst);

    float r_l = 1.0f / (right - left);
    float t_b = 1.0f / (top - bottom);
    float f_n = 1.0f / (zFarPlane - zNearPlane);

    memset(dst, 0, MATRIX_SIZE);
    dst->m[0] = 2.0f * r_l;
    dst->m[5] = 2.0f * t_b;
    dst->m[10] = -2.0f * f_n;
    dst->m[12] = (-(right + left)) * r_l;
    dst->m[13] = (-(top + bottom)) * t_b;
    dst->m[14] = (-(zFarPlane + zNearPlane)) * f_n;
    dst->m[15] = 1.0f;
}

void C3DMatrix::createScale(const C3DVector3& scale, C3DMatrix* dst)
{
    assert(dst);

    memcpy(dst, MATRIX_IDENTITY, MATRIX_SIZE);

    dst->m[0] = scale.x;
    dst->m[5] = scale.y;
    dst->m[10] = scale.z;
}

void C3DMatrix::createScale(float xScale, float yScale, float zScale, C3DMatrix* dst)
{
    assert(dst);

    memcpy(dst, MATRIX_IDENTITY, MATRIX_SIZE);

    dst->m[0] = xScale;
    dst->m[5] = yScale;
    dst->m[10] = zScale;
}


void C3DMatrix::createRotation(const C3DQuaternion& q, C3DMatrix* dst)
{
    assert(dst);

    float x2 = q.x + q.x;
    float y2 = q.y + q.y;
    float z2 = q.z + q.z;

    float xx2 = q.x * x2;
    float yy2 = q.y * y2;
    float zz2 = q.z * z2;
    float xy2 = q.x * y2;
    float xz2 = q.x * z2;
    float yz2 = q.y * z2;
    float wx2 = q.w * x2;
    float wy2 = q.w * y2;
    float wz2 = q.w * z2;

    dst->m[0] = 1.0f - yy2 - zz2;
    dst->m[1] = xy2 + wz2;
    dst->m[2] = xz2 - wy2;
    dst->m[3] = 0.0f;

    dst->m[4] = xy2 - wz2;
    dst->m[5] = 1.0f - xx2 - zz2;
    dst->m[6] = yz2 + wx2;
    dst->m[7] = 0.0f;

    dst->m[8] = xz2 + wy2;
    dst->m[9] = yz2 - wx2;
    dst->m[10] = 1.0f - xx2 - yy2;
    dst->m[11] = 0.0f;

    dst->m[12] = 0.0f;
    dst->m[13] = 0.0f;
    dst->m[14] = 0.0f;
    dst->m[15] = 1.0f;
}

void C3DMatrix::createRotation(const C3DVector3& axis, float angle, C3DMatrix* dst, bool approximate)
{
    assert(dst);

    float x = axis.x;
    float y = axis.y;
    float z = axis.z;

    // Make sure the input axis is normalized.
    float n = x*x + y*y + z*z;
    if (n != 1.0f)
    {
        // Not normalized.
        n = sqrt(n);
        // Prevent divide too close to zero.
        if (n > 0.000001f)
        {
            n = 1.0f / n;
            x *= n;
            y *= n;
            z *= n;
        }
    }

    float c, s;
    if (approximate)
    {
        C3DUtility::getInstance().sincos(angle, &s, &c);
    }
    else
    {
        c = cos(angle);
        s = sin(angle);
    }
    

    float t = 1.0f - c;
    float tx = t * x;
    float ty = t * y;
    float tz = t * z;
    float txy = tx * y;
    float txz = tx * z;
    float tyz = ty * z;
    float sx = s * x;
    float sy = s * y;
    float sz = s * z;

    dst->m[0] = c + tx*x;
    dst->m[1] = txy + sz;
    dst->m[2] = txz - sy;
    dst->m[3] = 0.0f;

    dst->m[4] = txy - sz;
    dst->m[5] = c + ty*y;
    dst->m[6] = tyz + sx;
    dst->m[7] = 0.0f;

    dst->m[8] = txz + sy;
    dst->m[9] = tyz - sx;
    dst->m[10] = c + tz*z;
    dst->m[11] = 0.0f;

    dst->m[12] = 0.0f;
    dst->m[13] = 0.0f;
    dst->m[14] = 0.0f;
    dst->m[15] = 1.0f;
}

void C3DMatrix::createRotationX(float angle, C3DMatrix* dst)
{
    assert(dst);

    memcpy(dst, MATRIX_IDENTITY, MATRIX_SIZE);

    float c = cos(angle);
    float s = sin(angle);

    dst->m[5]  = c;
    dst->m[6]  = s;
    dst->m[9]  = -s;
    dst->m[10] = c;
}

void C3DMatrix::createRotationY(float angle, C3DMatrix* dst)
{
    assert(dst);

    memcpy(dst, MATRIX_IDENTITY, MATRIX_SIZE);

    float c = cos(angle);
    float s = sin(angle);

    dst->m[0]  = c;
    dst->m[2]  = -s;
    dst->m[8]  = s;
    dst->m[10] = c;
}

void C3DMatrix::createRotationZ(float angle, C3DMatrix* dst)
{
    assert(dst);

    memcpy(dst, MATRIX_IDENTITY, MATRIX_SIZE);

    float c = cos(angle);
    float s = sin(angle);

    dst->m[0] = c;
    dst->m[1] = s;
    dst->m[4] = -s;
    dst->m[5] = c;
}

void C3DMatrix::createTranslation(const C3DVector3& translation, C3DMatrix* dst)
{
    assert(dst);

    memcpy(dst, MATRIX_IDENTITY, MATRIX_SIZE);

    dst->m[12] = translation.x;
    dst->m[13] = translation.y;
    dst->m[14] = translation.z;
}

void C3DMatrix::createTranslation(float xTranslation, float yTranslation, float zTranslation, C3DMatrix* dst)
{
    assert(dst);

    memcpy(dst, MATRIX_IDENTITY, MATRIX_SIZE);

    dst->m[12] = xTranslation;
    dst->m[13] = yTranslation;
    dst->m[14] = zTranslation;
}

void C3DMatrix::add(float scalar)
{
    add(scalar, this);
}

void C3DMatrix::add(float scalar, C3DMatrix* dst)
{
    assert(dst);

    dst->m[0]  = m[0]  + scalar;
    dst->m[1]  = m[1]  + scalar;
    dst->m[2]  = m[2]  + scalar;
    dst->m[3]  = m[3]  + scalar;
    dst->m[4]  = m[4]  + scalar;
    dst->m[5]  = m[5]  + scalar;
    dst->m[6]  = m[6]  + scalar;
    dst->m[7]  = m[7]  + scalar;
    dst->m[8]  = m[8]  + scalar;
    dst->m[9]  = m[9]  + scalar;
    dst->m[10] = m[10] + scalar;
    dst->m[11] = m[11] + scalar;
    dst->m[12] = m[12] + scalar;
    dst->m[13] = m[13] + scalar;
    dst->m[14] = m[14] + scalar;
    dst->m[15] = m[15] + scalar;
}

void C3DMatrix::add(const C3DMatrix& m)
{
    add(*this, m, this);
}

void C3DMatrix::add(const C3DMatrix& m1, const C3DMatrix& m2, C3DMatrix* dst)
{
    assert(dst);

    dst->m[0]  = m1.m[0]  + m2.m[0];
    dst->m[1]  = m1.m[1]  + m2.m[1];
    dst->m[2]  = m1.m[2]  + m2.m[2];
    dst->m[3]  = m1.m[3]  + m2.m[3];
    dst->m[4]  = m1.m[4]  + m2.m[4];
    dst->m[5]  = m1.m[5]  + m2.m[5];
    dst->m[6]  = m1.m[6]  + m2.m[6];
    dst->m[7]  = m1.m[7]  + m2.m[7];
    dst->m[8]  = m1.m[8]  + m2.m[8];
    dst->m[9]  = m1.m[9]  + m2.m[9];
    dst->m[10] = m1.m[10] + m2.m[10];
    dst->m[11] = m1.m[11] + m2.m[11];
    dst->m[12] = m1.m[12] + m2.m[12];
    dst->m[13] = m1.m[13] + m2.m[13];
    dst->m[14] = m1.m[14] + m2.m[14];
    dst->m[15] = m1.m[15] + m2.m[15];
}

bool C3DMatrix::decompose(C3DVector3* scale, C3DQuaternion* rotation, C3DVector3* translation) const
{
    if (translation)
    {
        // Extract the translation.
        translation->x = m[12];
        translation->y = m[13];
        translation->z = m[14];
    }

    // Nothing left to do.
    if (scale == NULL && rotation == NULL)
        return true;

    // Extract the scale.
    // This is simply the length of each axis (row/column) in the matrix.
    C3DVector3 xaxis(m[0], m[1], m[2]);
    float scaleX = xaxis.length();

    C3DVector3 yaxis(m[4], m[5], m[6]);
    float scaleY = yaxis.length();

    C3DVector3 zaxis(m[8], m[9], m[10]);
    float scaleZ = zaxis.length();

    // Determine if we have a negative scale (true if determinant is less than zero).
    // In this case, we simply negate a single axis of the scale.
    float det = determinant();
    if (det < 0)
        scaleZ = -scaleZ;

    if (scale)
    {
        scale->x = scaleX;
        scale->y = scaleY;
        scale->z = scaleZ;
    }

    // Nothing left to do.
    if (rotation == NULL)
        return true;

    // Scale too close to zero, can't decompose rotation.
    if (scaleX < MATH_TOLERANCE || scaleY < MATH_TOLERANCE || fabs(scaleZ) < MATH_TOLERANCE)
        return false;

    float rn;

    // Factor the scale out of the matrix axes.
    rn = 1.0f / scaleX;
    xaxis.x *= rn;
    xaxis.y *= rn;
    xaxis.z *= rn;

    rn = 1.0f / scaleY;
    yaxis.x *= rn;
    yaxis.y *= rn;
    yaxis.z *= rn;

    rn = 1.0f / scaleZ;
    zaxis.x *= rn;
    zaxis.y *= rn;
    zaxis.z *= rn;

    // Now calculate the rotation from the resulting matrix (axes).
    float trace = xaxis.x + yaxis.y + zaxis.z + 1.0f;

    if (trace > MATH_EPSILON)
    {
        float s = 0.5f / sqrt(trace);
        rotation->w = 0.25f / s;
        rotation->x = ( yaxis.z - zaxis.y ) * s;
        rotation->y = ( zaxis.x - xaxis.z ) * s;
        rotation->z = ( xaxis.y - yaxis.x ) * s;
    } 
    else
    {
        if (xaxis.x > yaxis.y && xaxis.x > zaxis.z)
        {
            float s = 2.0f * sqrt(1.0f + xaxis.x - yaxis.y - zaxis.z);
            rotation->w = (yaxis.z - zaxis.y ) / s;
            rotation->x = 0.25f * s;
            rotation->y = (yaxis.x + xaxis.y ) / s;
            rotation->z = (zaxis.x + xaxis.z ) / s;
        }
        else if (yaxis.y > zaxis.z)
        {
            float s = 2.0f * sqrt(1.0f + yaxis.y - xaxis.x - zaxis.z);
            rotation->w = (zaxis.x - xaxis.z ) / s;
            rotation->x = (yaxis.x + xaxis.y ) / s;
            rotation->y = 0.25f * s;
            rotation->z = (zaxis.y + yaxis.z ) / s;
        }
        else
        {
            float s = 2.0f * sqrt(1.0f + zaxis.z - xaxis.x - yaxis.y );
            rotation->w = (xaxis.y - yaxis.x ) / s;
            rotation->x = (zaxis.x + xaxis.z ) / s;
            rotation->y = (zaxis.y + yaxis.z ) / s;
            rotation->z = 0.25f * s;
        }
    }

    return true;
}

float C3DMatrix::determinant() const
{
    float a0 = m[0] * m[5] - m[1] * m[4];
    float a1 = m[0] * m[6] - m[2] * m[4];
    float a2 = m[0] * m[7] - m[3] * m[4];
    float a3 = m[1] * m[6] - m[2] * m[5];
    float a4 = m[1] * m[7] - m[3] * m[5];
    float a5 = m[2] * m[7] - m[3] * m[6];
    float b0 = m[8] * m[13] - m[9] * m[12];
    float b1 = m[8] * m[14] - m[10] * m[12];
    float b2 = m[8] * m[15] - m[11] * m[12];
    float b3 = m[9] * m[14] - m[10] * m[13];
    float b4 = m[9] * m[15] - m[11] * m[13];
    float b5 = m[10] * m[15] - m[11] * m[14];

    // Calculate the determinant.
    return (a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0);
}

void C3DMatrix::getScale(C3DVector3* scale) const
{
    decompose(scale, NULL, NULL);
}

bool C3DMatrix::getRotation(C3DQuaternion* rotation) const
{
    return decompose(NULL, rotation, NULL);
}

void C3DMatrix::getPosition(C3DVector3* translation) const
{
    decompose(NULL, NULL, translation);
}

void C3DMatrix::getUpVector(C3DVector3* dst) const
{
    assert(dst);

    //dst->x = m[8];
    //dst->y = m[9];
    //dst->z = m[10];

	    dst->x = m[4];
    dst->y = m[5];
    dst->z = m[6];
}


void C3DMatrix::getRightVector(C3DVector3* dst) const
{
    assert(dst);

    dst->x = m[0];
    dst->y = m[1];
    dst->z = m[2];
}

void C3DMatrix::getForwardVector(C3DVector3* dst) const
{
    assert(dst);

    //dst->x = -m[4];
    //dst->y = -m[5];
    //dst->z = -m[6];

	dst->x = -m[8];
    dst->y = -m[9];
    dst->z = -m[10];
}


bool C3DMatrix::invert()
{
    return invert(this);
}

bool C3DMatrix::invert(C3DMatrix* dst) const
{
    float a0 = m[0] * m[5] - m[1] * m[4];
    float a1 = m[0] * m[6] - m[2] * m[4];
    float a2 = m[0] * m[7] - m[3] * m[4];
    float a3 = m[1] * m[6] - m[2] * m[5];
    float a4 = m[1] * m[7] - m[3] * m[5];
    float a5 = m[2] * m[7] - m[3] * m[6];
    float b0 = m[8] * m[13] - m[9] * m[12];
    float b1 = m[8] * m[14] - m[10] * m[12];
    float b2 = m[8] * m[15] - m[11] * m[12];
    float b3 = m[9] * m[14] - m[10] * m[13];
    float b4 = m[9] * m[15] - m[11] * m[13];
    float b5 = m[10] * m[15] - m[11] * m[14];

    // Calculate the determinant.
    float det = a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;

    // Close to zero, can't invert.
    if (fabs(det) <= MATH_TOLERANCE)
        return false;

    // Support the case where m == dst.
    C3DMatrix inverse;
    inverse.m[0]  = m[5] * b5 - m[6] * b4 + m[7] * b3;
    inverse.m[1]  = -m[1] * b5 + m[2] * b4 - m[3] * b3;
    inverse.m[2]  = m[13] * a5 - m[14] * a4 + m[15] * a3;
    inverse.m[3]  = -m[9] * a5 + m[10] * a4 - m[11] * a3;

    inverse.m[4]  = -m[4] * b5 + m[6] * b2 - m[7] * b1;
    inverse.m[5]  = m[0] * b5 - m[2] * b2 + m[3] * b1;
    inverse.m[6]  = -m[12] * a5 + m[14] * a2 - m[15] * a1;
    inverse.m[7]  = m[8] * a5 - m[10] * a2 + m[11] * a1;

    inverse.m[8]  = m[4] * b4 - m[5] * b2 + m[7] * b0;
    inverse.m[9]  = -m[0] * b4 + m[1] * b2 - m[3] * b0;
    inverse.m[10] = m[12] * a4 - m[13] * a2 + m[15] * a0;
    inverse.m[11] = -m[8] * a4 + m[9] * a2 - m[11] * a0;

    inverse.m[12] = -m[4] * b3 + m[5] * b1 - m[6] * b0;
    inverse.m[13] = m[0] * b3 - m[1] * b1 + m[2] * b0;
    inverse.m[14] = -m[12] * a3 + m[13] * a1 - m[14] * a0;
    inverse.m[15] = m[8] * a3 - m[9] * a1 + m[10] * a0;

    multiply(inverse, 1.0f / det, dst);

    return true;
}

bool C3DMatrix::isIdentity() const
{
    return (memcmp(m, MATRIX_IDENTITY, MATRIX_SIZE) == 0);
}

void C3DMatrix::multiply(float scalar)
{
    multiply(scalar, this);
}

void C3DMatrix::multiply(float scalar, C3DMatrix* dst) const
{
    multiply(*this, scalar, dst);
}

void C3DMatrix::multiply(const C3DMatrix& m, float scalar, C3DMatrix* dst)
{
    assert(dst);

    dst->m[0]  = m.m[0]  * scalar;
    dst->m[1]  = m.m[1]  * scalar;
    dst->m[2]  = m.m[2]  * scalar;
    dst->m[3]  = m.m[3]  * scalar;
    dst->m[4]  = m.m[4]  * scalar;
    dst->m[5]  = m.m[5]  * scalar;
    dst->m[6]  = m.m[6]  * scalar;
    dst->m[7]  = m.m[7]  * scalar;
    dst->m[8]  = m.m[8]  * scalar;
    dst->m[9]  = m.m[9]  * scalar;
    dst->m[10] = m.m[10] * scalar;
    dst->m[11] = m.m[11] * scalar;
    dst->m[12] = m.m[12] * scalar;
    dst->m[13] = m.m[13] * scalar;
    dst->m[14] = m.m[14] * scalar;
    dst->m[15] = m.m[15] * scalar;
}

void C3DMatrix::multiply(const C3DMatrix& m)
{
    multiply(*this, m, this);
}

void C3DMatrix::multiply(const C3DMatrix& m1, const C3DMatrix& m2, C3DMatrix* dst)
{
    assert(dst);

    // Support the case where m1 or m2 is the same array as dst.
    float product[16];

    product[0]  = m1.m[0] * m2.m[0]  + m1.m[4] * m2.m[1] + m1.m[8]   * m2.m[2]  + m1.m[12] * m2.m[3];
    product[1]  = m1.m[1] * m2.m[0]  + m1.m[5] * m2.m[1] + m1.m[9]   * m2.m[2]  + m1.m[13] * m2.m[3];
    product[2]  = m1.m[2] * m2.m[0]  + m1.m[6] * m2.m[1] + m1.m[10]  * m2.m[2]  + m1.m[14] * m2.m[3];
    product[3]  = m1.m[3] * m2.m[0]  + m1.m[7] * m2.m[1] + m1.m[11]  * m2.m[2]  + m1.m[15] * m2.m[3];

    product[4]  = m1.m[0] * m2.m[4]  + m1.m[4] * m2.m[5] + m1.m[8]   * m2.m[6]  + m1.m[12] * m2.m[7];
    product[5]  = m1.m[1] * m2.m[4]  + m1.m[5] * m2.m[5] + m1.m[9]   * m2.m[6]  + m1.m[13] * m2.m[7];
    product[6]  = m1.m[2] * m2.m[4]  + m1.m[6] * m2.m[5] + m1.m[10]  * m2.m[6]  + m1.m[14] * m2.m[7];
    product[7]  = m1.m[3] * m2.m[4]  + m1.m[7] * m2.m[5] + m1.m[11]  * m2.m[6]  + m1.m[15] * m2.m[7];

    product[8]  = m1.m[0] * m2.m[8]  + m1.m[4] * m2.m[9] + m1.m[8]   * m2.m[10] + m1.m[12] * m2.m[11];
    product[9]  = m1.m[1] * m2.m[8]  + m1.m[5] * m2.m[9] + m1.m[9]   * m2.m[10] + m1.m[13] * m2.m[11];
    product[10] = m1.m[2] * m2.m[8]  + m1.m[6] * m2.m[9] + m1.m[10]  * m2.m[10] + m1.m[14] * m2.m[11];
    product[11] = m1.m[3] * m2.m[8]  + m1.m[7] * m2.m[9] + m1.m[11]  * m2.m[10] + m1.m[15] * m2.m[11];

    product[12] = m1.m[0] * m2.m[12] + m1.m[4] * m2.m[13] + m1.m[8]  * m2.m[14] + m1.m[12] * m2.m[15];
    product[13] = m1.m[1] * m2.m[12] + m1.m[5] * m2.m[13] + m1.m[9]  * m2.m[14] + m1.m[13] * m2.m[15];
    product[14] = m1.m[2] * m2.m[12] + m1.m[6] * m2.m[13] + m1.m[10] * m2.m[14] + m1.m[14] * m2.m[15];
    product[15] = m1.m[3] * m2.m[12] + m1.m[7] * m2.m[13] + m1.m[11] * m2.m[14] + m1.m[15] * m2.m[15];

    memcpy(dst->m, product, MATRIX_SIZE);
}

void C3DMatrix::negate()
{
    negate(this);
}

void C3DMatrix::negate(C3DMatrix* dst) const
{
    dst->m[0]  = -m[0];
    dst->m[1]  = -m[1];
    dst->m[2]  = -m[2];
    dst->m[3]  = -m[3];
    dst->m[4]  = -m[4];
    dst->m[5]  = -m[5];
    dst->m[6]  = -m[6];
    dst->m[7]  = -m[7];
    dst->m[8]  = -m[8];
    dst->m[9]  = -m[9];
    dst->m[10] = -m[10];
    dst->m[11] = -m[11];
    dst->m[12] = -m[12];
    dst->m[13] = -m[13];
    dst->m[14] = -m[14];
    dst->m[15] = -m[15];
}

void C3DMatrix::rotate(const C3DQuaternion& q)
{
    rotate(q, this);
}

void C3DMatrix::rotate(const C3DQuaternion& q, C3DMatrix* dst) const
{
    C3DMatrix r;
    createRotation(q, &r);
    multiply(*this, r, dst);
}

void C3DMatrix::rotate(const C3DVector3& axis, float angle)
{
    rotate(axis, angle, this);
}

void C3DMatrix::rotate(const C3DVector3& axis, float angle, C3DMatrix* dst) const
{
    C3DMatrix r;
    createRotation(axis, angle, &r);
    multiply(*this, r, dst);
}

void C3DMatrix::rotateX(float angle)
{
    rotateX(angle, this);
}

void C3DMatrix::rotateX(float angle, C3DMatrix* dst) const
{
    C3DMatrix r;
    createRotationX(angle, &r);
    multiply(*this, r, dst);
}

void C3DMatrix::rotateY(float angle)
{
    rotateY(angle, this);
}

void C3DMatrix::rotateY(float angle, C3DMatrix* dst) const
{
    C3DMatrix r;
    createRotationY(angle, &r);
    multiply(*this, r, dst);
}

void C3DMatrix::rotateZ(float angle)
{
    rotateZ(angle, this);
}

void C3DMatrix::rotateZ(float angle, C3DMatrix* dst) const
{
    assert(dst);

    C3DMatrix r;
    createRotationZ(angle, &r);
    multiply(*this, r, dst);
}

void C3DMatrix::scale(float value)
{
    scale(value, this);
}

void C3DMatrix::scale(float value, C3DMatrix* dst) const
{
    scale(value, value, value, dst);
}

void C3DMatrix::scale(float xScale, float yScale, float zScale)
{
    scale(xScale, yScale, zScale, this);
}

void C3DMatrix::setScale(float xScale,float yScale,float zScale)
{	
    this->m[0] = xScale;
    this->m[5] = yScale;
    this->m[10] = zScale;
}

void C3DMatrix::scale(float xScale, float yScale, float zScale, C3DMatrix* dst) const
{
    assert(dst);

    C3DMatrix s;
    createScale(xScale, yScale, zScale, &s);
    multiply(*this, s, dst);
}

void C3DMatrix::scale(const C3DVector3& s)
{
    scale(s.x, s.y, s.z, this);
}

void C3DMatrix::scale(const C3DVector3& s, C3DMatrix* dst) const
{
    scale(s.x, s.y, s.z, dst);
}

void C3DMatrix::set(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44)
{
    m[0]  = m11;
    m[1]  = m21;
    m[2]  = m31;
    m[3]  = m41;
    m[4]  = m12;
    m[5]  = m22;
    m[6]  = m32;
    m[7]  = m42;
    m[8]  = m13;
    m[9]  = m23;
    m[10] = m33;
    m[11] = m43;
    m[12] = m14;
    m[13] = m24;
    m[14] = m34;
    m[15] = m44;
}

void C3DMatrix::set(const float* m)
{
    assert(m);
    memcpy(this->m, m, MATRIX_SIZE);
}

void C3DMatrix::set(const C3DMatrix& m)
{
    memcpy(this->m, m.m, MATRIX_SIZE);
}

void C3DMatrix::setCol(int idx, const C3DVector3& col)
{
	if (idx > 4)
		return;
	idx *= 4;
	m[idx++] = col.x;
	m[idx++] = col.y;
	m[idx] = col.z;
}

C3DVector3 C3DMatrix::getCol(int idx) const
{
	if (idx > 4)
		return C3DVector3::zero();
	static C3DVector3 col;
	idx *= 4;
	col.set(m[idx], m[idx+1], m[idx+2]);
	return col;
}

void C3DMatrix::getCol(int idx, C3DVector3& col) const
{
	if (idx > 4)
		return;
	idx *= 4;
	col.set(m[idx], m[idx+1], m[idx+2]);
}

void C3DMatrix::setIdentity()
{
    memcpy(m, MATRIX_IDENTITY, MATRIX_SIZE);
}

void C3DMatrix::setZero()
{
    memset(m, 0, MATRIX_SIZE);
}

void C3DMatrix::subtract(const C3DMatrix& m)
{
    subtract(*this, m, this);
}

void C3DMatrix::subtract(const C3DMatrix& m1, const C3DMatrix& m2, C3DMatrix* dst)
{
    dst->m[0]  = m1.m[0]  - m2.m[0];
    dst->m[1]  = m1.m[1]  - m2.m[1];
    dst->m[2]  = m1.m[2]  - m2.m[2];
    dst->m[3]  = m1.m[3]  - m2.m[3];
    dst->m[4]  = m1.m[4]  - m2.m[4];
    dst->m[5]  = m1.m[5]  - m2.m[5];
    dst->m[6]  = m1.m[6]  - m2.m[6];
    dst->m[7]  = m1.m[7]  - m2.m[7];
    dst->m[8]  = m1.m[8]  - m2.m[8];
    dst->m[9]  = m1.m[9]  - m2.m[9];
    dst->m[10] = m1.m[10] - m2.m[10];
    dst->m[11] = m1.m[11] - m2.m[11];
    dst->m[12] = m1.m[12] - m2.m[12];
    dst->m[13] = m1.m[13] - m2.m[13];
    dst->m[14] = m1.m[14] - m2.m[14];
    dst->m[15] = m1.m[15] - m2.m[15];
}

void C3DMatrix::transformPoint(C3DVector3* point) const
{
    transformVector(point->x, point->y, point->z, 1.0f, point);
}

void C3DMatrix::transformPoint(const C3DVector3& point, C3DVector3* dst) const
{
    transformVector(point.x, point.y, point.z, 1.0f, dst);
}

void C3DMatrix::transformVector(C3DVector3* vector) const
{
    transformVector(vector->x, vector->y, vector->z, vector);
}

void C3DMatrix::transformVector(const C3DVector3& vector, C3DVector3* dst) const
{
    transformVector(vector.x, vector.y, vector.z, dst);
}

void C3DMatrix::transformVector(float x, float y, float z, float w, C3DVector3* dst) const
{
    assert(dst);
    
    dst->set(
        x * m[0] + y * m[4] + z * m[8] + w * m[12],
        x * m[1] + y * m[5] + z * m[9] + w * m[13],
        x * m[2] + y * m[6] + z * m[10] + w * m[14] );
}
    
void C3DMatrix::transformVector(float x, float y, float z, C3DVector3* dst) const
{
    assert(dst);
    
    dst->set(x * m[0] + y * m[4] + z * m[8],
             x * m[1] + y * m[5] + z * m[9],
             x * m[2] + y * m[6] + z * m[10]);
}

void C3DMatrix::transformVector(C3DVector4* vector) const
{
    transformVector(*vector, vector);
}

void C3DMatrix::transformVector(const C3DVector4& vector, C3DVector4* dst) const
{
    assert(dst);

    dst->set(
        vector.x * m[0] + vector.y * m[4] + vector.z * m[8] + vector.w * m[12],
        vector.x * m[1] + vector.y * m[5] + vector.z * m[9] + vector.w * m[13],
        vector.x * m[2] + vector.y * m[6] + vector.z * m[10] + vector.w * m[14],
        vector.x * m[3] + vector.y * m[7] + vector.z * m[11] + vector.w * m[15] );
}

void C3DMatrix::translate(float x, float y, float z)
{
    translate(x, y, z, this);
}

void C3DMatrix::translate(float x, float y, float z, C3DMatrix* dst) const
{
    assert(dst);

    C3DMatrix t;
    createTranslation(x, y, z, &t);
    multiply(*this, t, dst);
}

void C3DMatrix::translate(const C3DVector3& t)
{
    translate(t.x, t.y, t.z, this);
}

void C3DMatrix::translate(const C3DVector3& t, C3DMatrix* dst) const
{
    translate(t.x, t.y, t.z, dst);
}

void C3DMatrix::transpose()
{
    transpose(this);
}

void C3DMatrix::transpose(C3DMatrix* dst) const
{
    assert(dst);
    
    float t[16] = {
        m[0], m[4], m[8], m[12],
        m[1], m[5], m[9], m[13],
        m[2], m[6], m[10], m[14],
        m[3], m[7], m[11], m[15]
    };
    memcpy(dst->m, t, MATRIX_SIZE);
}
    
C3DMatrix& C3DMatrix::invertOrthMat()
{
    C3DMatrix src = *this;
    C3DMatrix::invertOrthMat(src, *this);
    return *this;
}
    
void C3DMatrix::invertOrthMat(const C3DMatrix& mat, C3DMatrix& invMat)
{
    invMat.m[0] = mat.m[0];
    invMat.m[1] = mat.m[4];
    invMat.m[2] = mat.m[8];
    
    invMat.m[4] = mat.m[1];
    invMat.m[5] = mat.m[5];
    invMat.m[6] = mat.m[9];
    
    invMat.m[8] = mat.m[2];
    invMat.m[9] = mat.m[6];
    invMat.m[10] = mat.m[10];
    
    invMat.m[3] = invMat.m[7] = invMat.m[11] = 0.0f;
    
    invMat.m[12] = -mat.m[0] * mat.m[12] - mat.m[1] * mat.m[13] - mat.m[2] * mat.m[14];
    invMat.m[13] = -mat.m[4] * mat.m[12] - mat.m[5] * mat.m[13] - mat.m[6] * mat.m[14];
    invMat.m[14] = -mat.m[8] * mat.m[12] - mat.m[9] * mat.m[13] - mat.m[10] * mat.m[14];
    invMat.m[15] = 1.0f;
}

}
