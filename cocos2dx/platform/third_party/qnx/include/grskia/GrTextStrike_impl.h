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


#ifndef GrTextStrike_impl_DEFINED
#define GrTextStrike_impl_DEFINED

class GrFontCache::Key {
public:
    Key(GrFontScaler* scaler) {
        fFontScalerKey = scaler->getKey();
    }
    
    uint32_t getHash() const { return fFontScalerKey->getHash(); }
    
    static bool LT(const GrTextStrike& strike, const Key& key) {
        return *strike.getFontScalerKey() < *key.fFontScalerKey;
    }
    static bool EQ(const GrTextStrike& strike, const Key& key) {
        return *strike.getFontScalerKey() == *key.fFontScalerKey;
    }
    
private:
    const GrKey* fFontScalerKey;
};

void GrFontCache::detachStrikeFromList(GrTextStrike* strike) {
    if (strike->fPrev) {
        GrAssert(fHead != strike);
        strike->fPrev->fNext = strike->fNext;
    } else {
        GrAssert(fHead == strike);
        fHead = strike->fNext;
    }

    if (strike->fNext) {
        GrAssert(fTail != strike);
        strike->fNext->fPrev = strike->fPrev;
    } else {
        GrAssert(fTail == strike);
        fTail = strike->fPrev;
    }
}

GrTextStrike* GrFontCache::getStrike(GrFontScaler* scaler) {
    this->validate();
    
    Key key(scaler);
    GrTextStrike* strike = fCache.find(key);
    if (NULL == strike) {
        strike = this->generateStrike(scaler, key);
    } else if (strike->fPrev) {
        // Need to put the strike at the head of its dllist, since that is how
        // we age the strikes for purging (we purge from the back of the list
        this->detachStrikeFromList(strike);
        // attach at the head
        fHead->fPrev = strike;
        strike->fNext = fHead;
        strike->fPrev = NULL;
        fHead = strike;
    }

    this->validate();
    return strike;
}

///////////////////////////////////////////////////////////////////////////////

/**
 *  This Key just wraps a glyphID, and matches the protocol need for
 *  GrTHashTable
 */
class GrTextStrike::Key {
public:
    Key(GrGlyph::PackedID id) : fPackedID(id) {}
    
    uint32_t getHash() const { return fPackedID; }
    
    static bool LT(const GrGlyph& glyph, const Key& key) {
        return glyph.fPackedID < key.fPackedID;
    }
    static bool EQ(const GrGlyph& glyph, const Key& key) {
        return glyph.fPackedID == key.fPackedID;
    }
    
private:
    GrGlyph::PackedID fPackedID;
};

GrGlyph* GrTextStrike::getGlyph(GrGlyph::PackedID packed,
                                GrFontScaler* scaler) {
    GrGlyph* glyph = fCache.find(packed);
    if (NULL == glyph) {
        glyph = this->generateGlyph(packed, scaler);
    }
    return glyph;
}

#endif

