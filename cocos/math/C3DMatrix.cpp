#include "CocosMath.h"

#include "neonmatriximpl.h"

#define MATRIX_SIZE     ( sizeof(float) * 16 )

NS_CC_BEGIN

static const float MATRIX_IDENTITY[16] =
{
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

Matrix::Matrix()
{
    *this = Matrix::identity();
}

Matrix::Matrix(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44)
{
    set(m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44);
}

Matrix::Matrix(const float* m1)
{
    if (m1)
        set(m1);
    else
        *this = Matrix::identity();
}

Matrix::Matrix(const Matrix& copy)
{
    memcpy(m, copy.m, MATRIX_SIZE);
}

Matrix::~Matrix()
{
}

const Matrix& Matrix::identity()
{
    static Matrix m(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1 );
    return m;
}

const Matrix& Matrix::zero()
{
    static Matrix m(
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0 );
    return m;
}

Matrix Matrix::createFromVectors(Vector3& vx, Vector3& vy, Vector3& vz, Vector3& pos)
{
    Matrix mat;
    
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

void Matrix::createPitchYawRoll(float pitch, float yaw, float roll, Matrix* dst)
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

void Matrix::createLookAt(const Vector3& eyePosition, const Vector3& targetPosition, const Vector3& up, Matrix* dst)
{
    createLookAt(eyePosition.x, eyePosition.y, eyePosition.z, targetPosition.x, targetPosition.y, targetPosition.z, up.x, up.y, up.z, dst);
}

void Matrix::createLookAt(float eyePositionX, float eyePositionY, float eyePositionZ,
                          float targetPositionX, float targetPositionY, float targetPositionZ,
                          float upX, float upY, float upZ, Matrix* dst)
{
    assert(dst);

    Vector3 eye(eyePositionX, eyePositionY, eyePositionZ);
    Vector3 target(targetPositionX, targetPositionY, targetPositionZ);
    Vector3 up(upX, upY, upZ);
    up.normalize();

    Vector3 zaxis;
    Vector3::subtract(eye, target, &zaxis);
    zaxis.normalize();

    Vector3 xaxis;
    Vector3::cross(up, zaxis, &xaxis);
    xaxis.normalize();

    Vector3 yaxis;
    Vector3::cross(zaxis, xaxis, &yaxis);
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

    dst->m[12] = -Vector3::dot(xaxis, eye);
    dst->m[13] = -Vector3::dot(yaxis, eye);
    dst->m[14] = -Vector3::dot(zaxis, eye);
    dst->m[15] = 1.0f;
}

void Matrix::createPerspective(float fieldOfView, float aspectRatio,
                                     float zNearPlane, float zFarPlane, Matrix* dst)
{
    assert(dst);

    float f_n = 1.0f / (zFarPlane - zNearPlane);
    float factor = 1.0f / tanf(CC_DEGREES_TO_RADIANS(fieldOfView) * 0.5f);

    memset(dst, 0, MATRIX_SIZE);

    dst->m[0] = (1.0f / aspectRatio) * factor;
    dst->m[5] = factor;
    dst->m[10] = (-(zFarPlane + zNearPlane)) * f_n;
    dst->m[11] = -1.0f;
    dst->m[14] = -2.0f * zFarPlane * zNearPlane * f_n;
}

void Matrix::createPerspectiveFOV(float width, float height, float zNear, float zFar, Matrix* dst)
{
    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;
    createPerspectiveOffCenter(-halfWidth, halfWidth, -halfHeight, halfHeight, zNear, zFar, dst);
}

void Matrix::createPerspectiveOffCenter(float left, float right, float bottom, float top,
                                         float zNear, float zFar, Matrix* dst)
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


void Matrix::createOrthographic(float width, float height, float zNearPlane, float zFarPlane, Matrix* dst)
{
    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;
    createOrthographicOffCenter(-halfWidth, halfWidth, -halfHeight, halfHeight, zNearPlane, zFarPlane, dst);
}

void Matrix::createOrthographicOffCenter(float left, float right, float bottom, float top,
                                         float zNearPlane, float zFarPlane, Matrix* dst)
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

void Matrix::createScale(const Vector3& scale, Matrix* dst)
{
    assert(dst);

    memcpy(dst, MATRIX_IDENTITY, MATRIX_SIZE);

    dst->m[0] = scale.x;
    dst->m[5] = scale.y;
    dst->m[10] = scale.z;
}

void Matrix::createScale(float xScale, float yScale, float zScale, Matrix* dst)
{
    assert(dst);

    memcpy(dst, MATRIX_IDENTITY, MATRIX_SIZE);

    dst->m[0] = xScale;
    dst->m[5] = yScale;
    dst->m[10] = zScale;
}


void Matrix::createRotation(const Quaternion& q, Matrix* dst)
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

void Matrix::createRotation(const Vector3& axis, float angle, Matrix* dst, bool approximate)
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
        MathUtility::getInstance().sincos(angle, &s, &c);
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

void Matrix::createRotationX(float angle, Matrix* dst)
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

void Matrix::createRotationY(float angle, Matrix* dst)
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

void Matrix::createRotationZ(float angle, Matrix* dst)
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

void Matrix::createTranslation(const Vector3& translation, Matrix* dst)
{
    assert(dst);

    memcpy(dst, MATRIX_IDENTITY, MATRIX_SIZE);

    dst->m[12] = translation.x;
    dst->m[13] = translation.y;
    dst->m[14] = translation.z;
}

void Matrix::createTranslation(float xTranslation, float yTranslation, float zTranslation, Matrix* dst)
{
    assert(dst);

    memcpy(dst, MATRIX_IDENTITY, MATRIX_SIZE);

    dst->m[12] = xTranslation;
    dst->m[13] = yTranslation;
    dst->m[14] = zTranslation;
}

void Matrix::add(float scalar)
{
    add(scalar, this);
}

void Matrix::add(float scalar, Matrix* dst)
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

void Matrix::add(const Matrix& m1)
{
    add(*this, m1, this);
}

void Matrix::add(const Matrix& m1, const Matrix& m2, Matrix* dst)
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

bool Matrix::decompose(Vector3* scale, Quaternion* rotation, Vector3* translation) const
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
    Vector3 xaxis(m[0], m[1], m[2]);
    float scaleX = xaxis.length();

    Vector3 yaxis(m[4], m[5], m[6]);
    float scaleY = yaxis.length();

    Vector3 zaxis(m[8], m[9], m[10]);
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

float Matrix::determinant() const
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

void Matrix::getScale(Vector3* scale) const
{
    decompose(scale, NULL, NULL);
}

bool Matrix::getRotation(Quaternion* rotation) const
{
    return decompose(NULL, rotation, NULL);
}

void Matrix::getPosition(Vector3* translation) const
{
    decompose(NULL, NULL, translation);
}

void Matrix::getUpVector(Vector3* dst) const
{
    assert(dst);

    //dst->x = m[8];
    //dst->y = m[9];
    //dst->z = m[10];

        dst->x = m[4];
    dst->y = m[5];
    dst->z = m[6];
}


void Matrix::getRightVector(Vector3* dst) const
{
    assert(dst);

    dst->x = m[0];
    dst->y = m[1];
    dst->z = m[2];
}

void Matrix::getForwardVector(Vector3* dst) const
{
    assert(dst);

    //dst->x = -m[4];
    //dst->y = -m[5];
    //dst->z = -m[6];

    dst->x = -m[8];
    dst->y = -m[9];
    dst->z = -m[10];
}


bool Matrix::invert()
{
    return invert(this);
}

bool Matrix::invert(Matrix* dst) const
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
    Matrix inverse;
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

bool Matrix::isIdentity() const
{
    return (memcmp(m, MATRIX_IDENTITY, MATRIX_SIZE) == 0);
}

void Matrix::multiply(float scalar)
{
    multiply(scalar, this);
}

void Matrix::multiply(float scalar, Matrix* dst) const
{
    multiply(*this, scalar, dst);
}

void Matrix::multiply(const Matrix& m, float scalar, Matrix* dst)
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
    

void Matrix::multiply(const Matrix& m1)
{
    multiply(*this, m1, this);
}

void Matrix::multiply(const Matrix& m1, const Matrix& m2, Matrix* dst)
{
    //assert(dst);

#if defined(__ARM_NEON__) && !defined(__arm64__)
    
    // It is possible to skip the memcpy() since "out" does not overwrite p1 or p2.
    // otherwise a temp must be needed.
    
    // Invert column-order with row-order
    NEON_Matrix4Mul( &m2.m[0], &m1.m[0], &dst->m[0] );
    
#else

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
#endif
    
}

void Matrix::negate()
{
    negate(this);
}

void Matrix::negate(Matrix* dst) const
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

void Matrix::rotate(const Quaternion& q)
{
    rotate(q, this);
}

void Matrix::rotate(const Quaternion& q, Matrix* dst) const
{
    Matrix r;
    createRotation(q, &r);
    multiply(*this, r, dst);
}

void Matrix::rotate(const Vector3& axis, float angle)
{
    rotate(axis, angle, this);
}

void Matrix::rotate(const Vector3& axis, float angle, Matrix* dst) const
{
    Matrix r;
    createRotation(axis, angle, &r);
    multiply(*this, r, dst);
}

void Matrix::rotateX(float angle)
{
    rotateX(angle, this);
}

void Matrix::rotateX(float angle, Matrix* dst) const
{
    Matrix r;
    createRotationX(angle, &r);
    multiply(*this, r, dst);
}

void Matrix::rotateY(float angle)
{
    rotateY(angle, this);
}

void Matrix::rotateY(float angle, Matrix* dst) const
{
    Matrix r;
    createRotationY(angle, &r);
    multiply(*this, r, dst);
}

void Matrix::rotateZ(float angle)
{
    rotateZ(angle, this);
}

void Matrix::rotateZ(float angle, Matrix* dst) const
{
    assert(dst);

#if defined(__ARM_NEON__) && !defined(__arm64__) 
     float d[2] {
            cosf(angle),
            sinf(angle)
        };
    NEON_Matrix4Copy(m, dst->m);
    NEON_Matrix4RotateZ(dst->m, d);  
#else
    Matrix r;
    createRotationZ(angle, &r);
    multiply(*this, r, dst);
#endif
}

void Matrix::scale(float value)
{
    scale(value, this);
}

void Matrix::scale(float value, Matrix* dst) const
{
    scale(value, value, value, dst);
}

void Matrix::scale(float xScale, float yScale, float zScale)
{
    scale(xScale, yScale, zScale, this);
}

void Matrix::setScale(float xScale,float yScale,float zScale)
{    
    this->m[0] = xScale;
    this->m[5] = yScale;
    this->m[10] = zScale;
}

void Matrix::scale(float xScale, float yScale, float zScale, Matrix* dst) const
{
    assert(dst);

    Matrix s;
    createScale(xScale, yScale, zScale, &s);
    multiply(*this, s, dst);
}

void Matrix::scale(const Vector3& s)
{
    scale(s.x, s.y, s.z, this);
}

void Matrix::scale(const Vector3& s, Matrix* dst) const
{
    scale(s.x, s.y, s.z, dst);
}

void Matrix::set(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44)
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

void Matrix::set(const float* m1)
{
#if defined(__ARM_NEON__) && !defined(__arm64__)
    NEON_Matrix4Copy(m1, m);
#else
    memcpy(this->m, m1, MATRIX_SIZE);
#endif
}

void Matrix::set(const Matrix& m1)
{
#if defined(__ARM_NEON__) && !defined(__arm64__)
    NEON_Matrix4Copy(m1.m, m);
#else
    memcpy(this->m, m1.m, MATRIX_SIZE);
#endif
}

void Matrix::setCol(int idx, const Vector3& col)
{
    if (idx > 4)
        return;
    idx *= 4;
    m[idx++] = col.x;
    m[idx++] = col.y;
    m[idx] = col.z;
}

Vector3 Matrix::getCol(int idx) const
{
    if (idx > 4)
        return Vector3::zero();
    static Vector3 col;
    idx *= 4;
    col.set(m[idx], m[idx+1], m[idx+2]);
    return col;
}

void Matrix::getCol(int idx, Vector3& col) const
{
    if (idx > 4)
        return;
    idx *= 4;
    col.set(m[idx], m[idx+1], m[idx+2]);
}

void Matrix::setIdentity()
{
    memcpy(m, MATRIX_IDENTITY, MATRIX_SIZE);
}

void Matrix::setZero()
{
    memset(m, 0, MATRIX_SIZE);
}

void Matrix::subtract(const Matrix& m1)
{
    subtract(*this, m1, this);
}

void Matrix::subtract(const Matrix& m1, const Matrix& m2, Matrix* dst)
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

void Matrix::transformPoint(Vector3* point) const
{
    transformVector(point->x, point->y, point->z, 1.0f, point);
}

void Matrix::transformPoint(const Vector3& point, Vector3* dst) const
{
    transformVector(point.x, point.y, point.z, 1.0f, dst);
}

void Matrix::transformVector(Vector3* vector) const
{
    transformVector(vector->x, vector->y, vector->z, vector);
}

void Matrix::transformVector(const Vector3& vector, Vector3* dst) const
{
    transformVector(vector.x, vector.y, vector.z, dst);
}

void Matrix::transformVector(float x, float y, float z, float w, Vector3* dst) const
{
#if defined(__ARM_NEON__) && !defined(__arm64__)
    float d[4];
    float v[4] {x, y, z, w};
    NEON_Matrix4Vector4Mul(m, v, d);
    dst->set(d[0], d[1], d[2]);
#else
    dst->set(
        x * m[0] + y * m[4] + z * m[8] + w * m[12],
        x * m[1] + y * m[5] + z * m[9] + w * m[13],
        x * m[2] + y * m[6] + z * m[10] + w * m[14] );
#endif
}
    
void Matrix::transformVector(float x, float y, float z, Vector3* dst) const
{
    assert(dst);
    
    dst->set(x * m[0] + y * m[4] + z * m[8],
             x * m[1] + y * m[5] + z * m[9],
             x * m[2] + y * m[6] + z * m[10]);
}

void Matrix::transformVector(Vector4* vector) const
{
    transformVector(*vector, vector);
}

void Matrix::transformVector(const Vector4& vector, Vector4* dst) const
{
    assert(dst);

    dst->set(
        vector.x * m[0] + vector.y * m[4] + vector.z * m[8] + vector.w * m[12],
        vector.x * m[1] + vector.y * m[5] + vector.z * m[9] + vector.w * m[13],
        vector.x * m[2] + vector.y * m[6] + vector.z * m[10] + vector.w * m[14],
        vector.x * m[3] + vector.y * m[7] + vector.z * m[11] + vector.w * m[15] );
}

void Matrix::translate(float x, float y, float z)
{
    translate(x, y, z, this);
}

void Matrix::translate(float x, float y, float z, Matrix* dst) const
{
    assert(dst);

#if defined(__ARM_NEON__) && !defined(__arm64__)
    float d[3] {x, y, z};
    NEON_Matrix4Copy(m, dst->m);
    NEON_Matrix4Translate(dst->m, d);
#else
    Matrix t;
    createTranslation(x, y, z, &t);
    multiply(*this, t, dst);
#endif
}

void Matrix::translate(const Vector3& t)
{
    translate(t.x, t.y, t.z, this);
}

void Matrix::translate(const Vector3& t, Matrix* dst) const
{
    translate(t.x, t.y, t.z, dst);
}

void Matrix::transpose()
{
    transpose(this);
}

void Matrix::transpose(Matrix* dst) const
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
    
Matrix& Matrix::invertOrthMat()
{
    Matrix src = *this;
    Matrix::invertOrthMat(src, *this);
    return *this;
}
    
void Matrix::invertOrthMat(const Matrix& mat, Matrix& invMat)
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

NS_CC_END
