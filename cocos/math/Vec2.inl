/**
 Copyright 2013 BlackBerry Inc.

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.

 Original file from GamePlay3D: http://gameplay3d.org

 This file was modified to fit the cocos2d-x project
 */

#include "math/Vec2.h"

NS_CC_MATH_BEGIN

inline Vec2::Vec2()
: x(0.0f), y(0.0f)
{
}

inline Vec2::Vec2(float xx, float yy)
: x(xx), y(yy)
{
}

inline Vec2::Vec2(const float* array)
{
    set(array);
}

inline Vec2::Vec2(const Vec2& p1, const Vec2& p2)
{
    set(p1, p2);
}

inline Vec2::Vec2(const Vec2& copy)
{
    set(copy);
}

inline Vec2::~Vec2()
{
}

inline bool Vec2::isZero() const
{
    return x == 0.0f && y == 0.0f;
}

bool Vec2::isOne() const
{
    return x == 1.0f && y == 1.0f;
}

inline void Vec2::add(const Vec2& v)
{
    x += v.x;
    y += v.y;
}

inline float Vec2::distanceSquared(const Vec2& v) const
{
    float dx = v.x - x;
    float dy = v.y - y;
    return (dx * dx + dy * dy);
}

inline float Vec2::dot(const Vec2& v) const
{
    return (x * v.x + y * v.y);
}

inline float Vec2::lengthSquared() const
{
    return (x * x + y * y);
}

inline void Vec2::negate()
{
    x = -x;
    y = -y;
}

inline void Vec2::scale(float scalar)
{
    x *= scalar;
    y *= scalar;
}

inline void Vec2::scale(const Vec2& scale)
{
    x *= scale.x;
    y *= scale.y;
}

inline void Vec2::set(float xx, float yy)
{
    this->x = xx;
    this->y = yy;
}

inline void Vec2::set(const Vec2& v)
{
    this->x = v.x;
    this->y = v.y;
}

inline void Vec2::set(const Vec2& p1, const Vec2& p2)
{
    x = p2.x - p1.x;
    y = p2.y - p1.y;
}

void Vec2::setZero()
{
    x = y = 0.0f;
}

inline void Vec2::subtract(const Vec2& v)
{
    x -= v.x;
    y -= v.y;
}

inline void Vec2::smooth(const Vec2& target, float elapsedTime, float responseTime)
{
    if (elapsedTime > 0)
    {
        *this += (target - *this) * (elapsedTime / (elapsedTime + responseTime));
    }
}

inline const Vec2 Vec2::operator+(const Vec2& v) const
{
    Vec2 result(*this);
    result.add(v);
    return result;
}

inline Vec2& Vec2::operator+=(const Vec2& v)
{
    add(v);
    return *this;
}

inline const Vec2 Vec2::operator-(const Vec2& v) const
{
    Vec2 result(*this);
    result.subtract(v);
    return result;
}

inline Vec2& Vec2::operator-=(const Vec2& v)
{
    subtract(v);
    return *this;
}

inline const Vec2 Vec2::operator-() const
{
    Vec2 result(*this);
    result.negate();
    return result;
}

inline const Vec2 Vec2::operator*(float s) const
{
    Vec2 result(*this);
    result.scale(s);
    return result;
}

inline Vec2& Vec2::operator*=(float s)
{
    scale(s);
    return *this;
}

inline const Vec2 Vec2::operator/(const float s) const
{
    return Vec2(this->x / s, this->y / s);
}

inline bool Vec2::operator<(const Vec2& v) const
{
    if (x == v.x)
    {
        return y < v.y;
    }
    return x < v.x;
}

inline bool Vec2::operator>(const Vec2& v) const
{
    if (x == v.x)
    {
        return y > v.y;
    }
    return x > v.x;
}

inline bool Vec2::operator==(const Vec2& v) const
{
    return x==v.x && y==v.y;
}

inline bool Vec2::operator!=(const Vec2& v) const
{
    return x!=v.x || y!=v.y;
}

inline const Vec2 operator*(float x, const Vec2& v)
{
    Vec2 result(v);
    result.scale(x);
    return result;
}

void Vec2::setPoint(float xx, float yy)
{
    this->x = xx;
    this->y = yy;
}

NS_CC_MATH_END
