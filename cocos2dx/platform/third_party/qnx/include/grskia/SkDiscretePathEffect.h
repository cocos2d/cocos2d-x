/*
 * Copyright (C) 2006 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SkDiscretePathEffect_DEFINED
#define SkDiscretePathEffect_DEFINED

#include "SkPathEffect.h"

/** \class SkDiscretePathEffect

    This path effect chops a path into discrete segments, and randomly displaces them.
*/
class SkDiscretePathEffect : public SkPathEffect {
public:
    /** Break the path into segments of segLength length, and randomly move the endpoints
        away from the original path by a maximum of deviation.
        Note: works on filled or framed paths
    */
    SkDiscretePathEffect(SkScalar segLength, SkScalar deviation);

    // overrides for SkPathEffect
    //  This method is not exported to java.
    virtual bool filterPath(SkPath* dst, const SkPath& src, SkScalar* width);

    // overrides for SkFlattenable
    //  This method is not exported to java.
    virtual Factory getFactory();
    //  This method is not exported to java.
    virtual void flatten(SkFlattenableWriteBuffer&);

    static SkFlattenable* CreateProc(SkFlattenableReadBuffer&);

protected:
    SkDiscretePathEffect(SkFlattenableReadBuffer&);

private:
    SkScalar fSegLength, fPerterb;
    
    typedef SkPathEffect INHERITED;
};

#endif

