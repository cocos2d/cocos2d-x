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

#ifndef SkColorShader_DEFINED
#define SkColorShader_DEFINED

#include "SkShader.h"

/** \class SkColorShader
    A Shader that represents a single color. In general, this effect can be
    accomplished by just using the color field on the paint, but if an
    actual shader object is needed, this provides that feature.
*/
class SK_API SkColorShader : public SkShader {
public:
    /** Create a ColorShader that will inherit its color from the Paint
        at draw time.
    */
    SkColorShader();

    /** Create a ColorShader that ignores the color in the paint, and uses the
        specified color. Note: like all shaders, at draw time the paint's alpha
        will be respected, and is applied to the specified color.
    */
    SkColorShader(SkColor c);

    virtual ~SkColorShader();

    virtual uint32_t getFlags() { return fFlags; }
    virtual uint8_t getSpan16Alpha() const;
    virtual bool setContext(const SkBitmap& device, const SkPaint& paint,
                            const SkMatrix& matrix);
    virtual void shadeSpan(int x, int y, SkPMColor span[], int count);
    virtual void shadeSpan16(int x, int y, uint16_t span[], int count);
    virtual void shadeSpanAlpha(int x, int y, uint8_t alpha[], int count);

    virtual BitmapType asABitmap(SkBitmap* outTexture,
                                 SkMatrix* outMatrix,
                                 TileMode xy[2],
                                 SkScalar* twoPointRadialParams) const;

    virtual GradientType asAGradient(GradientInfo* info) const;

protected:
    SkColorShader(SkFlattenableReadBuffer& );
    virtual void flatten(SkFlattenableWriteBuffer& );
    virtual Factory getFactory() { return CreateProc; }
private:
    static SkFlattenable* CreateProc(SkFlattenableReadBuffer& buffer) {
        return SkNEW_ARGS(SkColorShader, (buffer));
    }
    SkColor     fColor;         // ignored if fInheritColor is true
    SkPMColor   fPMColor;       // cached after setContext()
    uint32_t    fFlags;         // cached after setContext()
    uint16_t    fColor16;       // cached after setContext()
    SkBool8     fInheritColor;

    // deferred allocation, used for asABitmap()
    mutable SkPixelRef* fAsABitmapPixelRef;

    typedef SkShader INHERITED;
};

#endif
