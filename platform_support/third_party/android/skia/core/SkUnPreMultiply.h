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




#ifndef SkUnPreMultiply_DEFINED
#define SkUnPreMultiply_DEFINED

#include "SkColor.h"

class SkUnPreMultiply {
public:
    typedef uint32_t Scale;
    
    // index this table with alpha [0..255]
    static const Scale* GetScaleTable() {
        return gTable;
    }

    static Scale GetScale(U8CPU alpha) {
        SkASSERT(alpha <= 255);
        return gTable[alpha];
    }
    
    /** Usage:
     
        const Scale* table = SkUnPreMultiply::GetScaleTable();
     
        for (...) {
            unsigned a = ...
            SkUnPreMultiply::Scale scale = table[a];
     
            red = SkUnPreMultiply::ApplyScale(scale, red);
            ...
            // now red is unpremultiplied
        }
    */
    static U8CPU ApplyScale(Scale scale, U8CPU component) {
        SkASSERT(component <= 255);
        return (scale * component + (1 << 23)) >> 24;
    }
    
    static SkColor PMColorToColor(SkPMColor c);
    
private:
    static const uint32_t gTable[256];
};

#endif
