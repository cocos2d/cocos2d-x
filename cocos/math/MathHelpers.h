//
//  MathHelpers.h
//  cocos2d_libs
//
//  Created by sun zhuoshi on 7/18/14.
//
//

#ifndef cocos2d_libs_MathHelpers_h
#define cocos2d_libs_MathHelpers_h

#include "base/ccMacros.h"
#include "math/Vec2.h"
#include "math/Vec3.h"
#include "math/Vec4.h"
#include "math/Mat4.h"

NS_CC_MATH_BEGIN

struct CC_DLL FloatMat4 {
    float m[16];
    FloatMat4() {
        for (int i=0; i<16; ++i) {
            m[i] = 0.0f;
        }
    }
    FloatMat4(const Mat4& mat) {
        for (int i=0; i<16; ++i) {
            m[i] = mat.m[i];
        }
    }
    inline operator float*() {
        return reinterpret_cast<float *>(this->m);
    }
};

struct CC_DLL FloatVec2 {
    float x;
    float y;
    FloatVec2(): x(0.0f), y(0.0f) {
    }
    FloatVec2(const Vec2& vec) {
        x = vec.x;
        y = vec.y;
    }
    inline operator float*() {
        return reinterpret_cast<float *>(&this->x);
    }
};

struct CC_DLL FloatVec3 {
    float x;
    float y;
    float z;
    FloatVec3(): x(0.0f), y(0.0f), z(0.0f) {
    }
    FloatVec3(const Vec3& vec) {
        x = vec.x;
        y = vec.y;
        z = vec.z;
    }
    inline FloatVec3 &operator =(const Vec3& vec) {
        x = vec.x;
        y = vec.y;
        z = vec.z;
        return *this;
    }
    inline operator float*() {
        return reinterpret_cast<float *>(&this->x);
    }
};

struct CC_DLL FloatVec4 {
    float x;
    float y;
    float z;
    float w;
    FloatVec4(): x(0.0f), y(0.0f), z(0.0f), w(0.0f) {
    }
    FloatVec4(const Vec4& vec) {
        x = vec.x;
        y = vec.y;
        z = vec.z;
        w = vec.w;
    }
    void set(float x_, float y_, float z_, float w_) {
        x = x_;
        y = y_;
        z = z_;
        w = w_;
    }
    inline operator float*() {
        return reinterpret_cast<float *>(&this->x);
    }
};

class MathHelpers {
public:
    static void inline transformPoint(const Mat4& mat, FloatVec3& vec) {
        Vec3 v(vec);
        mat.transformPoint(&v);
        vec = v;
    };
};

NS_CC_MATH_END


#endif
