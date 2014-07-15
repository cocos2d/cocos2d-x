//
//  MathUtilSSE.h
//  cocos2d_libs
//
//  Created by sun zhuoshi on 7/15/14.
//
//

NS_CC_MATH_BEGIN

#include <xmmintrin.h>

inline void MathUtil::addMatrix(const float* m, float scalar, float* dst)
{
    __m128 col1 = _mm_load_ps(&m[0]);
    __m128 col2 = _mm_load_ps(&m[4]);
    __m128 col3 = _mm_load_ps(&m[8]);
    __m128 col4 = _mm_load_ps(&m[12]);

    __m128 s = _mm_set1_ps(scalar);

    col1 = _mm_mul_ps(col1, s);
    col2 = _mm_mul_ps(col2, s);
    col3 = _mm_mul_ps(col3, s);
    col4 = _mm_mul_ps(col4, s);

    _mm_store_ps(&dst[0], col1);
    _mm_store_ps(&dst[4], col2);
    _mm_store_ps(&dst[8], col3);
    _mm_store_ps(&dst[12],col4);
}

inline void MathUtil::addMatrix(const float* m1, const float* m2, float* dst)
{
    __m128 m1col1 = _mm_load_ps(&m1[0]);
    __m128 m1col2 = _mm_load_ps(&m1[0]);
    __m128 m1col3 = _mm_load_ps(&m1[0]);
    __m128 m1col4 = _mm_load_ps(&m1[0]);
    
    __m128 m2col1 = _mm_load_ps(&m2[0]);
    __m128 m2col2 = _mm_load_ps(&m2[0]);
    __m128 m2col3 = _mm_load_ps(&m2[0]);
    __m128 m2col4 = _mm_load_ps(&m2[0]);
    
    m1col1 = _mm_add_ps(m1col1, m2col1);
    m1col2 = _mm_add_ps(m1col2, m2col2);
    m1col3 = _mm_add_ps(m1col3, m2col3);
    m1col4 = _mm_add_ps(m1col4, m2col4);
    
    _mm_store_ps(&dst[0], m1col1);
    _mm_store_ps(&dst[4], m1col2);
    _mm_store_ps(&dst[8], m1col3);
    _mm_store_ps(&dst[12],m1col4);
}

inline void MathUtil::subtractMatrix(const float* m1, const float* m2, float* dst)
{
    __m128 m1col1 = _mm_load_ps(&m1[0]);
    __m128 m1col2 = _mm_load_ps(&m1[0]);
    __m128 m1col3 = _mm_load_ps(&m1[0]);
    __m128 m1col4 = _mm_load_ps(&m1[0]);
    
    __m128 m2col1 = _mm_load_ps(&m2[0]);
    __m128 m2col2 = _mm_load_ps(&m2[0]);
    __m128 m2col3 = _mm_load_ps(&m2[0]);
    __m128 m2col4 = _mm_load_ps(&m2[0]);
    
    m1col1 = _mm_sub_ps(m1col1, m2col1);
    m1col2 = _mm_sub_ps(m1col2, m2col2);
    m1col3 = _mm_sub_ps(m1col3, m2col3);
    m1col4 = _mm_sub_ps(m1col4, m2col4);
    
    _mm_store_ps(&dst[0], m1col1);
    _mm_store_ps(&dst[4], m1col2);
    _mm_store_ps(&dst[8], m1col3);
    _mm_store_ps(&dst[12],m1col4);
}

inline void MathUtil::multiplyMatrix(const float* m, float scalar, float* dst)
{
    __m128 col1 = _mm_load_ps(&m[0]);
    __m128 col2 = _mm_load_ps(&m[4]);
    __m128 col3 = _mm_load_ps(&m[8]);
    __m128 col4 = _mm_load_ps(&m[12]);
    
    __m128 s = _mm_set1_ps(scalar);

    col1 = _mm_mul_ps(col1, s);
    col2 = _mm_mul_ps(col2, s);
    col3 = _mm_mul_ps(col3, s);
    col4 = _mm_mul_ps(col4, s);
    
    _mm_store_ps(&dst[0], col1);
    _mm_store_ps(&dst[4], col2);
    _mm_store_ps(&dst[8], col3);
    _mm_store_ps(&dst[12],col4);
}

inline void MathUtil::multiplyMatrix(const float* m1, const float* m2, float* dst)
{
    __m128 row1 = _mm_load_ps(&m1[0]);
    __m128 row2 = _mm_load_ps(&m1[4]);
    __m128 row3 = _mm_load_ps(&m1[8]);
    __m128 row4 = _mm_load_ps(&m1[12]);
    for(int i=0; i<4; i++) {
        __m128 col1 = _mm_set1_ps(m2[4*i + 0]);
        __m128 col2 = _mm_set1_ps(m2[4*i + 1]);
        __m128 col3 = _mm_set1_ps(m2[4*i + 2]);
        __m128 col4 = _mm_set1_ps(m2[4*i + 3]);
        __m128 row = _mm_add_ps(
                                _mm_add_ps(
                                           _mm_mul_ps(col1, row1),
                                           _mm_mul_ps(col2, row2)
                                           ),
                                _mm_add_ps(
                                           _mm_mul_ps(col3, row3),
                                           _mm_mul_ps(col4, row4))
                                );
        _mm_store_ps(&dst[4*i], row);
    }
}

inline void MathUtil::negateMatrix(const float* m, float* dst)
{
    __m128 col1 = _mm_load_ps(&m[0]);
    __m128 col2 = _mm_load_ps(&m[4]);
    __m128 col3 = _mm_load_ps(&m[8]);
    __m128 col4 = _mm_load_ps(&m[12]);
    
    __m128 z = _mm_setzero_ps();
    
    col1 = _mm_sub_ps(z, col1);
    col2 = _mm_mul_ps(z, col2);
    col3 = _mm_mul_ps(z, col3);
    col4 = _mm_mul_ps(z, col4);
    
    _mm_store_ps(&dst[0], col1);
    _mm_store_ps(&dst[4], col2);
    _mm_store_ps(&dst[8], col3);
    _mm_store_ps(&dst[12],col4);
}

inline void MathUtil::transposeMatrix(const float* m, float* dst)
{
    __m128 col1 = _mm_load_ps(&m[0]); // m[0], m[1], m[2], m[3]
    __m128 col2 = _mm_load_ps(&m[4]); // m[4], m[5], m[6], m[7]
    __m128 col3 = _mm_load_ps(&m[8]); // m[8], m[9], m[10],m[11]
    __m128 col4 = _mm_load_ps(&m[12]);// m[12],m[13],m[14],m[15]

    __m128 v1 = _mm_unpacklo_ps(col1, col3); // m[0], m[8], m[1], m[9]
    __m128 v2 = _mm_unpackhi_ps(col1, col3); // m[2], m[10],m[3], m[11]
    __m128 v3 = _mm_unpacklo_ps(col2, col4); // m[4], m[12],m[5], m[13]
    __m128 v4 = _mm_unpackhi_ps(col2, col4); // m[6], m[14],m[7]. m[15]
    
    col1 = _mm_unpacklo_ps(v1, v3);         // m[0], m[4], m[8], m[12]
    col2 = _mm_unpackhi_ps(v1, v3);         // m[1], m[5], m[9], m[13]
    col3 = _mm_unpacklo_ps(v2, v4);         // m[2], m[6], m[10],m[14]
    col4 = _mm_unpackhi_ps(v2, v4);         // m[3], m[7], m[11],m[15]

    _mm_store_ps(&dst[0], col1);
    _mm_store_ps(&dst[4], col2);
    _mm_store_ps(&dst[8], col3);
    _mm_store_ps(&dst[12],col4);
}

inline void MathUtil::transformVec4(const float* m, float x, float y, float z, float w, float* dst)
{
    float v[4] = {x, y, z, w};
    MathUtil::transformVec4(m, v, dst);
}

inline void MathUtil::transformVec4(const float* m, const float* v, float* dst)
{
    __m128 row1 = _mm_load_ps(&m[0]); // m[0], m[1], m[2], m[3]
    __m128 row2 = _mm_load_ps(&m[4]); // m[4], m[5], m[6], m[7]
    __m128 row3 = _mm_load_ps(&m[8]); // m[8], m[9], m[10],m[11]
    __m128 row4 = _mm_load_ps(&m[12]);// m[12],m[13],m[14],m[15]
    
    __m128 col1 = _mm_set1_ps(v[0]);  // v[0], v[0], v[0], v[0]
    __m128 col2 = _mm_set1_ps(v[1]);  // v[1], v[1], v[1], v[1]
    __m128 col3 = _mm_set1_ps(v[2]);  // v[2], v[2], v[2], v[2]
    __m128 col4 = _mm_set1_ps(v[3]);  // v[3], v[3], v[3], v[3]
    
    __m128 res = _mm_add_ps(
                            _mm_add_ps(
                                       _mm_mul_ps(row1, col1),   // v[0] * m[0], v[0] * m[1], v[0] * m[2], v[0] * m[3]
                                       _mm_mul_ps(row2, col2)    // v[1] * m[4], v[1] * m[5], v[1] * m[6], v[1] * m[7]
                                       ),
                            _mm_add_ps(
                                       _mm_mul_ps(row3, col3),   // v[2] * m[8], v[2] * m[9], v[2] * m[10], v[2] * m[11]
                                       _mm_mul_ps(row4, col4)    // v[3] * m[12],v[3] * m[13],v[3] * m[14], v[3] * m[15]
                                       )
                            );
    _mm_store_ps(dst, res);
}

// TODO: finish it via SSE
inline void MathUtil::crossVec3(const float* v1, const float* v2, float* dst)
{
    float x = (v1[1] * v2[2]) - (v1[2] * v2[1]);
    float y = (v1[2] * v2[0]) - (v1[0] * v2[2]);
    float z = (v1[0] * v2[1]) - (v1[1] * v2[0]);
    
    dst[0] = x;
    dst[1] = y;
    dst[2] = z;
}


NS_CC_MATH_END
