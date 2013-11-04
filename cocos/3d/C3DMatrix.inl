#include "C3DMatrix.h"

namespace cocos3d
{

inline const C3DMatrix C3DMatrix::operator+(const C3DMatrix& m) const
{
    C3DMatrix result(*this);
    result.add(m);
    return result;
}

inline C3DMatrix& C3DMatrix::operator+=(const C3DMatrix& m)
{
    add(m);
    return *this;
}

inline const C3DMatrix C3DMatrix::operator-(const C3DMatrix& m) const
{
    C3DMatrix result(*this);
    result.subtract(m);
    return result;
}

inline C3DMatrix& C3DMatrix::operator-=(const C3DMatrix& m)
{
    subtract(m);
    return *this;
}

inline const C3DMatrix C3DMatrix::operator-() const
{
    C3DMatrix m(*this);
    m.negate();
    return m;
}

inline const C3DMatrix C3DMatrix::operator*(const C3DMatrix& m) const
{
    C3DMatrix result(*this);
    result.multiply(m);
    return result;
}

inline C3DMatrix& C3DMatrix::operator*=(const C3DMatrix& m)
{
    multiply(m);
    return *this;
}

inline C3DVector3& operator*=(C3DVector3& v, const C3DMatrix& m)
{
    m.transformVector(&v);
    return v;
}

inline const C3DVector3 operator*(const C3DMatrix& m, const C3DVector3& v)
{
    C3DVector3 x;
    m.transformVector(v, &x);
    return x;
}

inline C3DVector4& operator*=(C3DVector4& v, const C3DMatrix& m)
{
    m.transformVector(&v);
    return v;
}

inline const C3DVector4 operator*(const C3DMatrix& m, const C3DVector4& v)
{
    C3DVector4 x;
    m.transformVector(v, &x);
    return x;
}

}
