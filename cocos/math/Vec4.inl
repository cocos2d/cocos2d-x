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

#include "math/Mat4.h"
#include "math/Vec4.h"

NS_CC_MATH_BEGIN

inline Vec4 Vec4::operator+(const Vec4& v) const
{
    Vec4 result(*this);
    result.add(v);
    return result;
}

inline Vec4& Vec4::operator+=(const Vec4& v)
{
    add(v);
    return *this;
}

inline Vec4 Vec4::operator-(const Vec4& v) const
{
    Vec4 result(*this);
    result.subtract(v);
    return result;
}

inline Vec4& Vec4::operator-=(const Vec4& v)
{
    subtract(v);
    return *this;
}

inline Vec4 Vec4::operator-() const
{
    Vec4 result(*this);
    result.negate();
    return result;
}

inline Vec4 Vec4::operator*(float s) const
{
    Vec4 result(*this);
    result.scale(s);
    return result;
}

inline Vec4& Vec4::operator*=(float s)
{
    scale(s);
    return *this;
}

inline Vec4 Vec4::operator/(const float s) const
{
    return Vec4(this->x / s, this->y / s, this->z / s, this->w / s);
}

inline bool Vec4::operator<(const Vec4& v) const
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

inline bool Vec4::operator==(const Vec4& v) const
{
    return x==v.x && y==v.y && z==v.z && w==v.w;
}

inline bool Vec4::operator!=(const Vec4& v) const
{
    return x!=v.x || y!=v.y || z!=v.z || w!=v.w;
}

inline Vec4 operator*(float x, const Vec4& v)
{
    Vec4 result(v);
    result.scale(x);
    return result;
}

NS_CC_MATH_END
