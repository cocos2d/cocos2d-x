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

#include "Matrix.h"

NS_CC_MATH_BEGIN

inline const Matrix Matrix::operator+(const Matrix& mat) const
{
    Matrix result(*this);
    result.add(mat);
    return result;
}

inline Matrix& Matrix::operator+=(const Matrix& mat)
{
    add(mat);
    return *this;
}

inline const Matrix Matrix::operator-(const Matrix& mat) const
{
    Matrix result(*this);
    result.subtract(mat);
    return result;
}

inline Matrix& Matrix::operator-=(const Matrix& mat)
{
    subtract(mat);
    return *this;
}

inline const Matrix Matrix::operator-() const
{
    Matrix mat(*this);
    mat.negate();
    return mat;
}

inline const Matrix Matrix::operator*(const Matrix& mat) const
{
    Matrix result(*this);
    result.multiply(mat);
    return result;
}

inline Matrix& Matrix::operator*=(const Matrix& mat)
{
    multiply(mat);
    return *this;
}

inline Vector3& operator*=(Vector3& v, const Matrix& m)
{
    m.transformVector(&v);
    return v;
}

inline const Vector3 operator*(const Matrix& m, const Vector3& v)
{
    Vector3 x;
    m.transformVector(v, &x);
    return x;
}

inline Vector4& operator*=(Vector4& v, const Matrix& m)
{
    m.transformVector(&v);
    return v;
}

inline const Vector4 operator*(const Matrix& m, const Vector4& v)
{
    Vector4 x;
    m.transformVector(v, &x);
    return x;
}

NS_CC_MATH_END
