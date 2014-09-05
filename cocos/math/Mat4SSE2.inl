//
//  Mat4SSE2.inl
//  cocos2d_libs
//
//  Created by sun zhuoshi on 7/17/14.
//
//

#include "math/Mat4.h"

NS_CC_MATH_BEGIN

inline const Mat4 Mat4::operator+(const Mat4& mat) const
{
    Mat4 result(*this);
    result += mat;
    return result;
}

inline Mat4& Mat4::operator+=(const Mat4& mat)
{
    m11 = _mm_add_pd(m11, mat.m11);
    m12 = _mm_add_pd(m12, mat.m12);
    
    m21 = _mm_add_pd(m21, mat.m21);
    m22 = _mm_add_pd(m22, mat.m22);
    
    m31 = _mm_add_pd(m31, mat.m31);
    m32 = _mm_add_pd(m32, mat.m32);
    
    m41 = _mm_add_pd(m41, mat.m41);
    m42 = _mm_add_pd(m42, mat.m42);
    
    return *this;
}

inline const Mat4 Mat4::operator-(const Mat4& mat) const
{
    Mat4 result(*this);
    result -= mat;
    return result;
}

inline Mat4& Mat4::operator-=(const Mat4& mat)
{
    m11 = _mm_sub_pd(m11, mat.m11);
    m12 = _mm_sub_pd(m12, mat.m12);
    
    m21 = _mm_sub_pd(m21, mat.m21);
    m22 = _mm_sub_pd(m22, mat.m22);
    
    m31 = _mm_sub_pd(m31, mat.m31);
    m32 = _mm_sub_pd(m32, mat.m32);
    
    m41 = _mm_sub_pd(m41, mat.m41);
    m42 = _mm_sub_pd(m42, mat.m42);
    
    return *this;
}

inline const Mat4 Mat4::operator-() const
{
    Mat4 mat(*this);
    mat.negate();
    return mat;
}

inline const Mat4 Mat4::operator*(const Mat4& mat) const
{
    Mat4 result(*this);
    result *= mat;
    return result;
}

inline Mat4& Mat4::operator*=(const Mat4& mat)
{
    __m128d xx1 = _mm_unpacklo_pd(mat.m11, mat.m11);  // mat.m[0],  mat.m[0],
    __m128d yy1 = _mm_unpackhi_pd(mat.m11, mat.m11);  // mat.m[1],  mat.m[1]
    __m128d zz1 = _mm_unpacklo_pd(mat.m12, mat.m12);  // mat.m[2],  mat.m[2]
    __m128d ww1 = _mm_unpackhi_pd(mat.m12, mat.m12);  // mat.m[3],  mat.m[3]
    __m128d xx2 = _mm_unpacklo_pd(mat.m21, mat.m21);  // mat.m[4],  mat.m[4]
    __m128d yy2 = _mm_unpackhi_pd(mat.m21, mat.m21);  // mat.m[5],  mat.m[5]
    __m128d zz2 = _mm_unpacklo_pd(mat.m22, mat.m22);  // mat.m[6],  mat.m[6]
    __m128d ww2 = _mm_unpackhi_pd(mat.m22, mat.m22);  // mat.m[7],  mat.m[7]
    __m128d xx3 = _mm_unpacklo_pd(mat.m31, mat.m31);  // mat.m[8],  mat.m[8]
    __m128d yy3 = _mm_unpackhi_pd(mat.m31, mat.m31);  // mat.m[9],  mat.m[9]
    __m128d zz3 = _mm_unpacklo_pd(mat.m32, mat.m32);  // mat.m[10], mat.m[10]
    __m128d ww3 = _mm_unpackhi_pd(mat.m32, mat.m32);  // mat.m[11], mat.m[11]
    __m128d xx4 = _mm_unpacklo_pd(mat.m41, mat.m41);  // mat.m[12], mat.m[12]
    __m128d yy4 = _mm_unpackhi_pd(mat.m41, mat.m41);  // mat.m[13], mat.m[13]
    __m128d zz4 = _mm_unpacklo_pd(mat.m42, mat.m42);  // mat.m[14], mat.m[14]
    __m128d ww4 = _mm_unpackhi_pd(mat.m42, mat.m42);  // mat.m[15], mat.m[15]
    
    __m128d _m11 = m11; // m[0],    m[1]
    __m128d _m12 = m12; // m[2],    m[3]
    __m128d _m21 = m21; // m[4],    m[5]
    __m128d _m22 = m22; // m[6],    m[7]
    __m128d _m31 = m31; // m[8],    m[9]
    __m128d _m32 = m32; // m[10],   m[11]
    __m128d _m41 = m41; // m[12],   m[13]
    __m128d _m42 = m42; // m[14],   m[15]
    
    m11 = _mm_add_pd(_mm_add_pd(_mm_mul_pd(_m11, xx1),          // m1[0] * mat.m[0] + m1[4] * mat.m[1] + m1[8] * mat.m[2] + m1[12] * mat.m[3]
                                _mm_mul_pd(_m21, yy1)),         // m1[1] * mat.m[0] + m1[5] * mat.m[1] + m1[9] * mat.m[2] + m1[13] * mat.m[3]
                     _mm_add_pd(_mm_mul_pd(_m31, zz1),
                                _mm_mul_pd(_m41, ww1)));
    m12 = _mm_add_pd(_mm_add_pd(_mm_mul_pd(_m12, xx1),          // m1[2] * mat.m[0] + m1[6] * mat.m[1] + m1[10]* mat.m[2] + m1[14] * mat.m[3]
                                _mm_mul_pd(_m22, yy1)),         // m1[3] * mat.m[0] + m1[7] * mat.m[1] + m1[11]* mat.m[2] + m1[15] * mat.m[3]
                     _mm_add_pd(_mm_mul_pd(_m32, zz1),
                                _mm_mul_pd(_m42, ww1)));
    m21 = _mm_add_pd(_mm_add_pd(_mm_mul_pd(_m11, xx2),          // m1[0] * mat.m[4] + m1[4] * mat.m[5] + m1[8] * mat.m[6] + m1[12] * mat.m[7]
                                _mm_mul_pd(_m21, yy2)),         // m1[1] * mat.m[4] + m1[5] * mat.m[5] + m1[9] * mat.m[6] + m1[13] * mat.m[7]
                     _mm_add_pd(_mm_mul_pd(_m31, zz2),
                                _mm_mul_pd(_m41, ww2)));
    m22 = _mm_add_pd(_mm_add_pd(_mm_mul_pd(_m12, xx2),          // m1[2] * mat.m[4] + m1[6] * mat.m[5] + m1[10] * mat.m[6] + m1[14] * mat.m[7]
                                _mm_mul_pd(_m22, yy2)),         // m1[3] * mat.m[4] + m1[7] * mat.m[5] + m1[11] * mat.m[6] + m1[15] * mat.m[7]
                     _mm_add_pd(_mm_mul_pd(_m32, zz2),
                                _mm_mul_pd(_m42, ww2)));
    m31 = _mm_add_pd(_mm_add_pd(_mm_mul_pd(_m11, xx3),          // m1[0] * mat.m[8] + m1[4] * mat.m[9] + m1[8] * mat.m[10] + m1[12] * mat.m[11]
                                _mm_mul_pd(_m21, yy3)),         // m1[1] * mat.m[8] + m1[5] * mat.m[9] + m1[9] * mat.m[10] + m1[12] * mat.m[11]
                     _mm_add_pd(_mm_mul_pd(_m31, zz3),
                                _mm_mul_pd(_m41, ww3)));
    m32 = _mm_add_pd(_mm_add_pd(_mm_mul_pd(_m12, xx3),          // m1[2] * mat.m[8] + m1[6] * mat.m[9] + m1[10] * mat.m[10] + m1[12] * mat.m[11]
                                _mm_mul_pd(_m22, yy3)),         // m1[3] * mat.m[8] + m1[7] * mat.m[9] + m1[11] * mat.m[10] + m1[12] * mat.m[11]
                     _mm_add_pd(_mm_mul_pd(_m32, zz3),
                                _mm_mul_pd(_m42, ww3)));
    m41 = _mm_add_pd(_mm_add_pd(_mm_mul_pd(_m11, xx4),          // m1[0] * mat.m[12] + m1[4] * mat.m[13] + m1[8] * mat.m[14] + m1[12] * mat.m[15]
                                _mm_mul_pd(_m21, yy4)),         // m1[1] * mat.m[12] + m1[5] * mat.m[13] + m1[9] * mat.m[14] + m1[12] * mat.m[15]
                     _mm_add_pd(_mm_mul_pd(_m31, zz4),
                                _mm_mul_pd(_m41, ww4)));
    m42 = _mm_add_pd(_mm_add_pd(_mm_mul_pd(_m12, xx4),          // m1[2] * mat.m[12] + m1[6] * mat.m[13] + m1[10] * mat.m[14] + m1[12] * mat.m[15]
                                _mm_mul_pd(_m22, yy4)),         // m1[3] * mat.m[12] + m1[6] * mat.m[13] + m1[11] * mat.m[14] + m1[12] * mat.m[15]
                     _mm_add_pd(_mm_mul_pd(_m32, zz4),
                                _mm_mul_pd(_m42, ww4)));
    return *this;
}

inline Vec3& operator*=(Vec3& v, const Mat4& m)
{
    m.transformVector(&v);
    return v;
}

inline const Vec3 operator*(const Mat4& m, const Vec3& v)
{
    Vec3 x;
    m.transformVector(v, &x);
    return x;
}

inline Vec4& operator*=(Vec4& v, const Mat4& m)
{
    __m128d vxx = _mm_unpacklo_pd(v.xy, v.xy);
    __m128d vyy = _mm_unpackhi_pd(v.xy, v.xy);
    __m128d vzz = _mm_unpacklo_pd(v.zw, v.zw);
    __m128d vww = _mm_unpackhi_pd(v.zw, v.zw);
    
    v.xy = _mm_add_pd(
        _mm_add_pd(_mm_mul_pd(vxx, m.m11), _mm_mul_pd(vyy, m.m21)),
        _mm_add_pd(_mm_mul_pd(vzz, m.m31), _mm_mul_pd(vww, m.m41))
    );
    v.zw = _mm_add_pd(
        _mm_add_pd(_mm_mul_pd(vxx, m.m12), _mm_mul_pd(vyy, m.m22)),
        _mm_add_pd(_mm_mul_pd(vzz, m.m32), _mm_mul_pd(vww, m.m42))
    );
    return v;
}

inline const Vec4 operator*(const Mat4& m, const Vec4& v)
{
    Vec4 x;
    x *= m;
    return x;
}

NS_CC_MATH_END
