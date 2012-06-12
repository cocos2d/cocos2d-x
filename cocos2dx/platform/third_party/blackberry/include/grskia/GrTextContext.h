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


#ifndef GrTextContext_DEFINED
#define GrTextContext_DEFINED

#include "GrGlyph.h"
#include "GrPaint.h"
#include "GrMatrix.h"

struct GrGpuTextVertex;
class GrContext;
class GrTextStrike;
class GrFontScaler;
class GrDrawTarget;

class GrTextContext {
public:
    GrTextContext(GrContext*,
                  const GrPaint& paint,
                  const GrMatrix* extMatrix = NULL);
    ~GrTextContext();

    void drawPackedGlyph(GrGlyph::PackedID, GrFixed left, GrFixed top,
                         GrFontScaler*);

    void flush();   // optional; automatically called by destructor

private:
    GrPaint         fPaint;
    GrVertexLayout  fVertexLayout;
    GrContext*      fContext;
    GrDrawTarget*   fDrawTarget;

    GrMatrix        fExtMatrix;
    GrFontScaler*   fScaler;
    GrTextStrike*   fStrike;

    inline void flushGlyphs();
    void setupDrawTarget();

    enum {
        kMinRequestedGlyphs      = 1,
        kDefaultRequestedGlyphs  = 64,
        kMinRequestedVerts       = kMinRequestedGlyphs * 4,
        kDefaultRequestedVerts   = kDefaultRequestedGlyphs * 4,
    };

    GrGpuTextVertex* fVertices;

    int32_t     fMaxVertices;
    GrTexture*  fCurrTexture;
    int         fCurrVertex;

    GrIRect     fClipRect;
    GrMatrix    fOrigViewMatrix;    // restore previous viewmatrix
};

#endif


