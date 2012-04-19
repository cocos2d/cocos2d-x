/*
 * Copyright (C) 2011 Google Inc.
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

#ifndef SkPDFUtils_DEFINED
#define SkPDFUtils_DEFINED

#include "SkPath.h"

class SkMatrix;
class SkPath;
class SkPDFArray;
struct SkRect;

#if 0
#define PRINT_NOT_IMPL(str) fprintf(stderr, str)
#else
#define PRINT_NOT_IMPL(str)
#endif

#define NOT_IMPLEMENTED(condition, assert)                         \
    do {                                                           \
        if (condition) {                                           \
            PRINT_NOT_IMPL("NOT_IMPLEMENTED: " #condition "\n");   \
            SkDEBUGCODE(SkASSERT(!assert);)                        \
        }                                                          \
    } while(0)

class SkPDFUtils {
public:
    static SkPDFArray* MatrixToArray(const SkMatrix& matrix);
    static void AppendTransform(const SkMatrix& matrix, SkWStream* content);

    static void MoveTo(SkScalar x, SkScalar y, SkWStream* content);
    static void AppendLine(SkScalar x, SkScalar y, SkWStream* content);
    static void AppendCubic(SkScalar ctl1X, SkScalar ctl1Y,
                            SkScalar ctl2X, SkScalar ctl2Y,
                            SkScalar dstX, SkScalar dstY, SkWStream* content);
    static void AppendRectangle(const SkRect& rect, SkWStream* content);
    static void EmitPath(const SkPath& path, SkWStream* content);
    static void ClosePath(SkWStream* content);
    static void PaintPath(SkPaint::Style style, SkPath::FillType fill,
                          SkWStream* content);
    static void StrokePath(SkWStream* content);
    static void DrawFormXObject(int objectIndex, SkWStream* content);
    static void ApplyGraphicState(int objectIndex, SkWStream* content);
};

#endif
