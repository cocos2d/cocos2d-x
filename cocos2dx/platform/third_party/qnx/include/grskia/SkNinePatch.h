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

#ifndef SkNinePatch_DEFINED
#define SkNinePatch_DEFINED

#include "SkRect.h"
#include "SkRegion.h"

class SkBitmap;
class SkCanvas;
class SkPaint;

class SkNinePatch {
public:
    static void DrawNine(SkCanvas* canvas, const SkRect& dst,
                     const SkBitmap& bitmap, const SkIRect& margins,
                     const SkPaint* paint = NULL);
    
    static void DrawMesh(SkCanvas* canvas, const SkRect& dst,
                         const SkBitmap& bitmap,
                         const int32_t xDivs[], int numXDivs,
                         const int32_t yDivs[], int numYDivs,
                         const SkPaint* paint = NULL);
};

#endif
