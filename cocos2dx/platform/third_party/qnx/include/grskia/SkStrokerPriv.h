/* libs/graphics/sgl/SkStrokerPriv.h
**
** Copyright 2006, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License"); 
** you may not use this file except in compliance with the License. 
** You may obtain a copy of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** Unless required by applicable law or agreed to in writing, software 
** distributed under the License is distributed on an "AS IS" BASIS, 
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
** See the License for the specific language governing permissions and 
** limitations under the License.
*/

#ifndef SkStrokerPriv_DEFINED
#define SkStrokerPriv_DEFINED

#include "SkStroke.h"

#define CWX(x, y)   (-y)
#define CWY(x, y)   (x)
#define CCWX(x, y)  (y)
#define CCWY(x, y)  (-x)

#define CUBIC_ARC_FACTOR    ((SK_ScalarSqrt2 - SK_Scalar1) * 4 / 3)

class SkStrokerPriv {
public:
    typedef void (*CapProc)(SkPath* path,
                            const SkPoint& pivot,
                            const SkVector& normal,
                            const SkPoint& stop,
                            SkPath* otherPath);

    typedef void (*JoinProc)(SkPath* outer, SkPath* inner,
                             const SkVector& beforeUnitNormal,
                             const SkPoint& pivot,
                             const SkVector& afterUnitNormal,
                             SkScalar radius, SkScalar invMiterLimit,
                             bool prevIsLine, bool currIsLine);

    static CapProc  CapFactory(SkPaint::Cap);
    static JoinProc JoinFactory(SkPaint::Join);
};

#endif

