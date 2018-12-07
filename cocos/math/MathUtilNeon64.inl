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

class MathUtilNeon64
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

inline void MathUtilNeon64::addMatrix(const float* m, float scalar, float* dst) __attribute__((optnone))
{
    asm volatile(
	    "ld4  {v0.4s, v1.4s, v2.4s, v3.4s}, [%1]    	\n\t" // M[m0-m7] M[m8-m15]
	    "ld1r {v4.4s}, [%2]				                \n\t" //ssss

	    "fadd v8.4s, v0.4s, v4.4s			\n\t" // DST->M[m0-m3] = M[m0-m3] + s
	    "fadd v9.4s, v1.4s, v4.4s			\n\t" // DST->M[m4-m7] = M[m4-m7] + s
	    "fadd v10.4s, v2.4s, v4.4s			\n\t" // DST->M[m8-m11] = M[m8-m11] + s
	    "fadd v11.4s, v3.4s, v4.4s			\n\t" // DST->M[m12-m15] = M[m12-m15] + s
	
        "st4 {v8.4s, v9.4s, v10.4s, v11.4s}, [%0] 	\n\t"    // Result in V9
	    :
        : "r"(dst), "r"(m), "r"(&scalar)
        : "v0", "v1", "v2", "v3", "v4", "v8", "v9", "v10", "v11", "memory"
    );
}

inline void MathUtilNeon64::addMatrix(const float* m1, const float* m2, float* dst) __attribute__((optnone))
{
    asm volatile(
        "ld4     {v0.4s, v1.4s, v2.4s, v3.4s},     [%1] 	\n\t" // M1[m0-m7] M1[m8-m15]
        "ld4     {v8.4s, v9.4s, v10.4s, v11.4s},   [%2] 	\n\t" // M2[m0-m7] M2[m8-m15]

        "fadd   v12.4s, v0.4s, v8.4s          \n\t" // DST->M[m0-m3] = M1[m0-m3] + M2[m0-m3]
        "fadd   v13.4s, v1.4s, v9.4s          \n\t" // DST->M[m4-m7] = M1[m4-m7] + M2[m4-m7]
        "fadd   v14.4s, v2.4s, v10.4s         \n\t" // DST->M[m8-m11] = M1[m8-m11] + M2[m8-m11]
        "fadd   v15.4s, v3.4s, v11.4s         \n\t" // DST->M[m12-m15] = M1[m12-m15] + M2[m12-m15]

        "st4    {v12.4s, v13.4s, v14.4s, v15.4s}, [%0]    \n\t" // DST->M[m0-m7] DST->M[m8-m15] 
        :
        : "r"(dst), "r"(m1), "r"(m2)
        : "v0", "v1", "v2", "v3", "v8", "v9", "v10", "v11", "v12", "v13", "v14", "v15", "memory"
    );
}

inline void MathUtilNeon64::subtractMatrix(const float* m1, const float* m2, float* dst) __attribute__((optnone))
{
    asm volatile(
        "ld4     {v0.4s, v1.4s, v2.4s, v3.4s},     [%1]  \n\t" // M1[m0-m7] M1[m8-m15]
        "ld4     {v8.4s, v9.4s, v10.4s, v11.4s},   [%2]  \n\t" // M2[m0-m7] M2[m8-m15] 

        "fsub   v12.4s, v0.4s, v8.4s         \n\t" // DST->M[m0-m3] = M1[m0-m3] - M2[m0-m3]
        "fsub   v13.4s, v1.4s, v9.4s         \n\t" // DST->M[m4-m7] = M1[m4-m7] - M2[m4-m7]
        "fsub   v14.4s, v2.4s, v10.4s        \n\t" // DST->M[m8-m11] = M1[m8-m11] - M2[m8-m11]
        "fsub   v15.4s, v3.4s, v11.4s        \n\t" // DST->M[m12-m15] = M1[m12-m15] - M2[m12-m15]

        "st4    {v12.4s, v13.4s, v14.4s, v15.4s}, [%0]   \n\t" // DST->M[m0-m7] DST->M[m8-m15]
        :
        : "r"(dst), "r"(m1), "r"(m2)
        : "v0", "v1", "v2", "v3", "v8", "v9", "v10", "v11", "v12", "v13", "v14", "v15", "memory"
    );
}

inline void MathUtilNeon64::multiplyMatrix(const float* m, float scalar, float* dst) __attribute__((optnone))
{
    asm volatile(
        "ld1     {v0.s}[0],         [%2]            \n\t" //s  
        "ld4     {v4.4s, v5.4s, v6.4s, v7.4s}, [%1]       \n\t" //M[m0-m7] M[m8-m15]

        "fmul     v8.4s, v4.4s, v0.s[0]               \n\t" // DST->M[m0-m3] = M[m0-m3] * s
        "fmul     v9.4s, v5.4s, v0.s[0]               \n\t" // DST->M[m4-m7] = M[m4-m7] * s
        "fmul     v10.4s, v6.4s, v0.s[0]              \n\t" // DST->M[m8-m11] = M[m8-m11] * s
        "fmul     v11.4s, v7.4s, v0.s[0]              \n\t" // DST->M[m12-m15] = M[m12-m15] * s

        "st4     {v8.4s, v9.4s, v10.4s, v11.4s},           [%0]     \n\t" // DST->M[m0-m7] DST->M[m8-m15]
        :
        : "r"(dst), "r"(m), "r"(&scalar)
        : "v0", "v4", "v5", "v6", "v7", "v8", "v9", "v10", "v11", "memory"
    );
}

inline void MathUtilNeon64::multiplyMatrix(const float* m1, const float* m2, float* dst) __attribute__((optnone))
{
    asm volatile(
        "ld1     {v8.4s, v9.4s, v10.4s, v11.4s}, [%1] \n\t"       // M1[m0-m7] M1[m8-m15] M2[m0-m7]  M2[m8-m15]
        "ld4     {v0.4s, v1.4s, v2.4s, v3.4s},  [%2]   \n\t"       // M2[m0-m15]


        "fmul    v12.4s, v8.4s, v0.s[0]     \n\t"         // DST->M[m0-m3] = M1[m0-m3] * M2[m0]
        "fmul    v13.4s, v8.4s, v0.s[1]     \n\t"         // DST->M[m4-m7] = M1[m4-m7] * M2[m4]
        "fmul    v14.4s, v8.4s, v0.s[2]     \n\t"         // DST->M[m8-m11] = M1[m8-m11] * M2[m8]
        "fmul    v15.4s, v8.4s, v0.s[3]     \n\t"         // DST->M[m12-m15] = M1[m12-m15] * M2[m12]

        "fmla    v12.4s, v9.4s, v1.s[0]     \n\t"         // DST->M[m0-m3] += M1[m0-m3] * M2[m1]
        "fmla    v13.4s, v9.4s, v1.s[1]     \n\t"         // DST->M[m4-m7] += M1[m4-m7] * M2[m5]
        "fmla    v14.4s, v9.4s, v1.s[2]     \n\t"         // DST->M[m8-m11] += M1[m8-m11] * M2[m9]
        "fmla    v15.4s, v9.4s, v1.s[3]     \n\t"         // DST->M[m12-m15] += M1[m12-m15] * M2[m13]

        "fmla    v12.4s, v10.4s, v2.s[0]    \n\t"         // DST->M[m0-m3] += M1[m0-m3] * M2[m2]
        "fmla    v13.4s, v10.4s, v2.s[1]    \n\t"         // DST->M[m4-m7] += M1[m4-m7] * M2[m6]
        "fmla    v14.4s, v10.4s, v2.s[2]    \n\t"         // DST->M[m8-m11] += M1[m8-m11] * M2[m10]
        "fmla    v15.4s, v10.4s, v2.s[3]    \n\t"         // DST->M[m12-m15] += M1[m12-m15] * M2[m14]

        "fmla    v12.4s, v11.4s, v3.s[0]    \n\t"         // DST->M[m0-m3] += M1[m0-m3] * M2[m3]
        "fmla    v13.4s, v11.4s, v3.s[1]    \n\t"         // DST->M[m4-m7] += M1[m4-m7] * M2[m7]
        "fmla    v14.4s, v11.4s, v3.s[2]    \n\t"         // DST->M[m8-m11] += M1[m8-m11] * M2[m11]
        "fmla    v15.4s, v11.4s, v3.s[3]    \n\t"         // DST->M[m12-m15] += M1[m12-m15] * M2[m15]

        "st1    {v12.4s, v13.4s, v14.4s, v15.4s}, [%0]  \n\t"       // DST->M[m0-m7]// DST->M[m8-m15]

        : // output
        : "r"(dst), "r"(m1), "r"(m2) // input - note *value* of pointer doesn't change.
        : "memory", "v0", "v1", "v2", "v3", "v8", "v9", "v10", "v11", "v12", "v13", "v14", "v15"
     );
}

inline void MathUtilNeon64::negateMatrix(const float* m, float* dst) __attribute__((optnone))
{
    asm volatile(
        "ld4     {v0.4s, v1.4s, v2.4s, v3.4s},  [%1]     \n\t" // load m0-m7 load m8-m15

        "fneg     v4.4s, v0.4s             \n\t" // negate m0-m3
        "fneg     v5.4s, v1.4s             \n\t" // negate m4-m7
        "fneg     v6.4s, v2.4s             \n\t" // negate m8-m15
        "fneg     v7.4s, v3.4s             \n\t" // negate m8-m15

        "st4     {v4.4s, v5.4s, v6.4s, v7.4s},  [%0]     \n\t" // store m0-m7 store m8-m15
        :
        : "r"(dst), "r"(m)
        : "v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7", "memory"
    );
}

inline void MathUtilNeon64::transposeMatrix(const float* m, float* dst) __attribute__((optnone))
{
    asm volatile(
        "ld4 {v0.4s, v1.4s, v2.4s, v3.4s}, [%1]    \n\t" // DST->M[m0, m4, m8, m12] = M[m0-m3] 
							 //DST->M[m1, m5, m9, m12] = M[m4-m7] 
        "st1 {v0.4s, v1.4s, v2.4s, v3.4s}, [%0]    \n\t"
        :
        : "r"(dst), "r"(m)
        : "v0", "v1", "v2", "v3", "memory"
    );
}

inline void MathUtilNeon64::transformVec4(const float* m, float x, float y, float z, float w, float* dst) __attribute__((optnone))
{
    asm volatile(
        "ld1    {v0.s}[0],        [%1]    \n\t"    // V[x]
        "ld1    {v0.s}[1],        [%2]    \n\t"    // V[y]
        "ld1    {v0.s}[2],        [%3]    \n\t"    // V[z]
        "ld1    {v0.s}[3],        [%4]    \n\t"    // V[w]
        "ld1    {v9.4s, v10.4s, v11.4s, v12.4s}, [%5]   \n\t"    // M[m0-m7] M[m8-m15]

	
        "fmul v13.4s, v9.4s, v0.s[0]           \n\t"      // DST->V = M[m0-m3] * V[x]
        "fmla v13.4s, v10.4s, v0.s[1]           \n\t"    // DST->V += M[m4-m7] * V[y]
        "fmla v13.4s, v11.4s, v0.s[2]           \n\t"    // DST->V += M[m8-m11] * V[z]
        "fmla v13.4s, v12.4s, v0.s[3]           \n\t"    // DST->V += M[m12-m15] * V[w]

        //"st1 {v13.4s}, [%0]               \n\t"    // DST->V[x, y] // DST->V[z]
        "st1 {v13.2s}, [%0], 8               \n\t"
        "st1 {v13.s}[2], [%0]                \n\t"
        :
        : "r"(dst), "r"(&x), "r"(&y), "r"(&z), "r"(&w), "r"(m)
        : "v0", "v9", "v10","v11", "v12", "v13", "memory"
    );
}

inline void MathUtilNeon64::transformVec4(const float* m, const float* v, float* dst) __attribute__((optnone))
{
    asm volatile
    (
        "ld1    {v0.4s}, [%1]     \n\t"   // V[x, y, z, w]
        "ld1    {v9.4s, v10.4s, v11.4s, v12.4s}, [%2] \n\t"   // M[m0-m7] M[m8-m15]

        "fmul   v13.4s, v9.4s, v0.s[0]     \n\t"   // DST->V = M[m0-m3] * V[x]
        "fmla   v13.4s, v10.4s, v0.s[1]    \n\t"   // DST->V = M[m4-m7] * V[y]
        "fmla   v13.4s, v11.4s, v0.s[2]    \n\t"   // DST->V = M[m8-m11] * V[z]
        "fmla   v13.4s, v12.4s, v0.s[3]    \n\t"   // DST->V = M[m12-m15] * V[w]

        "st1    {v13.4s}, [%0]  	 \n\t"   // DST->V
        :
        : "r"(dst), "r"(v), "r"(m)
        : "v0", "v9", "v10","v11", "v12", "v13", "memory"
    );
}

inline void MathUtilNeon64::crossVec3(const float* v1, const float* v2, float* dst) __attribute__((optnone))
{
        asm volatile(
        "ld1 {v0.2s},  [%2]           \n\t"
        "ld1 {v0.s}[2],  [%1]           \n\t"
        "mov v0.s[3], v0.s[0]         \n\t" // q0 = (v1y, v1z, v1x, v1x)

        "ld1 {v1.4s},  [%3]           \n\t"
        "mov v1.s[3], v1.s[0]           \n\t" // q1 = (v2x, v2y, v2z, v2x)

        "fmul v2.4s, v0.4s, v1.4s            \n\t" // x = v1y * v2z, y = v1z * v2x


        "mov v0.s[0], v0.s[1]           \n\t"
        "mov v0.s[1], v0.s[2]           \n\t"
        "mov v0.s[2], v0.s[3]           \n\t"

        "mov v1.s[3], v1.s[2]           \n\t"

        "fmul v0.4s, v0.4s, v1.4s            \n\t"

        "mov v0.s[3], v0.s[1]           \n\t"
        "mov v0.s[1], v0.s[2]           \n\t"
        "mov v0.s[2], v0.s[0]           \n\t"

        "fsub v2.4s, v0.4s, v2.4s            \n\t"

        "mov v2.s[0], v2.s[1]           \n\t"
        "mov v2.s[1], v2.s[2]           \n\t"
        "mov v2.s[2], v2.s[3]           \n\t"

        "st1 {v2.2s},       [%0], 8      \n\t" // V[x, y]
        "st1 {v2.s}[2],     [%0]         \n\t" // V[z]
        :
        : "r"(dst), "r"(v1), "r"((v1+1)), "r"(v2), "r"((v2+1))
        : "v0", "v1", "v2", "memory"
    );
}

NS_CC_MATH_END
