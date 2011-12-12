/*
 * Copyright (C) 2008 The Android Open Source Project
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

#ifndef SkPaintFlagsDrawFilter_DEFINED
#define SkPaintFlagsDrawFilter_DEFINED

#include "SkDrawFilter.h"

class SkPaintFlagsDrawFilter : public SkDrawFilter {
public:
    SkPaintFlagsDrawFilter(uint32_t clearFlags, uint32_t setFlags);
    
    // overrides
    virtual void filter(SkPaint*, Type);
    
private:
    uint32_t    fPrevFlags;     // local cache for filter/restore
    uint16_t    fClearFlags;    // user specified
    uint16_t    fSetFlags;      // user specified
};

#endif

