#include "C3DMatrix.h"

NS_CC_BEGIN

inline const Matrix Matrix::operator+(const Matrix& m) const
{
    Matrix result(*this);
    result.add(m);
    return result;
}

inline Matrix& Matrix::operator+=(const Matrix& m)
{
    add(m);
    return *this;
}

inline const Matrix Matrix::operator-(const Matrix& m) const
{
    Matrix result(*this);
    result.subtract(m);
    return result;
}

inline Matrix& Matrix::operator-=(const Matrix& m)
{
    subtract(m);
    return *this;
}

inline const Matrix Matrix::operator-() const
{
    Matrix m(*this);
    m.negate();
    return m;
}

inline const Matrix Matrix::operator*(const Matrix& m) const
{
    Matrix result(*this);
    result.multiply(m);
    return result;
}

inline Matrix& Matrix::operator*=(const Matrix& m1)
{
    multiply(m1);
    return *this;
}

inline Vector3& operator*=(Vector3& v, const Matrix& m1)
{
    m1.transformVector(&v);
    return v;
}

inline const Vector3 operator*(const Matrix& m1, const Vector3& v)
{
    Vector3 x;
    m1.transformVector(v, &x);
    return x;
}

inline Vector4& operator*=(Vector4& v, const Matrix& m1)
{
    m1.transformVector(&v);
    return v;
}

inline const Vector4 operator*(const Matrix& m1, const Vector4& v)
{
    Vector4 x;
    m1.transformVector(v, &x);
    return x;
}

NS_CC_END
