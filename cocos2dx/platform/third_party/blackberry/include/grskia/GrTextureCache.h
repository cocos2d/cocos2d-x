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


#ifndef GrTextureCache_DEFINED
#define GrTextureCache_DEFINED

#include "GrTypes.h"
#include "GrTHashCache.h"

class GrTexture;

// return true if a<b, or false if b<a
//
#define RET_IF_LT_OR_GT(a, b)   \
    do {                        \
        if ((a) < (b)) {        \
            return true;        \
        }                       \
        if ((b) < (a)) {        \
            return false;       \
        }                       \
    } while (0)

/**
 *  Helper class for GrTextureCache, the Key is used to identify src data for
 *  a texture. It is identified by 2 32bit data fields which can hold any
 *  data (uninterpreted by the cache) and a width/height.
 */
class GrTextureKey {
public:
    enum {
        kHashBits   = 7,
        kHashCount  = 1 << kHashBits,
        kHashMask   = kHashCount - 1
    };

    GrTextureKey(uint32_t p0, uint32_t p1, uint16_t width, uint16_t height) {
        fP0 = p0;
        fP1 = p1;
        fP2 = width | (height << 16);
        GR_DEBUGCODE(fHashIndex = -1);
    }

    GrTextureKey(const GrTextureKey& src) {
        fP0 = src.fP0;
        fP1 = src.fP1;
        fP2 = src.fP2;
        finalize(src.fPrivateBits);
    }

    //!< returns hash value [0..kHashMask] for the key
    int hashIndex() const { return fHashIndex; }

    friend bool operator==(const GrTextureKey& a, const GrTextureKey& b) {
        GR_DEBUGASSERT(-1 != a.fHashIndex && -1 != b.fHashIndex);
        return a.fP0 == b.fP0 && a.fP1 == b.fP1 && a.fP2 == b.fP2 &&
               a.fPrivateBits == b.fPrivateBits;
    }

    friend bool operator!=(const GrTextureKey& a, const GrTextureKey& b) {
        GR_DEBUGASSERT(-1 != a.fHashIndex && -1 != b.fHashIndex);
        return !(a == b);
    }

    friend bool operator<(const GrTextureKey& a, const GrTextureKey& b) {
        RET_IF_LT_OR_GT(a.fP0, b.fP0);
        RET_IF_LT_OR_GT(a.fP1, b.fP1);
        RET_IF_LT_OR_GT(a.fP2, b.fP2);
        return a.fPrivateBits < b.fPrivateBits;
    }

private:
    void finalize(uint32_t privateBits) {
        fPrivateBits = privateBits;
        this->computeHashIndex();
    }

    uint16_t width() const { return fP2 & 0xffff; }
    uint16_t height() const { return (fP2 >> 16); }

    uint32_t getPrivateBits() const { return fPrivateBits; }

    static uint32_t rol(uint32_t x) {
        return (x >> 24) | (x << 8);
    }
    static uint32_t ror(uint32_t x) {
        return (x >> 8) | (x << 24);
    }
    static uint32_t rohalf(uint32_t x) {
        return (x >> 16) | (x << 16);
    }

    void computeHashIndex() {
        uint32_t hash = fP0 ^ rol(fP1) ^ ror(fP2) ^ rohalf(fPrivateBits);
        // this way to mix and reduce hash to its index may have to change
        // depending on how many bits we allocate to the index
        hash ^= hash >> 16;
        hash ^= hash >> 8;
        fHashIndex = hash & kHashMask;
    }

    uint32_t    fP0;
    uint32_t    fP1;
    uint32_t    fP2;
    uint32_t    fPrivateBits;

    // this is computed from the fP... fields
    int         fHashIndex;

    friend class GrContext;
};

///////////////////////////////////////////////////////////////////////////////

class GrTextureEntry {
public:
    GrTexture* texture() const { return fTexture; }
    const GrTextureKey& key() const { return fKey; }

#if GR_DEBUG
    GrTextureEntry* next() const { return fNext; }
    GrTextureEntry* prev() const { return fPrev; }
#endif

#if GR_DEBUG
    void validate() const;
#else
    void validate() const {}
#endif

private:
    GrTextureEntry(const GrTextureKey& key, GrTexture* texture);
    ~GrTextureEntry();

    bool isLocked() const { return fLockCount != 0; }
    void lock() { ++fLockCount; }
    void unlock() {
        GrAssert(fLockCount > 0);
        --fLockCount;
    }

    GrTextureKey    fKey;
    GrTexture*      fTexture;

    // track if we're in use, used when we need to purge
    // we only purge unlocked entries
    int fLockCount;

    // we're a dlinklist
    GrTextureEntry* fPrev;
    GrTextureEntry* fNext;

    friend class GrTextureCache;
};

///////////////////////////////////////////////////////////////////////////////

#include "GrTHashCache.h"

/**
 *  Cache of GrTexture objects.
 *
 *  These have a corresponding GrTextureKey, built from 96bits identifying the
 *  texture/bitmap.
 *
 *  The cache stores the entries in a double-linked list, which is its LRU.
 *  When an entry is "locked" (i.e. given to the caller), it is moved to the
 *  head of the list. If/when we must purge some of the entries, we walk the
 *  list backwards from the tail, since those are the least recently used.
 *
 *  For fast searches, we maintain a sorted array (based on the GrTextureKey)
 *  which we can bsearch. When a new entry is added, it is inserted into this
 *  array.
 *
 *  For even faster searches, a hash is computed from the Key. If there is
 *  a collision between two keys with the same hash, we fall back on the
 *  bsearch, and update the hash to reflect the most recent Key requested.
 */
class GrTextureCache {
public:
    GrTextureCache(int maxCount, size_t maxBytes);
    ~GrTextureCache();

    /**
     *  Return the current texture cache limits.
     *
     *  @param maxTextures If non-null, returns maximum number of textures that
     *                     can be held in the cache.
     *  @param maxTextureBytes If non-null, returns maximum number of bytes of
     *                         texture memory that can be held in the cache.
     */
    void getLimits(int* maxTextures, size_t* maxTextureBytes) const;

    /**
     *  Specify the texture cache limits. If the current cache exceeds either
     *  of these, it will be purged (LRU) to keep the cache within these limits.
     *
     *  @param maxTextures The maximum number of textures that can be held in
     *                     the cache.
     *  @param maxTextureBytes The maximum number of bytes of texture memory
     *                         that can be held in the cache.
     */
    void setLimits(int maxTextures, size_t maxTextureBytes);

    /**
     *  Search for an entry with the same Key. If found, "lock" it and return it.
     *  If not found, return null.
     */
    GrTextureEntry* findAndLock(const GrTextureKey&);

    /**
     *  Create a new entry, based on the specified key and texture, and return
     *  its "locked" entry.
     *
     *  Ownership of the texture is transferred to the Entry, which will unref()
     *  it when we are purged or deleted.
     */
    GrTextureEntry* createAndLock(const GrTextureKey&, GrTexture*);

    /**
     * Detach removes an entry from the cache. This prevents the entry from
     * being found by a subsequent findAndLock() until it is reattached. The
     * entry still counts against the cache's budget and should be reattached
     * when exclusive access is no longer needed.
     */
    void detach(GrTextureEntry*);

    /**
     * Reattaches a texture to the cache and unlocks it. Allows it to be found
     * by a subsequent findAndLock or be purged (provided its lock count is
     * now 0.)
     */
    void reattachAndUnlock(GrTextureEntry*);

    /**
     *  When done with an entry, call unlock(entry) on it, which returns it to
     *  a purgable state.
     */
    void unlock(GrTextureEntry*);

    void removeAll();

#if GR_DEBUG
    void validate() const;
#else
    void validate() const {}
#endif

private:
    void internalDetach(GrTextureEntry*, bool);
    void attachToHead(GrTextureEntry*, bool);
    void purgeAsNeeded();   // uses kFreeTexture_DeleteMode

    class Key;
    GrTHashTable<GrTextureEntry, Key, 8> fCache;

    // manage the dlink list
    GrTextureEntry* fHead;
    GrTextureEntry* fTail;

    // our budget, used in purgeAsNeeded()
    int fMaxCount;
    size_t fMaxBytes;

    // our current stats, related to our budget
    int fEntryCount;
    size_t fEntryBytes;
    int fClientDetachedCount;
    size_t fClientDetachedBytes;
};

///////////////////////////////////////////////////////////////////////////////

#if GR_DEBUG
    class GrAutoTextureCacheValidate {
    public:
        GrAutoTextureCacheValidate(GrTextureCache* cache) : fCache(cache) {
            cache->validate();
        }
        ~GrAutoTextureCacheValidate() {
            fCache->validate();
        }
    private:
        GrTextureCache* fCache;
    };
#else
    class GrAutoTextureCacheValidate {
    public:
        GrAutoTextureCacheValidate(GrTextureCache*) {}
    };
#endif

#endif

