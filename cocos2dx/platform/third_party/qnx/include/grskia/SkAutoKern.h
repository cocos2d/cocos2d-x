/* libs/graphics/sgl/SkAutoKern.h
**
** Copyright 2006, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License"); 
** you may not use this file except in compliance with the License. 
** You may obtain a copy of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** Unless required by applicable law or agreed to in writing, software 
** distributed under the License is distributed on an "AS IS" BASIS, 
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
** See the License for the specific language governing permissions and 
** limitations under the License.
*/

#ifndef SkAutoKern_DEFINED
#define SkAutoKern_DEFINED

#include "SkScalerContext.h"

#define SkAutoKern_AdjustF(prev, next)    (((next) - (prev) + 32) >> 6 << 16)
#define SkAutoKern_AdjustS(prev, next)    SkIntToScalar(((next) - (prev) + 32) >> 6)

/* this is a helper class to perform auto-kerning
 * the adjust() method returns a SkFixed corresponding
 * to a +1/0/-1 pixel adjustment
 */

class SkAutoKern {
public:
    SkAutoKern() : fPrevRsbDelta(0) {}

    SkFixed  adjust(const SkGlyph&  glyph) 
    {
//        if (SkAbs32(glyph.fLsbDelta) > 47 || SkAbs32(glyph.fRsbDelta) > 47)
//            printf("------- %d> L %d R %d\n", glyph.f_GlyphID, glyph.fLsbDelta, glyph.fRsbDelta);

#if 0
        int  distort = fPrevRsbDelta - glyph.fLsbDelta;

        fPrevRsbDelta = glyph.fRsbDelta;

        if (distort >= 32)
            return -SK_Fixed1;
        else if (distort < -32)
            return +SK_Fixed1;
        else
            return 0;
#else
        SkFixed adjust = SkAutoKern_AdjustF(fPrevRsbDelta, glyph.fLsbDelta);
        fPrevRsbDelta = glyph.fRsbDelta;
        return adjust;
#endif
    }
private:
    int   fPrevRsbDelta;
};

#endif

