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

#ifndef SkParsePaint_DEFINED
#define SkParsePaint_DEFINED

#include "SkPaint.h"
#include "SkDOM.h"

/** "color"             color
    "opacity"           scalar  [0..1]
    "stroke-width"      scalar  (0...inf)
    "text-size"         scalar  (0..inf)
    "is-stroke"         bool
    "is-antialias"      bool
    "is-lineartext"     bool
*/
void SkPaint_Inflate(SkPaint*, const SkDOM&, const SkDOM::Node*);

#endif

