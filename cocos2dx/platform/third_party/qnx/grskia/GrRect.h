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


#ifndef GrRect_DEFINED
#define GrRect_DEFINED

#include "GrPoint.h"
#include "SkRect.h"

typedef SkIRect GrIRect;
typedef SkRect  GrRect;

struct GrIRect16 {
    int16_t fLeft, fTop, fRight, fBottom;
    
    int width() const { return fRight - fLeft; }
    int height() const { return fBottom - fTop; }
    int area() const { return this->width() * this->height(); }
    bool isEmpty() const { return fLeft >= fRight || fTop >= fBottom; }
    
    void set(const GrIRect& r) {
        fLeft   = SkToS16(r.fLeft);
        fTop    = SkToS16(r.fTop);
        fRight  = SkToS16(r.fRight);
        fBottom = SkToS16(r.fBottom);
    }
};

#endif

