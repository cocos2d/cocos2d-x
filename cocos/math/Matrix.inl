#include "Matrix.h"

NS_CC_MATH_BEGIN

inline const Matrix Matrix::operator+(const Matrix& mat) const
{
    Matrix result(*this);
    result.add(mat);
    return result;
}

inline Matrix& Matrix::operator+=(const Matrix& mat)
{
    add(mat);
    return *this;
}

inline const Matrix Matrix::operator-(const Matrix& mat) const
{
    Matrix result(*this);
    result.subtract(mat);
    return result;
}

inline Matrix& Matrix::operator-=(const Matrix& mat)
{
    subtract(mat);
    return *this;
}

inline const Matrix Matrix::operator-() const
{
    Matrix mat(*this);
    mat.negate();
    return mat;
}

inline const Matrix Matrix::operator*(const Matrix& mat) const
{
    Matrix result(*this);
    result.multiply(mat);
    return result;
}

inline Matrix& Matrix::operator*=(const Matrix& mat)
{
    multiply(mat);
    return *this;
}

inline Vector3& operator*=(Vector3& v, const Matrix& m)
{
    m.transformVector(&v);
    return v;
}

inline const Vector3 operator*(const Matrix& m, const Vector3& v)
{
    Vector3 x;
    m.transformVector(v, &x);
    return x;
}

inline Vector4& operator*=(Vector4& v, const Matrix& m)
{
    m.transformVector(&v);
    return v;
}

inline const Vector4 operator*(const Matrix& m, const Vector4& v)
{
    Vector4 x;
    m.transformVector(v, &x);
    return x;
}

NS_CC_MATH_END
