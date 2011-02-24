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

#ifndef SkPixelXorXfermode_DEFINED
#define SkPixelXorXfermode_DEFINED

#include "SkXfermode.h"

/** SkPixelXorXfermode implements a simple pixel xor (op ^ src ^ dst).
    This transformation does not follow premultiplied conventions, therefore
    this proc *always* returns an opaque color (alpha == 255). Thus it is
    not really usefull for operating on blended colors.
*/
class SkPixelXorXfermode : public SkXfermode {
public:
    SkPixelXorXfermode(SkColor opColor) : fOpColor(opColor) {}

    // override from SkFlattenable
    virtual Factory getFactory();
    virtual void flatten(SkFlattenableWriteBuffer&);

protected:
    // override from SkXfermode
    virtual SkPMColor xferColor(SkPMColor src, SkPMColor dst);

private:
    SkColor fOpColor;

    SkPixelXorXfermode(SkFlattenableReadBuffer& rb);
    // our private factory
    static SkFlattenable* Create(SkFlattenableReadBuffer&);

    typedef SkXfermode INHERITED;
};

#endif

