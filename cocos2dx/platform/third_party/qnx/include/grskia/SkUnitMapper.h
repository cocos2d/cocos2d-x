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

#ifndef SkUnitMapper_DEFINED
#define SkUnitMapper_DEFINED

#include "SkRefCnt.h"
#include "SkScalar.h"

#include "SkFlattenable.h"

class SkUnitMapper : public SkFlattenable {
public:
    SkUnitMapper() {}

    /** Given a value in [0..0xFFFF], return a value in the same range.
    */
    virtual uint16_t mapUnit16(uint16_t x) = 0;
    
protected:
    SkUnitMapper(SkFlattenableReadBuffer& rb) : SkFlattenable(rb) {}
};

#endif

