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

#ifndef SkAvoidXfermode_DEFINED
#define SkAvoidXfermode_DEFINED

#include "SkXfermode.h"

/** \class SkAvoidXfermode

    This xfermode will draw the src everywhere except on top of the specified
    color.
*/
class SkAvoidXfermode : public SkXfermode {
public:
    enum Mode {
        kAvoidColor_Mode,   //!< draw everywhere except on the opColor
        kTargetColor_Mode   //!< draw only on top of the opColor
    };

    /** This xfermode will draw the src everywhere except on top of the opColor
        or, depending on the Mode, draw only on top of the opColor.
        @param opColor  the color to avoid (or to target depending on Mode).
                        note: the alpha in opColor is ignored
        @param tolerance    How closely we compare a pixel to the opColor.
                            0 - only operate if exact match
                            255 - maximum gradation (blending) based on how
                            similar the pixel is to our opColor (max tolerance)
        @param mode If we should avoid or target the opColor
    */
    SkAvoidXfermode(SkColor opColor, U8CPU tolerance, Mode mode);

    // overrides from SkXfermode
    virtual void xfer32(SkPMColor dst[], const SkPMColor src[], int count,
                        const SkAlpha aa[]);
    virtual void xfer16(uint16_t dst[], const SkPMColor src[], int count,
                        const SkAlpha aa[]);
    virtual void xfer4444(uint16_t dst[], const SkPMColor src[], int count,
                          const SkAlpha aa[]);
    virtual void xferA8(SkAlpha dst[], const SkPMColor src[], int count,
                        const SkAlpha aa[]);

    // overrides from SkFlattenable
    virtual Factory getFactory();
    virtual void flatten(SkFlattenableWriteBuffer&);

protected:
    SkAvoidXfermode(SkFlattenableReadBuffer&);

private:
    SkColor     fOpColor;
    uint32_t    fDistMul;   // x.14
    Mode        fMode;
    
    static SkFlattenable* Create(SkFlattenableReadBuffer&);
    
    typedef SkXfermode INHERITED;
};

#endif
