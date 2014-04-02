#include "Vector2.h"

namespace gameplay
{

inline const Vector2 Vector2::operator+(const Vector2& v) const
{
    Vector2 result(*this);
    result.add(v);
    return result;
}

inline Vector2& Vector2::operator+=(const Vector2& v)
{
    add(v);
    return *this;
}

inline const Vector2 Vector2::operator-(const Vector2& v) const
{
    Vector2 result(*this);
    result.subtract(v);
    return result;
}

inline Vector2& Vector2::operator-=(const Vector2& v)
{
    subtract(v);
    return *this;
}

inline const Vector2 Vector2::operator-() const
{
    Vector2 result(*this);
    result.negate();
    return result;
}

inline const Vector2 Vector2::operator*(float x) const
{
    Vector2 result(*this);
    result.scale(x);
    return result;
}

inline Vector2& Vector2::operator*=(float x)
{
    scale(x);
    return *this;
}

inline const Vector2 Vector2::operator/(const float x) const
{
    return Vector2(this->x / x, this->y / x);
}

inline bool Vector2::operator<(const Vector2& v) const
{
    if (x == v.x)
    {
        return y < v.y;
    }
    return x < v.x;
}

inline bool Vector2::operator==(const Vector2& v) const
{
    return x==v.x && y==v.y;
}

inline bool Vector2::operator!=(const Vector2& v) const
{
    return x!=v.x || y!=v.y;
}

inline const Vector2 operator*(float x, const Vector2& v)
{
    Vector2 result(v);
    result.scale(x);
    return result;
}

}
