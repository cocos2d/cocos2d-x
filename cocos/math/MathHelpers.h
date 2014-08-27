//
//  MathHelpers.h
//  cocos2d_libs
//
//  Created by sun zhuoshi on 7/18/14.
//
//

#ifndef cocos2d_libs_MathHelpers_h
#define cocos2d_libs_MathHelpers_h

#include "math/Mat4.h"

NS_CC_MATH_BEGIN

struct FloatMat4 {
    float m[16];
    FloatMat4(const Mat4& mat) {
        for (int i=0; i<16; ++i) {
            m[i] = mat.m[i];
        }
    }
    inline operator float*() {
        return reinterpret_cast<float *>(this->m);
    }
};

NS_CC_MATH_END


#endif
