/*
    Copyright 2010 Google Inc.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

         http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
 */


#ifndef GrGpuVertex_DEFINED
#define GrGpuVertex_DEFINED

#include "GrGLConfig.h"
#include "GrPoint.h"

#if GR_TEXT_SCALAR_IS_USHORT
    typedef uint16_t                GrTextScalar;  
    #define GrIntToTextScalar(x)    ((uint16_t)x)
    #define GrFixedToTextScalar(x)  (x)
#elif GR_TEXT_SCALAR_IS_FIXED
    typedef GrFixed                 GrTextScalar;
    #define GrIntToTextScalar(x)    GrIntToFixed(x)
    #define GrFixedToTextScalar(x)  (x)
#elif GR_TEXT_SCALAR_IS_FLOAT
    typedef float                   GrTextScalar;    
    #define GrIntToTextScalar(x)    ((GrTextScalar)x)
    #define GrFixedToTextScalar(x)  GrFixedToFloat(x)
#else
    #error "Text scalar type not defined"
#endif

// text has its own vertex class, since it may want to be in fixed point (given)
// that it starts with all integers) even when the default vertices are floats
struct GrGpuTextVertex {
    GrTextScalar fX;
    GrTextScalar fY;

    void set(GrTextScalar x, GrTextScalar y) {
        fX = x;
        fY = y;
    }

    void setI(int x, int y) {
        fX = GrIntToTextScalar(x);
        fY = GrIntToTextScalar(y);
    }
    
    void setX(GrFixed x, GrFixed y) {
        fX = GrFixedToTextScalar(x);
        fY = GrFixedToTextScalar(y);
    }
    
    // rect fan is counter-clockwise

    void setRectFan(GrTextScalar l, GrTextScalar t, GrTextScalar r,
                    GrTextScalar b) {
        GrGpuTextVertex* v = this;
        v[0].set(l, t);
        v[1].set(l, b);
        v[2].set(r, b);
        v[3].set(r, t);
    }

    void setIRectFan(int l, int t, int r, int b) {
        this->setRectFan(GrIntToTextScalar(l), GrIntToTextScalar(t),
                         GrIntToTextScalar(r), GrIntToTextScalar(b));
    }

    void setIRectFan(int l, int t, int r, int b, size_t stride) {
        GrAssert(stride > sizeof(GrGpuTextVertex));
        char* v = (char*)this;
        ((GrGpuTextVertex*)(v + 0*stride))->setI(l, t);
        ((GrGpuTextVertex*)(v + 1*stride))->setI(l, b);
        ((GrGpuTextVertex*)(v + 2*stride))->setI(r, b);
        ((GrGpuTextVertex*)(v + 3*stride))->setI(r, t);
    }

    // counter-clockwise fan
    void setXRectFan(GrFixed l, GrFixed t, GrFixed r, GrFixed b) {
        this->setRectFan(GrFixedToTextScalar(l), GrFixedToTextScalar(t),
                         GrFixedToTextScalar(r), GrFixedToTextScalar(b));
    }

    void setXRectFan(GrFixed l, GrFixed t, GrFixed r, GrFixed b, size_t stride) {
        GrAssert(stride > sizeof(GrGpuTextVertex));
        char* v = (char*)this;
        ((GrGpuTextVertex*)(v + 0*stride))->setX(l, t);
        ((GrGpuTextVertex*)(v + 1*stride))->setX(l, b);
        ((GrGpuTextVertex*)(v + 2*stride))->setX(r, b);
        ((GrGpuTextVertex*)(v + 3*stride))->setX(r, t);
    }

};

#endif

