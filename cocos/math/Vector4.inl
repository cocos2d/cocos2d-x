#include "Matrix.h"
#include "Vector4.h"

NS_CC_MATH_BEGIN

inline const Vector4 Vector4::operator+(const Vector4& v) const
{
    Vector4 result(*this);
    result.add(v);
    return result;
}

inline Vector4& Vector4::operator+=(const Vector4& v)
{
    add(v);
    return *this;
}

inline const Vector4 Vector4::operator-(const Vector4& v) const
{
    Vector4 result(*this);
    result.subtract(v);
    return result;
}

inline Vector4& Vector4::operator-=(const Vector4& v)
{
    subtract(v);
    return *this;
}

inline const Vector4 Vector4::operator-() const
{
    Vector4 result(*this);
    result.negate();
    return result;
}

inline const Vector4 Vector4::operator*(float s) const
{
    Vector4 result(*this);
    result.scale(s);
    return result;
}

inline Vector4& Vector4::operator*=(float s)
{
    scale(s);
    return *this;
}

inline const Vector4 Vector4::operator/(const float s) const
{
    return Vector4(this->x / s, this->y / s, this->z / s, this->w / s);
}

inline bool Vector4::operator<(const Vector4& v) const
{
    if (x == v.x)
    {
        if (y == v.y)
        {
            if (z < v.z)
            {
                if (w < v.w)
                {
                    return w < v.w;
                }
            }
            return z < v.z;
        }
        return y < v.y;
    }
    return x < v.x;
}

inline bool Vector4::operator==(const Vector4& v) const
{
    return x==v.x && y==v.y && z==v.z && w==v.w;
}

inline bool Vector4::operator!=(const Vector4& v) const
{
    return x!=v.x || y!=v.y || z!=v.z || w!=v.w;
}

inline const Vector4 operator*(float x, const Vector4& v)
{
    Vector4 result(v);
    result.scale(x);
    return result;
}

NS_CC_MATH_END
