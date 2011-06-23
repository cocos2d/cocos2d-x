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

#ifndef SkTableMaskFilter_DEFINED
#define SkTableMaskFilter_DEFINED

#include "SkMaskFilter.h"
#include "SkScalar.h"

/** \class SkTableMaskFilter
 
    Applies a table lookup on each of the alpha values in the mask.
    Helper methods create some common tables (e.g. gamma, clipping)
 */
class SkTableMaskFilter : public SkMaskFilter {
public:
    SkTableMaskFilter();
    SkTableMaskFilter(const uint8_t table[256]);
    virtual ~SkTableMaskFilter();

    void setTable(const uint8_t table[256]);

    /** Utility that sets the gamma table
     */
    static void MakeGammaTable(uint8_t table[256], SkScalar gamma);

    /** Utility that creates a clipping table: clamps values below min to 0
        and above max to 255, and rescales the remaining into 0..255
     */
    static void MakeClipTable(uint8_t table[256], uint8_t min, uint8_t max);

    static SkTableMaskFilter* CreateGamma(SkScalar gamma) {
        uint8_t table[256];
        MakeGammaTable(table, gamma);
        return SkNEW_ARGS(SkTableMaskFilter, (table));
    }

    static SkTableMaskFilter* CreateClip(uint8_t min, uint8_t max) {
        uint8_t table[256];
        MakeClipTable(table, min, max);
        return SkNEW_ARGS(SkTableMaskFilter, (table));
    }

    // overrides from SkMaskFilter
    virtual SkMask::Format getFormat();
    virtual bool filterMask(SkMask*, const SkMask&, const SkMatrix&, SkIPoint*);
    
    // overrides from SkFlattenable
    virtual void flatten(SkFlattenableWriteBuffer& wb);
    virtual Factory getFactory();

protected:
    SkTableMaskFilter(SkFlattenableReadBuffer& rb);
    static SkFlattenable* Factory(SkFlattenableReadBuffer&);

private:
    uint8_t fTable[256];
    
    typedef SkMaskFilter INHERITED;
};

#endif

