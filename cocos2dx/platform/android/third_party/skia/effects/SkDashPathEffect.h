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

#ifndef SkDashPathEffect_DEFINED
#define SkDashPathEffect_DEFINED

#include "SkPathEffect.h"

/** \class SkDashPathEffect

    SkDashPathEffect is a subclass of SkPathEffect that implements dashing
*/
class SkDashPathEffect : public SkPathEffect {
public:
    /** The intervals array must contain an even number of entries (>=2), with the even
        indices specifying the "on" intervals, and the odd indices specifying the "off"
        intervals. phase is an offset into the intervals array (mod the sum of all of the
        intervals).
        Note: only affects framed paths
    */
    SkDashPathEffect(const SkScalar intervals[], int count, SkScalar phase, bool scaleToFit = false);
    virtual ~SkDashPathEffect();

    // overrides for SkPathEffect
    //  This method is not exported to java.
    virtual bool filterPath(SkPath* dst, const SkPath& src, SkScalar* width);

    // overrides for SkFlattenable
    //  This method is not exported to java.
    virtual Factory getFactory();
    //  This method is not exported to java.
    virtual void flatten(SkFlattenableWriteBuffer&);

protected:
    SkDashPathEffect(SkFlattenableReadBuffer&);
    
private:
    SkScalar*   fIntervals;
    int32_t     fCount;
    // computed from phase
    SkScalar    fInitialDashLength;
    int32_t     fInitialDashIndex;
    SkScalar    fIntervalLength;
    bool        fScaleToFit;

    static SkFlattenable* CreateProc(SkFlattenableReadBuffer&);

    typedef SkPathEffect INHERITED;
};

#endif

