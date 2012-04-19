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


#ifndef SkFlingState_DEFINED
#define SkFlingState_DEFINED

#include "SkScalar.h"
#include "SkPoint.h"

class SkMatrix;

struct FlingState {
    FlingState() : fActive(false) {}

    bool isActive() const { return fActive; }
    void stop() { fActive = false; }

    void reset(float sx, float sy);
    bool evaluateMatrix(SkMatrix* matrix);

private:
    SkPoint     fDirection;
    SkScalar    fSpeed0;
    double      fTime0;
    bool        fActive;
};

class GrAnimateFloat {
public:
    GrAnimateFloat();

    void start(float v0, float v1, float duration);
    bool isActive() const { return fTime0 != 0; }
    void stop() { fTime0 = 0; }

    float evaluate();

private:
    float   fValue0, fValue1, fDuration;
    SkMSec  fTime0;
};

#endif

