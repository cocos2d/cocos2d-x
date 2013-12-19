#include "Base.h"
#include "C3DVector3.h"

namespace cocos3d
{

C3DVector3::C3DVector3()
    : x(0.0f), y(0.0f), z(0.0f)
{
}

C3DVector3::C3DVector3(float x, float y, float z)
{
    set(x, y, z);
}

C3DVector3::C3DVector3(const float* array)
{
    if (array)
        set(array);
    else
        set(0, 0, 0);
}

C3DVector3::C3DVector3(const C3DVector3& p1, const C3DVector3& p2)
{
    set(p1, p2);
}

C3DVector3::C3DVector3(const C3DVector3& copy)
{
    set(copy);
}

C3DVector3 C3DVector3::fromColor(unsigned int color)
{
    float components[3];
    int componentIndex = 0;
    for (int i = 2; i >= 0; --i)
    {
        int component = (color >> i*8) & 0x0000ff;

        components[componentIndex++] = static_cast<float>(component) / 255.0f;
    }

    C3DVector3 value(components);
    return value;
}

C3DVector3::~C3DVector3()
{
}

const C3DVector3& C3DVector3::zero()
{
    static C3DVector3 value(0.0f, 0.0f, 0.0f);
    return value;
}

const C3DVector3& C3DVector3::one()
{
    static C3DVector3 value(1.0f, 1.0f, 1.0f);
    return value;
}

const C3DVector3& C3DVector3::unitX()
{
    static C3DVector3 value(1.0f, 0.0f, 0.0f);
    return value;
}

const C3DVector3& C3DVector3::unitY()
{
    static C3DVector3 value(0.0f, 1.0f, 0.0f);
    return value;
}

const C3DVector3& C3DVector3::unitZ()
{
    static C3DVector3 value(0.0f, 0.0f, 1.0f);
    return value;
}

bool C3DVector3::isZero() const
{
    return x == 0.0f && y == 0.0f && z == 0.0f;
}

bool C3DVector3::isOne() const
{
    return x == 1.0f && y == 1.0f && z == 1.0f;
}

float C3DVector3::angle(const C3DVector3& v1, const C3DVector3& v2)
{
    float dx = v1.y * v2.z - v1.z * v2.y;
    float dy = v1.z * v2.x - v1.x * v2.z;
    float dz = v1.x * v2.y - v1.y * v2.x;

    return atan2f(sqrt(dx * dx + dy * dy + dz * dz) + MATH_FLOAT_SMALL, dot(v1, v2));
}

void C3DVector3::add(const C3DVector3& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
}

void C3DVector3::add(const C3DVector3& v1, const C3DVector3& v2, C3DVector3* dst)
{
    assert(dst);

    dst->x = v1.x + v2.x;
    dst->y = v1.y + v2.y;
    dst->z = v1.z + v2.z;
}

void C3DVector3::clamp(const C3DVector3& min, const C3DVector3& max)
{
    assert(!( min.x > max.x || min.y > max.y || min.z > max.z));

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
}

void C3DVector3::clamp(const C3DVector3& v, const C3DVector3& min, const C3DVector3& max, C3DVector3* dst)
{
    assert(dst);
    assert(!( min.x > max.x || min.y > max.y || min.z > max.z));

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
}

void C3DVector3::cross(const C3DVector3& v)
{
    float tx = (y * v.z) - (z * v.y);
    float ty = (z * v.x) - (x * v.z);
    float tz = (x * v.y) - (y * v.x);
    x = tx;
    y = ty;
    z = tz;
}

void C3DVector3::cross(const C3DVector3& v1, const C3DVector3& v2, C3DVector3* dst)
{
    //assert(dst);

    dst->x = (v1.y * v2.z) - (v1.z * v2.y);
    dst->y = (v1.z * v2.x) - (v1.x * v2.z);
    dst->z = (v1.x * v2.y) - (v1.y * v2.x);
    
}

float C3DVector3::distance(const C3DVector3& v) const
{
    float dx = v.x - x;
    float dy = v.y - y;
    float dz = v.z - z;

    return sqrt(dx * dx + dy * dy + dz * dz);
}

float C3DVector3::distanceSquared(const C3DVector3& v) const
{
    float dx = v.x - x;
    float dy = v.y - y;
    float dz = v.z - z;

    return (dx * dx + dy * dy + dz * dz);
}

float C3DVector3::dot(const C3DVector3& v) const
{
    return (x * v.x + y * v.y + z * v.z);
}

float C3DVector3::dot(const C3DVector3& v1, const C3DVector3& v2)
{
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float C3DVector3::length() const
{
    return sqrt(x * x + y * y + z * z);
}

float C3DVector3::lengthSquared() const
{
    return (x * x + y * y + z * z);
}

void C3DVector3::negate()
{
    x = -x;
    y = -y;
    z = -z;
}

C3DVector3& C3DVector3::normalize()
{
    normalize(this);
    return *this;
}

void C3DVector3::normalize(C3DVector3* dst) const
{
    assert(dst);

    if (dst != this)
    {
        dst->x = x;
        dst->y = y;
        dst->z = z;
    }

    float n = x * x + y * y + z * z;
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
}

void C3DVector3::scale(float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
}

void C3DVector3::set(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void C3DVector3::set(const float* array)
{
    assert(array);

    x = array[0];
    y = array[1];
    z = array[2];
}

void C3DVector3::set(const C3DVector3& v)
{
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
}

void C3DVector3::set(const C3DVector3& p1, const C3DVector3& p2)
{
    x = p2.x - p1.x;
    y = p2.y - p1.y;
    z = p2.z - p1.z;
}

void C3DVector3::subtract(const C3DVector3& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
}

void C3DVector3::subtract(const C3DVector3& v1, const C3DVector3& v2, C3DVector3* dst)
{
    assert(dst);

    dst->x = v1.x - v2.x;
    dst->y = v1.y - v2.y;
    dst->z = v1.z - v2.z;
}

}
