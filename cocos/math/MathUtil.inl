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

NS_CC_MATH_BEGIN

class MathUtilC
{
public:
    inline static void addMatrix(const float* m, float scalar, float* dst);
    
    inline static void addMatrix(const float* m1, const float* m2, float* dst);
    
    inline static void subtractMatrix(const float* m1, const float* m2, float* dst);
    
    inline static void multiplyMatrix(const float* m, float scalar, float* dst);
    
    inline static void multiplyMatrix(const float* m1, const float* m2, float* dst);
    
    inline static void negateMatrix(const float* m, float* dst);
    
    inline static void transposeMatrix(const float* m, float* dst);
    
    inline static void transformVec4(const float* m, float x, float y, float z, float w, float* dst);
    
    inline static void transformVec4(const float* m, const float* v, float* dst);
    
    inline static void crossVec3(const float* v1, const float* v2, float* dst);
};

inline void MathUtilC::addMatrix(const float* m, float scalar, float* dst)
{
    dst[0]  = m[0]  + scalar;
    dst[1]  = m[1]  + scalar;
    dst[2]  = m[2]  + scalar;
    dst[3]  = m[3]  + scalar;
    dst[4]  = m[4]  + scalar;
    dst[5]  = m[5]  + scalar;
    dst[6]  = m[6]  + scalar;
    dst[7]  = m[7]  + scalar;
    dst[8]  = m[8]  + scalar;
    dst[9]  = m[9]  + scalar;
    dst[10] = m[10] + scalar;
    dst[11] = m[11] + scalar;
    dst[12] = m[12] + scalar;
    dst[13] = m[13] + scalar;
    dst[14] = m[14] + scalar;
    dst[15] = m[15] + scalar;
}

inline void MathUtilC::addMatrix(const float* m1, const float* m2, float* dst)
{
    dst[0]  = m1[0]  + m2[0];
    dst[1]  = m1[1]  + m2[1];
    dst[2]  = m1[2]  + m2[2];
    dst[3]  = m1[3]  + m2[3];
    dst[4]  = m1[4]  + m2[4];
    dst[5]  = m1[5]  + m2[5];
    dst[6]  = m1[6]  + m2[6];
    dst[7]  = m1[7]  + m2[7];
    dst[8]  = m1[8]  + m2[8];
    dst[9]  = m1[9]  + m2[9];
    dst[10] = m1[10] + m2[10];
    dst[11] = m1[11] + m2[11];
    dst[12] = m1[12] + m2[12];
    dst[13] = m1[13] + m2[13];
    dst[14] = m1[14] + m2[14];
    dst[15] = m1[15] + m2[15];
}

inline void MathUtilC::subtractMatrix(const float* m1, const float* m2, float* dst)
{
    dst[0]  = m1[0]  - m2[0];
    dst[1]  = m1[1]  - m2[1];
    dst[2]  = m1[2]  - m2[2];
    dst[3]  = m1[3]  - m2[3];
    dst[4]  = m1[4]  - m2[4];
    dst[5]  = m1[5]  - m2[5];
    dst[6]  = m1[6]  - m2[6];
    dst[7]  = m1[7]  - m2[7];
    dst[8]  = m1[8]  - m2[8];
    dst[9]  = m1[9]  - m2[9];
    dst[10] = m1[10] - m2[10];
    dst[11] = m1[11] - m2[11];
    dst[12] = m1[12] - m2[12];
    dst[13] = m1[13] - m2[13];
    dst[14] = m1[14] - m2[14];
    dst[15] = m1[15] - m2[15];
}

inline void MathUtilC::multiplyMatrix(const float* m, float scalar, float* dst)
{
    dst[0]  = m[0]  * scalar;
    dst[1]  = m[1]  * scalar;
    dst[2]  = m[2]  * scalar;
    dst[3]  = m[3]  * scalar;
    dst[4]  = m[4]  * scalar;
    dst[5]  = m[5]  * scalar;
    dst[6]  = m[6]  * scalar;
    dst[7]  = m[7]  * scalar;
    dst[8]  = m[8]  * scalar;
    dst[9]  = m[9]  * scalar;
    dst[10] = m[10] * scalar;
    dst[11] = m[11] * scalar;
    dst[12] = m[12] * scalar;
    dst[13] = m[13] * scalar;
    dst[14] = m[14] * scalar;
    dst[15] = m[15] * scalar;
}

inline void MathUtilC::multiplyMatrix(const float* m1, const float* m2, float* dst)
{
    // Support the case where m1 or m2 is the same array as dst.
    float product[16];
    
    product[0]  = m1[0] * m2[0]  + m1[4] * m2[1] + m1[8]   * m2[2]  + m1[12] * m2[3];
    product[1]  = m1[1] * m2[0]  + m1[5] * m2[1] + m1[9]   * m2[2]  + m1[13] * m2[3];
    product[2]  = m1[2] * m2[0]  + m1[6] * m2[1] + m1[10]  * m2[2]  + m1[14] * m2[3];
    product[3]  = m1[3] * m2[0]  + m1[7] * m2[1] + m1[11]  * m2[2]  + m1[15] * m2[3];
    
    product[4]  = m1[0] * m2[4]  + m1[4] * m2[5] + m1[8]   * m2[6]  + m1[12] * m2[7];
    product[5]  = m1[1] * m2[4]  + m1[5] * m2[5] + m1[9]   * m2[6]  + m1[13] * m2[7];
    product[6]  = m1[2] * m2[4]  + m1[6] * m2[5] + m1[10]  * m2[6]  + m1[14] * m2[7];
    product[7]  = m1[3] * m2[4]  + m1[7] * m2[5] + m1[11]  * m2[6]  + m1[15] * m2[7];
    
    product[8]  = m1[0] * m2[8]  + m1[4] * m2[9] + m1[8]   * m2[10] + m1[12] * m2[11];
    product[9]  = m1[1] * m2[8]  + m1[5] * m2[9] + m1[9]   * m2[10] + m1[13] * m2[11];
    product[10] = m1[2] * m2[8]  + m1[6] * m2[9] + m1[10]  * m2[10] + m1[14] * m2[11];
    product[11] = m1[3] * m2[8]  + m1[7] * m2[9] + m1[11]  * m2[10] + m1[15] * m2[11];
    
    product[12] = m1[0] * m2[12] + m1[4] * m2[13] + m1[8]  * m2[14] + m1[12] * m2[15];
    product[13] = m1[1] * m2[12] + m1[5] * m2[13] + m1[9]  * m2[14] + m1[13] * m2[15];
    product[14] = m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14] + m1[14] * m2[15];
    product[15] = m1[3] * m2[12] + m1[7] * m2[13] + m1[11] * m2[14] + m1[15] * m2[15];
    
    memcpy(dst, product, MATRIX_SIZE);
}

inline void MathUtilC::negateMatrix(const float* m, float* dst)
{
    dst[0]  = -m[0];
    dst[1]  = -m[1];
    dst[2]  = -m[2];
    dst[3]  = -m[3];
    dst[4]  = -m[4];
    dst[5]  = -m[5];
    dst[6]  = -m[6];
    dst[7]  = -m[7];
    dst[8]  = -m[8];
    dst[9]  = -m[9];
    dst[10] = -m[10];
    dst[11] = -m[11];
    dst[12] = -m[12];
    dst[13] = -m[13];
    dst[14] = -m[14];
    dst[15] = -m[15];
}

inline void MathUtilC::transposeMatrix(const float* m, float* dst)
{
    float t[16] = {
        m[0], m[4], m[8], m[12],
        m[1], m[5], m[9], m[13],
        m[2], m[6], m[10], m[14],
        m[3], m[7], m[11], m[15]
    };
    memcpy(dst, t, MATRIX_SIZE);
}

inline void MathUtilC::transformVec4(const float* m, float x, float y, float z, float w, float* dst)
{
    dst[0] = x * m[0] + y * m[4] + z * m[8] + w * m[12];
    dst[1] = x * m[1] + y * m[5] + z * m[9] + w * m[13];
    dst[2] = x * m[2] + y * m[6] + z * m[10] + w * m[14];
}

inline void MathUtilC::transformVec4(const float* m, const float* v, float* dst)
{
    // Handle case where v == dst.
    float x = v[0] * m[0] + v[1] * m[4] + v[2] * m[8] + v[3] * m[12];
    float y = v[0] * m[1] + v[1] * m[5] + v[2] * m[9] + v[3] * m[13];
    float z = v[0] * m[2] + v[1] * m[6] + v[2] * m[10] + v[3] * m[14];
    float w = v[0] * m[3] + v[1] * m[7] + v[2] * m[11] + v[3] * m[15];
    
    dst[0] = x;
    dst[1] = y;
    dst[2] = z;
    dst[3] = w;
}

inline void MathUtilC::crossVec3(const float* v1, const float* v2, float* dst)
{
    float x = (v1[1] * v2[2]) - (v1[2] * v2[1]);
    float y = (v1[2] * v2[0]) - (v1[0] * v2[2]);
    float z = (v1[0] * v2[1]) - (v1[1] * v2[0]);
    
    dst[0] = x;
    dst[1] = y;
    dst[2] = z;
}

NS_CC_MATH_END
