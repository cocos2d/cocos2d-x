#include "C3DVector2.h"

namespace cocos3d
{

inline const C3DVector2 C3DVector2::operator+(const C3DVector2& v) const
{
    C3DVector2 result(*this);
    result.add(v);
    return result;
}

inline C3DVector2& C3DVector2::operator+=(const C3DVector2& v)
{
    add(v);
    return *this;
}

inline const C3DVector2 C3DVector2::operator-(const C3DVector2& v) const
{
    C3DVector2 result(*this);
    result.subtract(v);
    return result;
}

inline C3DVector2& C3DVector2::operator-=(const C3DVector2& v)
{
    subtract(v);
    return *this;
}

inline const C3DVector2 C3DVector2::operator-() const
{
    C3DVector2 result(*this);
    result.negate();
    return result;
}

inline const C3DVector2 C3DVector2::operator*(float x) const
{
    C3DVector2 result(*this);
    result.scale(x);
    return result;
}

inline C3DVector2& C3DVector2::operator*=(float x)
{
    scale(x);
    return *this;
}

inline bool C3DVector2::operator<(const C3DVector2& v) const
{
    if (x == v.x)
    {
        return y < v.y;
    }
    return x < v.x;
}

inline bool C3DVector2::operator==(const C3DVector2& v) const
{
    return x==v.x && y==v.y;
}

inline bool C3DVector2::operator!=(const C3DVector2& v) const
{
    return x!=v.x || y!=v.y;
}

inline const C3DVector2 operator*(float x, const C3DVector2& v)
{
    C3DVector2 result(v);
    result.scale(x);
    return result;
}

}
