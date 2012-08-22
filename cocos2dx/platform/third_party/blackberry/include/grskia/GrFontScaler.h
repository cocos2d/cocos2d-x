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


#ifndef GrFontScaler_DEFINED
#define GrFontScaler_DEFINED

#include "GrGlyph.h"
#include "GrKey.h"

class SkPath;

/**
 *  This is a virtual base class which Gr's interface to the host platform's
 *  font scaler.
 *
 *  The client is responsible for subclassing, and instantiating this. The
 *  instance is create for a specific font+size+matrix.
 */
class GrFontScaler : public GrRefCnt {
public:
    virtual const GrKey* getKey() = 0;
    virtual GrMaskFormat getMaskFormat() = 0;
    virtual bool getPackedGlyphBounds(GrGlyph::PackedID, GrIRect* bounds) = 0;
    virtual bool getPackedGlyphImage(GrGlyph::PackedID, int width, int height,
                                     int rowBytes, void* image) = 0;
    virtual bool getGlyphPath(uint16_t glyphID, SkPath*) = 0;
};

#endif

