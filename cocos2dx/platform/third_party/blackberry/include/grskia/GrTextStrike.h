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


#ifndef GrTextStrike_DEFINED
#define GrTextStrike_DEFINED

#include "GrAllocPool.h"
#include "GrFontScaler.h"
#include "GrTHashCache.h"
#include "GrPoint.h"
#include "GrGlyph.h"

class GrAtlasMgr;
class GrFontCache;
class GrGpu;
class GrFontPurgeListener;

/**
 *  The textcache maps a hostfontscaler instance to a dictionary of
 *  glyphid->strike
 */
class GrTextStrike {
public:
    GrTextStrike(GrFontCache*, const GrKey* fontScalerKey, GrMaskFormat,
                 GrAtlasMgr*);
    ~GrTextStrike();

    const GrKey* getFontScalerKey() const { return fFontScalerKey; }
    GrFontCache* getFontCache() const { return fFontCache; }
    GrMaskFormat getMaskFormat() const { return fMaskFormat; }

    inline GrGlyph* getGlyph(GrGlyph::PackedID, GrFontScaler*);
    bool getGlyphAtlas(GrGlyph*, GrFontScaler*);

    // testing
    int countGlyphs() const { return fCache.getArray().count(); }
    const GrGlyph* glyphAt(int index) const {
        return fCache.getArray()[index];
    }
    GrAtlas* getAtlas() const { return fAtlas; }

public:
    // for LRU
    GrTextStrike*   fPrev;
    GrTextStrike*   fNext;

private:
    class Key;
    GrTHashTable<GrGlyph, Key, 7> fCache;
    const GrKey* fFontScalerKey;
    GrTAllocPool<GrGlyph> fPool;

    GrFontCache*    fFontCache;
    GrAtlasMgr*     fAtlasMgr;
    GrAtlas*        fAtlas;     // linklist

    GrMaskFormat fMaskFormat;

    GrGlyph* generateGlyph(GrGlyph::PackedID packed, GrFontScaler* scaler);
    // returns true if after the purge, the strike is empty
    bool purgeAtlasAtY(GrAtlas* atlas, int yCoord);

    friend class GrFontCache;
};

class GrFontCache {
public:
    GrFontCache(GrGpu*);
    ~GrFontCache();

    inline GrTextStrike* getStrike(GrFontScaler*);

    void freeAll();

    void purgeExceptFor(GrTextStrike*);

    // testing
    int countStrikes() const { return fCache.getArray().count(); }
    const GrTextStrike* strikeAt(int index) const {
        return fCache.getArray()[index];
    }
    GrTextStrike* getHeadStrike() const { return fHead; }

#if GR_DEBUG
    void validate() const;
#else
    void validate() const {}
#endif

private:
    friend class GrFontPurgeListener;

    class Key;
    GrTHashTable<GrTextStrike, Key, 8> fCache;
    // for LRU
    GrTextStrike* fHead;
    GrTextStrike* fTail;

    GrGpu*      fGpu;
    GrAtlasMgr* fAtlasMgr;


    GrTextStrike* generateStrike(GrFontScaler*, const Key&);
    inline void detachStrikeFromList(GrTextStrike*);
};

#endif

