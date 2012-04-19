/*
    Copyright 2010 Google Inc.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

         http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
 */


#ifndef GrGlyph_DEFINED
#define GrGlyph_DEFINED

#include "GrPath.h"
#include "GrRect.h"

class GrAtlas;

/*  Need this to be quad-state:
    - complete w/ image
    - just metrics
    - failed to get image, but has metrics
    - failed to get metrics
 */
struct GrGlyph {
    typedef uint32_t PackedID;

    GrAtlas*    fAtlas;
    GrPath*     fPath;
    PackedID    fPackedID;
    GrIRect16   fBounds;
    GrIPoint16  fAtlasLocation;

    void init(GrGlyph::PackedID packed, const GrIRect& bounds) {
        fAtlas = NULL;
        fPath = NULL;
        fPackedID = packed;
        fBounds.set(bounds);
        fAtlasLocation.set(0, 0);
    }
    
    void free() {
        if (fPath) {
            delete fPath;
            fPath = NULL;
        }
    }
    
    int width() const { return fBounds.width(); }
    int height() const { return fBounds.height(); }
    bool isEmpty() const { return fBounds.isEmpty(); }
    uint16_t glyphID() const { return UnpackID(fPackedID); }

    ///////////////////////////////////////////////////////////////////////////
    
    static inline unsigned ExtractSubPixelBitsFromFixed(GrFixed pos) {
        // two most significant fraction bits from fixed-point
        return (pos >> 14) & 3;
    }
    
    static inline PackedID Pack(uint16_t glyphID, GrFixed x, GrFixed y) {
        x = ExtractSubPixelBitsFromFixed(x);
        y = ExtractSubPixelBitsFromFixed(y);
        return (x << 18) | (y << 16) | glyphID;
    }
    
    static inline GrFixed UnpackFixedX(PackedID packed) {
        return ((packed >> 18) & 3) << 14;
    }
    
    static inline GrFixed UnpackFixedY(PackedID packed) {
        return ((packed >> 16) & 3) << 14;
    }
    
    static inline uint16_t UnpackID(PackedID packed) {
        return (uint16_t)packed;
    }
};


#endif

