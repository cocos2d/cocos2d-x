/*
 * Copyright (C) 2007 The Android Open Source Project
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

#ifndef SkColorMatrixFilter_DEFINED
#define SkColorMatrixFilter_DEFINED

#include "SkColorFilter.h"
#include "SkColorMatrix.h"

class SkColorMatrixFilter : public SkColorFilter {
public:
    SkColorMatrixFilter();
    explicit SkColorMatrixFilter(const SkColorMatrix&);
    SkColorMatrixFilter(const SkScalar array[20]);

    void setMatrix(const SkColorMatrix&);
    void setArray(const SkScalar array[20]);

    // overrides from SkColorFilter
    virtual void filterSpan(const SkPMColor src[], int count, SkPMColor[]);
    virtual void filterSpan16(const uint16_t src[], int count, uint16_t[]);
    virtual uint32_t getFlags();

    // overrides for SkFlattenable
    virtual void flatten(SkFlattenableWriteBuffer& buffer);

    struct State {
        int32_t fArray[20];
        int     fShift;
        int32_t fResult[4];
    };

    static SkFlattenable* CreateProc(SkFlattenableReadBuffer& buffer);

protected:
    // overrides for SkFlattenable
    virtual Factory getFactory();

    SkColorMatrixFilter(SkFlattenableReadBuffer& buffer);

private:

    typedef void (*Proc)(State*, unsigned r, unsigned g, unsigned b,
                         unsigned a);

    Proc        fProc;
    State       fState;
    uint32_t    fFlags;

    void setup(const SkScalar array[20]);

    typedef SkColorFilter INHERITED;
};

#endif
