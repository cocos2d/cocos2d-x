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

#ifndef SkMask_DEFINED
#define SkMask_DEFINED

#include "SkRect.h"

/** \class SkMask
    SkMask is used to describe alpha bitmaps, either 1bit, 8bit, or
    the 3-channel 3D format. These are passed to SkMaskFilter objects.
*/
struct SkMask {
    enum Format {
        kBW_Format, //!< 1bit per pixel mask (e.g. monochrome)
        kA8_Format, //!< 8bits per pixel mask (e.g. antialiasing)
        k3D_Format, //!< 3 8bit per pixl planes: alpha, mul, add

        /* The LCD formats look like this in memory:

           First, there's an A8 plane which contains the average alpha value for
           each pixel. Because of this, the LCD formats can be passed directly
           to functions which expect an A8 and everything will just work.

           After that in memory, there's a bitmap of 32-bit values which have
           been RGB order corrected for the current screen (based on the
           settings in SkFontHost at the time of renderering). The alpha value
           for each pixel is the maximum of the three alpha values.

           kHorizontalLCD_Format has an extra column of pixels on the left and right
           edges. kVerticalLCD_Format has an extra row at the top and bottom.
        */

        kHorizontalLCD_Format, //!< 4 bytes/pixel: a/r/g/b
        kVerticalLCD_Format, //!< 4 bytes/pixel: a/r/g/b
    };

    enum {
        kCountMaskFormats = kVerticalLCD_Format + 1
    };

    uint8_t*    fImage;
    SkIRect     fBounds;
    uint32_t    fRowBytes;
    Format      fFormat;

    /** Returns true if the mask is empty: i.e. it has an empty bounds.
     */
    bool isEmpty() const { return fBounds.isEmpty(); }

    /** Return the byte size of the mask, assuming only 1 plane.
        Does not account for k3D_Format. For that, use computeTotalImageSize().
        If there is an overflow of 32bits, then returns 0.
    */
    size_t computeImageSize() const;

    /** Return the byte size of the mask, taking into account
        any extra planes (e.g. k3D_Format).
        If there is an overflow of 32bits, then returns 0.
    */
    size_t computeTotalImageSize() const;

    /** Returns the address of the byte that holds the specified bit.
        Asserts that the mask is kBW_Format, and that x,y are in range.
        x,y are in the same coordiate space as fBounds.
    */
    uint8_t* getAddr1(int x, int y) const {
        SkASSERT(fFormat == kBW_Format);
        SkASSERT(fBounds.contains(x, y));
        SkASSERT(fImage != NULL);
        return fImage + ((x - fBounds.fLeft) >> 3) + (y - fBounds.fTop) * fRowBytes;
    }

    /** Returns the address of the specified byte.
        Asserts that the mask is kA8_Format, and that x,y are in range.
        x,y are in the same coordiate space as fBounds.
    */
    uint8_t* getAddr(int x, int y) const {
        SkASSERT(fFormat != kBW_Format);
        SkASSERT(fBounds.contains(x, y));
        SkASSERT(fImage != NULL);
        return fImage + x - fBounds.fLeft + (y - fBounds.fTop) * fRowBytes;
    }

    /** Return an address into the 32-bit plane of an LCD or VerticalLCD mask
        for the given position.
    */
    const uint32_t* getAddrLCD(int x, int y) const {
        SkASSERT(fFormat == kHorizontalLCD_Format || fFormat == kVerticalLCD_Format);
        SkASSERT(fImage != NULL);

        return reinterpret_cast<const uint32_t*>(fImage + SkAlign4(fRowBytes * fBounds.height())) +
               x - fBounds.fLeft + (y - fBounds.fTop) * rowWordsLCD();
    }

    /** Return the number of 32-bit words in a row of the 32-bit plane of an
       LCD or VerticalLCD mask.
    */
    unsigned rowWordsLCD() const {
        SkASSERT(fFormat == kHorizontalLCD_Format || fFormat == kVerticalLCD_Format);
        if (fFormat == kHorizontalLCD_Format)
            return fBounds.width() + 2;
        else
            return fBounds.width();
    }

    static uint8_t* AllocImage(size_t bytes);
    static void FreeImage(void* image);
    
    enum CreateMode {
        kJustComputeBounds_CreateMode,      //!< compute bounds and return
        kJustRenderImage_CreateMode,        //!< render into preallocate mask
        kComputeBoundsAndRenderImage_CreateMode  //!< compute bounds, alloc image and render into it
    };

    static bool FormatIsLCD(Format fm) {
        return kHorizontalLCD_Format == fm || kVerticalLCD_Format == fm;
    }
};

#endif

