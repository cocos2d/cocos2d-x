#include "Base.h"
#include "C3DVector2.h"

namespace cocos3d
{

C3DVector2::C3DVector2()
    : x(0.0f), y(0.0f)
{
}

C3DVector2::C3DVector2(float x, float y)
{
    set(x, y);
}

C3DVector2::C3DVector2(const float* array)
{
    if (array)
        set(array);
    else
        set(0, 0);
}

C3DVector2::C3DVector2(const C3DVector2& p1, const C3DVector2& p2)
{
    set(p1, p2);
}

C3DVector2::C3DVector2(const C3DVector2& copy)
{
    set(copy);
}

C3DVector2::~C3DVector2()
{
}

const C3DVector2& C3DVector2::zero()
{
    static C3DVector2 value(0.0f, 0.0f);
    return value;
}

const C3DVector2& C3DVector2::one()
{
    static C3DVector2 value(1.0f, 1.0f);
    return value;
}

const C3DVector2& C3DVector2::unitX()
{
    static C3DVector2 value(1.0f, 0.0f);
    return value;
}

const C3DVector2& C3DVector2::unitY()
{
    static C3DVector2 value(0.0f, 1.0f);
    return value;
}

bool C3DVector2::isZero() const
{
    return x == 0.0f && y == 0.0f;
}

bool C3DVector2::isOne() const
{
    return x == 1.0f && y == 1.0f;
}

float C3DVector2::angle(const C3DVector2& v1, const C3DVector2& v2)
{
    float dz = v1.x * v2.y - v1.y * v2.x;
    return atan2f(fabsf(dz) + MATH_FLOAT_SMALL, dot(v1, v2));
}

void C3DVector2::add(const C3DVector2& v)
{
    x += v.x;
    y += v.y;
}

void C3DVector2::add(const C3DVector2& v1, const C3DVector2& v2, C3DVector2* dst)
{
    assert(dst);

    dst->x = v1.x + v2.x;
    dst->y = v1.y + v2.y;
}

void C3DVector2::clamp(const C3DVector2& min, const C3DVector2& max)
{
    assert(!( min.x > max.x || min.y > max.y ));

    // Clamp the x value.
    if ( x < min.x )
        x = min.x;
    if ( x > max.x )
        x = max.x;

    // Clamp the y value.
    if ( y < min.y )
        y = min.y;
    if ( y > max.y )
        y = max.y;
}

void C3DVector2::clamp(const C3DVector2& v, const C3DVector2& min, const C3DVector2& max, C3DVector2* dst)
{
    assert(dst);
    assert(!( min.x > max.x || min.y > max.y ));

    // Clamp the x value.
    dst->x = v.x;
    if ( dst->x < min.x )
        dst->x = min.x;
    if ( dst->x > max.x )
        dst->x = max.x;

    // Clamp the y value.
    dst->y = v.y;
    if ( dst->y < min.y )
        dst->y = min.y;
    if ( dst->y > max.y )
        dst->y = max.y;
}

float C3DVector2::distance(const C3DVector2& v) const
{
    float dx = v.x - x;
    float dy = v.y - y;

    return sqrt(dx * dx + dy * dy);
}

float C3DVector2::distanceSquared(const C3DVector2& v) const
{
    float dx = v.x - x;
    float dy = v.y - y;
    return (dx * dx + dy * dy);
}

float C3DVector2::dot(const C3DVector2& v) const
{
    return (x * v.x + y * v.y);
}

float C3DVector2::dot(const C3DVector2& v1, const C3DVector2& v2)
{
    return (v1.x * v2.x + v1.y * v2.y);
}

float C3DVector2::length() const
{
    return sqrt(x * x + y * y);
}

float C3DVector2::lengthSquared() const
{
    return (x * x + y * y);
}

void C3DVector2::negate()
{
    x = -x;
    y = -y;
}

C3DVector2& C3DVector2::normalize()
{
    normalize(this);
    return *this;
}

void C3DVector2::normalize(C3DVector2* dst)
{
    assert(dst);

    if (dst != this)
    {
        dst->x = x;
        dst->y = y;
    }

    float n = x * x + y * y;
    // Already normalized.
    if (n == 1.0f)
        return;

    n = sqrt(n);
    // Too close to zero.
    if (n < MATH_TOLERANCE)
        return;

    n = 1.0f / n;
    dst->x *= n;
    dst->y *= n;
}

void C3DVector2::scale(float scalar)
{
    x *= scalar;
    y *= scalar;
}

void C3DVector2::scale(const C3DVector2& scale)
{
    x *= scale.x;
    y *= scale.y;
}

void C3DVector2::rotate(const C3DVector2& point, float angle)
{
    double sinAngle = sin(angle);
    double cosAngle = cos(angle);

    if (point.isZero())
    {
        float tempX = x * cosAngle - y * sinAngle;
        y = y * cosAngle + x * sinAngle;
        x = tempX;
    }
    else
    {
        float tempX = x - point.x;
        float tempY = y - point.y;

        x = tempX * cosAngle - tempY * sinAngle + point.x;
        y = tempY * cosAngle + tempX * sinAngle + point.y;
    }
}

void C3DVector2::set(float x, float y)
{
    this->x = x;
    this->y = y;
}

void C3DVector2::set(const float* array)
{
    assert(array);

    x = array[0];
    y = array[1];
}

void C3DVector2::set(const C3DVector2& v)
{
    this->x = v.x;
    this->y = v.y;
}

void C3DVector2::set(const C3DVector2& p1, const C3DVector2& p2)
{
     x = p2.x - p1.x;
     y = p2.y - p1.y;
}

void C3DVector2::subtract(const C3DVector2& v)
{
    x -= v.x;
    y -= v.y;
}

void C3DVector2::subtract(const C3DVector2& v1, const C3DVector2& v2, C3DVector2* dst)
{
    assert(dst);

    dst->x = v1.x - v2.x;
    dst->y = v1.y - v2.y;
}

}
