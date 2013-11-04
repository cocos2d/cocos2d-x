#include "Base.h"
#include "C3DVector4.h"

namespace cocos3d
{

C3DVector4::C3DVector4()
    : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
{
}

C3DVector4::C3DVector4(float x, float y, float z, float w)
{
    set(x, y, z, w);
}

C3DVector4::C3DVector4(const float* array)
{
    if (array)
        set(array);
    else
        set(0, 0, 0, 0);
}

C3DVector4::C3DVector4(const C3DVector4& p1, const C3DVector4& p2)
{
    set(p1, p2);
}

C3DVector4::C3DVector4(const C3DVector4& copy)
{
    set(copy);
}

C3DVector4 C3DVector4::fromColor(unsigned int color)
{
    float components[4];
    int componentIndex = 0;
    for (int i = 3; i >= 0; --i)
    {
        int component = (color >> i*8) & 0x000000ff;

        components[componentIndex++] = static_cast<float>(component) / 255.0f;
    }

    C3DVector4 value(components);
    return value;
}

C3DVector4::~C3DVector4()
{
}

const C3DVector4& C3DVector4::zero()
{
    static C3DVector4 value(0.0f, 0.0f, 0.0f, 0.0f);
    return value;
}

const C3DVector4& C3DVector4::one()
{
    static C3DVector4 value(1.0f, 1.0f, 1.0f, 1.0f);
    return value;
}

const C3DVector4& C3DVector4::unitX()
{
    static C3DVector4 value(1.0f, 0.0f, 0.0f, 0.0f);
    return value;
}

const C3DVector4& C3DVector4::unitY()
{
    static C3DVector4 value(0.0f, 1.0f, 0.0f, 0.0f);
    return value;
}

const C3DVector4& C3DVector4::unitZ()
{
    static C3DVector4 value(0.0f, 0.0f, 1.0f, 0.0f);
    return value;
}

const C3DVector4& C3DVector4::unitW()
{
    static C3DVector4 value(0.0f, 0.0f, 0.0f, 1.0f);
    return value;
}

bool C3DVector4::isZero() const
{
    return x == 0.0f && y == 0.0f && z == 0.0f && w == 0.0f;
}

bool C3DVector4::isOne() const
{
    return x == 1.0f && y == 1.0f && z == 1.0f && z == 1.0f;
}

float C3DVector4::angle(const C3DVector4& v1, const C3DVector4& v2)
{
    float dx = v1.w * v2.x - v1.x * v2.w - v1.y * v2.z + v1.z * v2.y;
    float dy = v1.w * v2.y - v1.y * v2.w - v1.z * v2.x + v1.x * v2.z;
    float dz = v1.w * v2.z - v1.z * v2.w - v1.x * v2.y + v1.y * v2.x;

    return atan2f(sqrt(dx * dx + dy * dy + dz * dz) + MATH_FLOAT_SMALL, dot(v1, v2));
}

void C3DVector4::add(const C3DVector4& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
}

void C3DVector4::add(const C3DVector4& v1, const C3DVector4& v2, C3DVector4* dst)
{
    assert(dst);

    dst->x = v1.x + v2.x;
    dst->y = v1.y + v2.y;
    dst->z = v1.z + v2.z;
    dst->w = v1.w + v2.w;
}

void C3DVector4::clamp(const C3DVector4& min, const C3DVector4& max)
{
    assert(!( min.x > max.x || min.y > max.y || min.z > max.z || min.w > max.w));

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

    // Clamp the z value.
    if ( z < min.z )
        z = min.z;
    if ( z > max.z )
        z = max.z;

    // Clamp the z value.
    if ( w < min.w )
        w = min.w;
    if ( w > max.w )
        w = max.w;
}

void C3DVector4::clamp(const C3DVector4& v, const C3DVector4& min, const C3DVector4& max, C3DVector4* dst)
{
    assert(dst);
    assert(!( min.x > max.x || min.y > max.y || min.z > max.z || min.w > max.w));

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

    // Clamp the z value.
    dst->z = v.z;
    if ( dst->z < min.z )
        dst->z = min.z;
    if ( dst->z > max.z )
        dst->z = max.z;

    // Clamp the w value.
    dst->w = v.w;
    if ( dst->w < min.w )
        dst->w = min.w;
    if ( dst->w > max.w )
        dst->w = max.w;
}

float C3DVector4::distance(const C3DVector4& v) const
{
    float dx = v.x - x;
    float dy = v.y - y;
    float dz = v.z - z;
    float dw = v.w - w;

    return sqrt(dx * dx + dy * dy + dz * dz + dw * dw);
}

float C3DVector4::distanceSquared(const C3DVector4& v) const
{
    float dx = v.x - x;
    float dy = v.y - y;
    float dz = v.z - z;
    float dw = v.w - w;

    return (dx * dx + dy * dy + dz * dz + dw * dw);
}

float C3DVector4::dot(const C3DVector4& v) const
{
    return (x * v.x + y * v.y + z * v.z + w * v.w);
}

float C3DVector4::dot(const C3DVector4& v1, const C3DVector4& v2)
{
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
}

float C3DVector4::length() const
{
    return sqrt(x * x + y * y + z * z + w * w);
}


float C3DVector4::lengthSquared() const
{
    return (x * x + y * y + z * z + w * w);
}

void C3DVector4::negate()
{
    x = -x;
    y = -y;
    z = -z;
    w = -w;
}

C3DVector4& C3DVector4::normalize()
{
    normalize(this);
    return *this;
}

void C3DVector4::normalize(C3DVector4* dst)
{
    assert(dst);

    if (dst != this)
    {
        dst->x = x;
        dst->y = y;
        dst->z = z;
        dst->w = w;
    }

    float n = x * x + y * y + z * z + w * w;
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
    dst->z *= n;
    dst->w *= n;
}

void C3DVector4::scale(float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
}

void C3DVector4::set(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

void C3DVector4::set(const float* array)
{
    assert(array);

    x = array[0];
    y = array[1];
    z = array[2];
    w = array[3];
}

void C3DVector4::set(const C3DVector4& v)
{
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    this->w = v.w;
}

void C3DVector4::set(const C3DVector4& p1, const C3DVector4& p2)
{
    x = p2.x - p1.x;
    y = p2.y - p1.y;
    z = p2.z - p1.z;
    w = p2.w - p1.w;
}

void C3DVector4::subtract(const C3DVector4& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
}

void C3DVector4::subtract(const C3DVector4& v1, const C3DVector4& v2, C3DVector4* dst)
{
    assert(dst);

    dst->x = v1.x - v2.x;
    dst->y = v1.y - v2.y;
    dst->z = v1.z - v2.z;
    dst->w = v1.w - v2.w;
}


}
