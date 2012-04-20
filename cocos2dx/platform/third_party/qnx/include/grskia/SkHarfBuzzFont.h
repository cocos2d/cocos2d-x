/*
 * Copyright (c) 2009, Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SkHarfBuzzFont_DEFINED
#define SkHarfBuzzFont_DEFINED

extern "C" {
#include "harfbuzz-shaper.h"
//#include "harfbuzz-unicode.h"
}

#include "SkTypes.h"

class SkPaint;
class SkTypeface;

class SkHarfBuzzFont {
public:
    /** The subclass returns the typeface for this font, or NULL
     */
    virtual SkTypeface* getTypeface() const = 0;
    /** The subclass sets the text related attributes of the paint.
        e.g. textSize, typeface, textSkewX, etc.
        All of the attributes that could effect how the text is measured.
        Color information (e.g. color, xfermode, shader, etc.) are not required.
     */
    virtual void setupPaint(SkPaint*) const = 0;
    
    /** Implementation of HB_GetFontTableFunc, using SkHarfBuzzFont* as
        the first parameter.
     */
    static HB_Error GetFontTableFunc(void* skharfbuzzfont, const HB_Tag tag,
                                     HB_Byte* buffer, HB_UInt* len);

    static const HB_FontClass& GetFontClass();
};

#endif

