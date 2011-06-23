/*
 * Copyright (C) 2009 The Android Open Source Project
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

#ifndef SkMeshUtils_DEFINED
#define SkMeshUtils_DEFINED

#include "SkPoint.h"
#include "SkColor.h"

class SkBitmap;
class SkCanvas;
class SkPaint;

class SkMeshIndices {
public:
    SkMeshIndices();
    ~SkMeshIndices();

    bool init(int texW, int texH, int rows, int cols) {
        return this->init(NULL, NULL, texW, texH, rows, cols);
    }

    bool init(SkPoint tex[], uint16_t indices[],
              int texW, int texH, int rows, int cols);

    size_t          indexCount() const { return fIndexCount; }
    const uint16_t* indices() const { return fIndices; }

    size_t          texCount() const { return fTexCount; }
    const SkPoint*  tex() const { return fTex; }

private:
    size_t      fIndexCount, fTexCount;
    SkPoint*    fTex;
    uint16_t*   fIndices;
    void*       fStorage; // may be null
};

class SkMeshUtils {
public:
    static void Draw(SkCanvas*, const SkBitmap&, int rows, int cols,
                     const SkPoint verts[], const SkColor colors[],
                     const SkPaint& paint);
};

#endif
