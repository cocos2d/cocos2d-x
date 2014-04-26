#include "Vector2.h"
#include "2d/ccMacros.h"
#include "MathUtil.h"

NS_CC_MATH_BEGIN

// returns true if segment A-B intersects with segment C-D. S->E is the ovderlap part
bool isOneDimensionSegmentOverlap(float A, float B, float C, float D, float *S, float * E)
{
    float ABmin = MIN(A, B);
    float ABmax = MAX(A, B);
    float CDmin = MIN(C, D);
    float CDmax = MAX(C, D);
    
    if (ABmax < CDmin || CDmax < ABmin)
    {
        // ABmin->ABmax->CDmin->CDmax or CDmin->CDmax->ABmin->ABmax
        return false;
    }
    else
    {
        if (ABmin >= CDmin && ABmin <= CDmax)
        {
            // CDmin->ABmin->CDmax->ABmax or CDmin->ABmin->ABmax->CDmax
            if (S != nullptr) *S = ABmin;
            if (E != nullptr) *E = CDmax < ABmax ? CDmax : ABmax;
        }
        else if (ABmax >= CDmin && ABmax <= CDmax)
        {
            // ABmin->CDmin->ABmax->CDmax
            if (S != nullptr) *S = CDmin;
            if (E != nullptr) *E = ABmax;
        }
        else
        {
            // ABmin->CDmin->CDmax->ABmax
            if (S != nullptr) *S = CDmin;
            if (E != nullptr) *E = CDmax;
        }
        return true;
    }
}

// cross procuct of 2 vector. A->B X C->D
float crossProduct2Vector(const Vector2& A, const Vector2& B, const Vector2& C, const Vector2& D)
{
    return (D.y - C.y) * (B.x - A.x) - (D.x - C.x) * (B.y - A.y);
}

Vector2::Vector2()
    : x(0.0f), y(0.0f)
{
}

Vector2::Vector2(float xx, float yy)
    : x(xx), y(yy)
{
}

Vector2::Vector2(const float* array)
{
    set(array);
}

Vector2::Vector2(const Vector2& p1, const Vector2& p2)
{
    set(p1, p2);
}

Vector2::Vector2(const Vector2& copy)
{
    set(copy);
}

Vector2::~Vector2()
{
}

const Vector2& Vector2::zero()
{
    static Vector2 value(0.0f, 0.0f);
    return value;
}

const Vector2& Vector2::one()
{
    static Vector2 value(1.0f, 1.0f);
    return value;
}

const Vector2& Vector2::unitX()
{
    static Vector2 value(1.0f, 0.0f);
    return value;
}

const Vector2& Vector2::unitY()
{
    static Vector2 value(0.0f, 1.0f);
    return value;
}

bool Vector2::isZero() const
{
    return x == 0.0f && y == 0.0f;
}

bool Vector2::isOne() const
{
    return x == 1.0f && y == 1.0f;
}

float Vector2::angle(const Vector2& v1, const Vector2& v2)
{
    float dz = v1.x * v2.y - v1.y * v2.x;
    return atan2f(fabsf(dz) + MATH_FLOAT_SMALL, dot(v1, v2));
}

void Vector2::add(const Vector2& v)
{
    x += v.x;
    y += v.y;
}

void Vector2::add(const Vector2& v1, const Vector2& v2, Vector2* dst)
{
    GP_ASSERT(dst);

    dst->x = v1.x + v2.x;
    dst->y = v1.y + v2.y;
}

void Vector2::clamp(const Vector2& min, const Vector2& max)
{
    GP_ASSERT(!(min.x > max.x || min.y > max.y ));

    // Clamp the x value.
    if (x < min.x)
        x = min.x;
    if (x > max.x)
        x = max.x;

    // Clamp the y value.
    if (y < min.y)
        y = min.y;
    if (y > max.y)
        y = max.y;
}

void Vector2::clamp(const Vector2& v, const Vector2& min, const Vector2& max, Vector2* dst)
{
    GP_ASSERT(dst);
    GP_ASSERT(!(min.x > max.x || min.y > max.y ));

    // Clamp the x value.
    dst->x = v.x;
    if (dst->x < min.x)
        dst->x = min.x;
    if (dst->x > max.x)
        dst->x = max.x;

    // Clamp the y value.
    dst->y = v.y;
    if (dst->y < min.y)
        dst->y = min.y;
    if (dst->y > max.y)
        dst->y = max.y;
}

float Vector2::distance(const Vector2& v) const
{
    float dx = v.x - x;
    float dy = v.y - y;

    return sqrt(dx * dx + dy * dy);
}

float Vector2::distanceSquared(const Vector2& v) const
{
    float dx = v.x - x;
    float dy = v.y - y;
    return (dx * dx + dy * dy);
}

float Vector2::dot(const Vector2& v) const
{
    return (x * v.x + y * v.y);
}

float Vector2::dot(const Vector2& v1, const Vector2& v2)
{
    return (v1.x * v2.x + v1.y * v2.y);
}

float Vector2::length() const
{
    return sqrt(x * x + y * y);
}

float Vector2::lengthSquared() const
{
    return (x * x + y * y);
}

void Vector2::negate()
{
    x = -x;
    y = -y;
}

Vector2& Vector2::normalize()
{
    normalize(this);
    return *this;
}

void Vector2::normalize(Vector2* dst) const
{
    GP_ASSERT(dst);

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

void Vector2::scale(float scalar)
{
    x *= scalar;
    y *= scalar;
}

void Vector2::scale(const Vector2& scale)
{
    x *= scale.x;
    y *= scale.y;
}

void Vector2::rotate(const Vector2& point, float angle)
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

void Vector2::set(float xx, float yy)
{
    this->x = xx;
    this->y = yy;
}

void Vector2::set(const float* array)
{
    GP_ASSERT(array);

    x = array[0];
    y = array[1];
}

void Vector2::set(const Vector2& v)
{
    this->x = v.x;
    this->y = v.y;
}

void Vector2::set(const Vector2& p1, const Vector2& p2)
{
     x = p2.x - p1.x;
     y = p2.y - p1.y;
}

void Vector2::subtract(const Vector2& v)
{
    x -= v.x;
    y -= v.y;
}

void Vector2::subtract(const Vector2& v1, const Vector2& v2, Vector2* dst)
{
    GP_ASSERT(dst);

    dst->x = v1.x - v2.x;
    dst->y = v1.y - v2.y;
}

void Vector2::smooth(const Vector2& target, float elapsedTime, float responseTime)
{
    if (elapsedTime > 0)
    {
        *this += (target - *this) * (elapsedTime / (elapsedTime + responseTime));
    }
}

void Vector2::setPoint(float xx, float yy)
{
    this->x = xx;
    this->y = yy;
}

bool Vector2::equals(const Vector2& target) const
{
    return (fabs(this->x - target.x) < FLT_EPSILON)
        && (fabs(this->y - target.y) < FLT_EPSILON);
}

bool Vector2::fuzzyEquals(const Vector2& b, float var) const
{
    if(x - var <= b.x && b.x <= x + var)
        if(y - var <= b.y && b.y <= y + var)
            return true;
    return false;
}

float Vector2::getAngle(const Vector2& other) const
{
    Vector2 a2 = normalize();
    Vector2 b2 = other.normalize();
    float angle = atan2f(a2.cross(b2), a2.dot(b2));
    if( fabs(angle) < FLT_EPSILON ) return 0.f;
    return angle;
}

Vector2 Vector2::rotateByAngle(const Vector2& pivot, float angle) const
{
    return pivot + (*this - pivot).rotate(Vector2::forAngle(angle));
}

bool Vector2::isLineIntersect(const Vector2& A, const Vector2& B,
                            const Vector2& C, const Vector2& D,
                            float *S, float *T)
{
    // FAIL: Line undefined
    if ( (A.x==B.x && A.y==B.y) || (C.x==D.x && C.y==D.y) )
    {
        return false;
    }
    
    const float denom = crossProduct2Vector(A, B, C, D);
    
    if (denom == 0)
    {
        // Lines parallel or overlap
        return false;
    }
    
    if (S != nullptr) *S = crossProduct2Vector(C, D, C, A) / denom;
    if (T != nullptr) *T = crossProduct2Vector(A, B, C, A) / denom;
    
    return true;
}

bool Vector2::isLineParallel(const Vector2& A, const Vector2& B,
                           const Vector2& C, const Vector2& D)
{
    // FAIL: Line undefined
    if ( (A.x==B.x && A.y==B.y) || (C.x==D.x && C.y==D.y) )
    {
        return false;
    }
    
    if (crossProduct2Vector(A, B, C, D) == 0)
    {
        // line overlap
        if (crossProduct2Vector(C, D, C, A) == 0 || crossProduct2Vector(A, B, C, A) == 0)
        {
            return false;
        }
        
        return true;
    }
    
    return false;
}

bool Vector2::isLineOverlap(const Vector2& A, const Vector2& B,
                            const Vector2& C, const Vector2& D)
{
    // FAIL: Line undefined
    if ( (A.x==B.x && A.y==B.y) || (C.x==D.x && C.y==D.y) )
    {
        return false;
    }
    
    if (crossProduct2Vector(A, B, C, D) == 0 &&
        (crossProduct2Vector(C, D, C, A) == 0 || crossProduct2Vector(A, B, C, A) == 0))
    {
        return true;
    }
    
    return false;
}

bool Vector2::isSegmentOverlap(const Vector2& A, const Vector2& B, const Vector2& C, const Vector2& D, Vector2* S, Vector2* E)
{
    
    if (isLineOverlap(A, B, C, D))
    {
        return isOneDimensionSegmentOverlap(A.x, B.x, C.x, D.x, &S->x, &E->x) &&
        isOneDimensionSegmentOverlap(A.y, B.y, C.y, D.y, &S->y, &E->y);
    }  
    
    return false;
}

bool Vector2::isSegmentIntersect(const Vector2& A, const Vector2& B, const Vector2& C, const Vector2& D)
{
    float S, T;
    
    if (isLineIntersect(A, B, C, D, &S, &T )&&
        (S >= 0.0f && S <= 1.0f && T >= 0.0f && T <= 1.0f))
    {
        return true;
    }
    
    return false;
}

Vector2 Vector2::getIntersectPoint(const Vector2& A, const Vector2& B, const Vector2& C, const Vector2& D)
{
    float S, T;
    
    if (isLineIntersect(A, B, C, D, &S, &T))
    {
        // Vector2 of intersection
        Vector2 P;
        P.x = A.x + S * (B.x - A.x);
        P.y = A.y + S * (B.y - A.y);
        return P;
    }
    
    return Vector2::ZERO;
}

const Vector2 Vector2::ZERO = Vector2(0.0f, 0.0f);
const Vector2 Vector2::ANCHOR_MIDDLE = Vector2(0.5f, 0.5f);
const Vector2 Vector2::ANCHOR_BOTTOM_LEFT = Vector2(0.0f, 0.0f);
const Vector2 Vector2::ANCHOR_TOP_LEFT = Vector2(0.0f, 1.0f);
const Vector2 Vector2::ANCHOR_BOTTOM_RIGHT = Vector2(1.0f, 0.0f);
const Vector2 Vector2::ANCHOR_TOP_RIGHT = Vector2(1.0f, 1.0f);
const Vector2 Vector2::ANCHOR_MIDDLE_RIGHT = Vector2(1.0f, 0.5f);
const Vector2 Vector2::ANCHOR_MIDDLE_LEFT = Vector2(0.0f, 0.5f);
const Vector2 Vector2::ANCHOR_MIDDLE_TOP = Vector2(0.5f, 1.0f);
const Vector2 Vector2::ANCHOR_MIDDLE_BOTTOM = Vector2(0.5f, 0.0f);

NS_CC_MATH_END
