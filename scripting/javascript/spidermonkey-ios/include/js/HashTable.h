/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sw=4 et tw=99 ft=cpp:
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef jshashtable_h_
#define jshashtable_h_

#include "TemplateLib.h"
#include "Utility.h"

namespace js {

class TempAllocPolicy;

/* Integral types for all hash functions. */
typedef uint32_t HashNumber;

/*****************************************************************************/

namespace detail {

template <class T, class HashPolicy, class AllocPolicy>
class HashTable;

template <class T>
class HashTableEntry {
    HashNumber keyHash;

    typedef typename tl::StripConst<T>::result NonConstT;

    static const HashNumber sFreeKey = 0;
    static const HashNumber sRemovedKey = 1;
    static const HashNumber sCollisionBit = 1;

    template <class, class, class> friend class HashTable;

    static bool isLiveHash(HashNumber hash)
    {
        return hash > sRemovedKey;
    }

  public:
    HashTableEntry() : keyHash(0), t() {}
    HashTableEntry(MoveRef<HashTableEntry> rhs) : keyHash(rhs->keyHash), t(Move(rhs->t)) { }
    void operator=(const HashTableEntry &rhs) { keyHash = rhs.keyHash; t = rhs.t; }
    void operator=(MoveRef<HashTableEntry> rhs) { keyHash = rhs->keyHash; t = Move(rhs->t); }

    NonConstT t;

    bool isFree() const           { return keyHash == sFreeKey; }
    void setFree()                { keyHash = sFreeKey; t = T(); }
    bool isRemoved() const        { return keyHash == sRemovedKey; }
    void setRemoved()             { keyHash = sRemovedKey; t = T(); }
    bool isLive() const           { return isLiveHash(keyHash); }
    void setLive(HashNumber hn)   { JS_ASSERT(isLiveHash(hn)); keyHash = hn; }

    void setCollision()           { JS_ASSERT(isLive()); keyHash |= sCollisionBit; }
    void setCollision(HashNumber collisionBit) {
        JS_ASSERT(isLive()); keyHash |= collisionBit;
    }
    void unsetCollision()         { keyHash &= ~sCollisionBit; }
    bool hasCollision() const     { return keyHash & sCollisionBit; }
    bool matchHash(HashNumber hn) { return (keyHash & ~sCollisionBit) == hn; }
    HashNumber getKeyHash() const { JS_ASSERT(!hasCollision()); return keyHash; }
};

/*
 * js::detail::HashTable is an implementation detail of the js::HashMap and
 * js::HashSet templates. For js::Hash{Map,Set} API documentation and examples,
 * skip to the end of the detail namespace.
 */

/* Reusable implementation of HashMap and HashSet. */
template <class T, class HashPolicy, class AllocPolicy>
class HashTable : private AllocPolicy
{
    typedef typename tl::StripConst<T>::result NonConstT;
    typedef typename HashPolicy::KeyType Key;
    typedef typename HashPolicy::Lookup Lookup;

  public:
    typedef HashTableEntry<T> Entry;

    /*
     * A nullable pointer to a hash table element. A Ptr |p| can be tested
     * either explicitly |if (p.found()) p->...| or using boolean conversion
     * |if (p) p->...|. Ptr objects must not be used after any mutating hash
     * table operations unless |generation()| is tested.
     */
    class Ptr
    {
        friend class HashTable;
        typedef void (Ptr::* ConvertibleToBool)();
        void nonNull() {}

        Entry *entry;

      protected:
        Ptr(Entry &entry) : entry(&entry) {}

      public:
        /* Leaves Ptr uninitialized. */
        Ptr() {
#ifdef DEBUG
            entry = (Entry *)0xbad;
#endif
        }

        bool found() const                    { return entry->isLive(); }
        operator ConvertibleToBool() const    { return found() ? &Ptr::nonNull : 0; }
        bool operator==(const Ptr &rhs) const { JS_ASSERT(found() && rhs.found()); return entry == rhs.entry; }
        bool operator!=(const Ptr &rhs) const { return !(*this == rhs); }

        T &operator*() const                  { return entry->t; }
        T *operator->() const                 { return &entry->t; }
    };

    /* A Ptr that can be used to add a key after a failed lookup. */
    class AddPtr : public Ptr
    {
        friend class HashTable;
        HashNumber keyHash;
        DebugOnly<uint64_t> mutationCount;

        AddPtr(Entry &entry, HashNumber hn) : Ptr(entry), keyHash(hn) {}
      public:
        /* Leaves AddPtr uninitialized. */
        AddPtr() {}
    };

    /*
     * A collection of hash table entries. The collection is enumerated by
     * calling |front()| followed by |popFront()| as long as |!empty()|. As
     * with Ptr/AddPtr, Range objects must not be used after any mutating hash
     * table operation unless the |generation()| is tested.
     */
    class Range
    {
      protected:
        friend class HashTable;

        Range(Entry *c, Entry *e) : cur(c), end(e), validEntry(true) {
            while (cur < end && !cur->isLive())
                ++cur;
        }

        Entry *cur, *end;
        DebugOnly<bool> validEntry;

      public:
        Range() : cur(NULL), end(NULL), validEntry(false) {}

        bool empty() const {
            return cur == end;
        }

        T &front() const {
            JS_ASSERT(validEntry);
            JS_ASSERT(!empty());
            return cur->t;
        }

        void popFront() {
            JS_ASSERT(!empty());
            while (++cur < end && !cur->isLive())
                continue;
            validEntry = true;
        }
    };

    /*
     * A Range whose lifetime delimits a mutating enumeration of a hash table.
     * Since rehashing when elements were removed during enumeration would be
     * bad, it is postponed until |endEnumeration()| is called. If
     * |endEnumeration()| is not called before an Enum's constructor, it will
     * be called automatically. Since |endEnumeration()| touches the hash
     * table, the user must ensure that the hash table is still alive when this
     * happens.
     */
    class Enum : public Range
    {
        friend class HashTable;

        HashTable &table;
        bool rekeyed;
        bool removed;

        /* Not copyable. */
        Enum(const Enum &);
        void operator=(const Enum &);

      public:
        template<class Map> explicit
        Enum(Map &map) : Range(map.all()), table(map.impl), rekeyed(false), removed(false) {}

        /*
         * Removes the |front()| element from the table, leaving |front()|
         * invalid until the next call to |popFront()|. For example:
         *
         *   HashSet<int> s;
         *   for (HashSet<int>::Enum e(s); !e.empty(); e.popFront())
         *     if (e.front() == 42)
         *       e.removeFront();
         */
        void removeFront() {
            table.remove(*this->cur);
            removed = true;
            this->validEntry = false;
        }

        /*
         * Removes the |front()| element and re-inserts it into the table with
         * a new key at the new Lookup position.  |front()| is invalid after
         * this operation until the next call to |popFront()|.
         */
        void rekeyFront(const Lookup &l, const Key &k) {
            JS_ASSERT(&k != &HashPolicy::getKey(this->cur->t));
            if (match(*this->cur, l))
                return;
            typename HashTableEntry<T>::NonConstT t = this->cur->t;
            HashPolicy::setKey(t, const_cast<Key &>(k));
            table.remove(*this->cur);
            table.putNewInfallible(l, t);
            rekeyed = true;
            this->validEntry = false;
        }

        void rekeyFront(const Key &k) {
            rekeyFront(k, k);
        }

        /* Potentially rehashes the table. */
        ~Enum() {
            if (rekeyed)
                table.checkOverRemoved();
            if (removed)
                table.checkUnderloaded();
        }
    };

  private:
    uint32_t    hashShift;      /* multiplicative hash shift */
    uint32_t    entryCount;     /* number of entries in table */
    uint32_t    gen;            /* entry storage generation number */
    uint32_t    removedCount;   /* removed entry sentinels in table */
    Entry       *table;         /* entry storage */

    void setTableSizeLog2(unsigned sizeLog2) {
        hashShift = sHashBits - sizeLog2;
    }

#ifdef DEBUG
    mutable struct Stats {
        uint32_t        searches;       /* total number of table searches */
        uint32_t        steps;          /* hash chain links traversed */
        uint32_t        hits;           /* searches that found key */
        uint32_t        misses;         /* searches that didn't find key */
        uint32_t        addOverRemoved; /* adds that recycled a removed entry */
        uint32_t        removes;        /* calls to remove */
        uint32_t        removeFrees;    /* calls to remove that freed the entry */
        uint32_t        grows;          /* table expansions */
        uint32_t        shrinks;        /* table contractions */
        uint32_t        compresses;     /* table compressions */
        uint32_t        rehashes;       /* tombstone decontaminations */
    } stats;
#   define METER(x) x
#else
#   define METER(x)
#endif

    friend class js::ReentrancyGuard;
    mutable DebugOnly<bool> entered;
    DebugOnly<uint64_t>     mutationCount;

    /* The default initial capacity is 16, but you can ask for as small as 4. */
    static const unsigned sMinSizeLog2  = 2;
    static const unsigned sMinSize      = 1 << sMinSizeLog2;
    static const unsigned sDefaultInitSizeLog2 = 4;
  public:
    static const unsigned sDefaultInitSize = 1 << sDefaultInitSizeLog2;
  private:
    static const unsigned sMaxInit      = JS_BIT(23);
    static const unsigned sMaxCapacity  = JS_BIT(24);
    static const unsigned sHashBits     = tl::BitSize<HashNumber>::result;
    static const uint8_t  sMinAlphaFrac = 64;  /* (0x100 * .25) taken from jsdhash.h */
    static const uint8_t  sMaxAlphaFrac = 192; /* (0x100 * .75) taken from jsdhash.h */
    static const uint8_t  sInvMaxAlpha  = 171; /* (ceil(0x100 / .75) >> 1) */
    static const HashNumber sGoldenRatio  = 0x9E3779B9U;       /* taken from jsdhash.h */
    static const HashNumber sFreeKey = Entry::sFreeKey;
    static const HashNumber sRemovedKey = Entry::sRemovedKey;
    static const HashNumber sCollisionBit = Entry::sCollisionBit;

    static void staticAsserts()
    {
        /* Rely on compiler "constant overflow warnings". */
        JS_STATIC_ASSERT(((sMaxInit * sInvMaxAlpha) >> 7) < sMaxCapacity);
        JS_STATIC_ASSERT((sMaxCapacity * sInvMaxAlpha) <= UINT32_MAX);
        JS_STATIC_ASSERT((sMaxCapacity * sizeof(Entry)) <= UINT32_MAX);
    }

    static bool isLiveHash(HashNumber hash)
    {
        return Entry::isLiveHash(hash);
    }

    static HashNumber prepareHash(const Lookup& l)
    {
        HashNumber keyHash = HashPolicy::hash(l);

        /* Improve keyHash distribution. */
        keyHash *= sGoldenRatio;

        /* Avoid reserved hash codes. */
        if (!isLiveHash(keyHash))
            keyHash -= (sRemovedKey + 1);
        return keyHash & ~sCollisionBit;
    }

    static Entry *createTable(AllocPolicy &alloc, uint32_t capacity)
    {
        Entry *newTable = (Entry *)alloc.malloc_(capacity * sizeof(Entry));
        if (!newTable)
            return NULL;
        for (Entry *e = newTable, *end = e + capacity; e < end; ++e)
            new(e) Entry();
        return newTable;
    }

    static void destroyTable(AllocPolicy &alloc, Entry *oldTable, uint32_t capacity)
    {
        for (Entry *e = oldTable, *end = e + capacity; e < end; ++e)
            e->~Entry();
        alloc.free_(oldTable);
    }

  public:
    HashTable(AllocPolicy ap)
      : AllocPolicy(ap),
        hashShift(sHashBits),
        entryCount(0),
        gen(0),
        removedCount(0),
        table(NULL),
        entered(false),
        mutationCount(0)
    {}

    MOZ_WARN_UNUSED_RESULT bool init(uint32_t length)
    {
        /* Make sure that init isn't called twice. */
        JS_ASSERT(table == NULL);

        /*
         * Correct for sMaxAlphaFrac such that the table will not resize
         * when adding 'length' entries.
         */
        if (length > sMaxInit) {
            this->reportAllocOverflow();
            return false;
        }
        uint32_t capacity = (length * sInvMaxAlpha) >> 7;

        if (capacity < sMinSize)
            capacity = sMinSize;

        /* FIXME: use JS_CEILING_LOG2 when PGO stops crashing (bug 543034). */
        uint32_t roundUp = sMinSize, roundUpLog2 = sMinSizeLog2;
        while (roundUp < capacity) {
            roundUp <<= 1;
            ++roundUpLog2;
        }

        capacity = roundUp;
        JS_ASSERT(capacity <= sMaxCapacity);

        table = createTable(*this, capacity);
        if (!table)
            return false;

        setTableSizeLog2(roundUpLog2);
        METER(memset(&stats, 0, sizeof(stats)));
        return true;
    }

    bool initialized() const
    {
        return !!table;
    }

    ~HashTable()
    {
        if (table)
            destroyTable(*this, table, capacity());
    }

  private:
    static HashNumber hash1(HashNumber hash0, uint32_t shift) {
        return hash0 >> shift;
    }

    struct DoubleHash {
        HashNumber h2;
        HashNumber sizeMask;
    };

    DoubleHash hash2(HashNumber curKeyHash, uint32_t hashShift) const {
        unsigned sizeLog2 = sHashBits - hashShift;
        DoubleHash dh = {
            ((curKeyHash << sizeLog2) >> hashShift) | 1,
            (HashNumber(1) << sizeLog2) - 1
        };
        return dh;
    }

    static HashNumber applyDoubleHash(HashNumber h1, const DoubleHash &dh) {
        return (h1 - dh.h2) & dh.sizeMask;
    }

    bool overloaded() {
        return entryCount + removedCount >= ((sMaxAlphaFrac * capacity()) >> 8);
    }

    bool underloaded() {
        uint32_t tableCapacity = capacity();
        return tableCapacity > sMinSize &&
               entryCount <= ((sMinAlphaFrac * tableCapacity) >> 8);
    }

    static bool match(Entry &e, const Lookup &l) {
        return HashPolicy::match(HashPolicy::getKey(e.t), l);
    }

    Entry &lookup(const Lookup &l, HashNumber keyHash, unsigned collisionBit) const
    {
        JS_ASSERT(isLiveHash(keyHash));
        JS_ASSERT(!(keyHash & sCollisionBit));
        JS_ASSERT(collisionBit == 0 || collisionBit == sCollisionBit);
        JS_ASSERT(table);
        METER(stats.searches++);

        /* Compute the primary hash address. */
        HashNumber h1 = hash1(keyHash, hashShift);
        Entry *entry = &table[h1];

        /* Miss: return space for a new entry. */
        if (entry->isFree()) {
            METER(stats.misses++);
            return *entry;
        }

        /* Hit: return entry. */
        if (entry->matchHash(keyHash) && match(*entry, l)) {
            METER(stats.hits++);
            return *entry;
        }

        /* Collision: double hash. */
        DoubleHash dh = hash2(keyHash, hashShift);

        /* Save the first removed entry pointer so we can recycle later. */
        Entry *firstRemoved = NULL;

        while(true) {
            if (JS_UNLIKELY(entry->isRemoved())) {
                if (!firstRemoved)
                    firstRemoved = entry;
            } else {
                entry->setCollision(collisionBit);
            }

            METER(stats.steps++);
            h1 = applyDoubleHash(h1, dh);

            entry = &table[h1];
            if (entry->isFree()) {
                METER(stats.misses++);
                return firstRemoved ? *firstRemoved : *entry;
            }

            if (entry->matchHash(keyHash) && match(*entry, l)) {
                METER(stats.hits++);
                return *entry;
            }
        }
    }

    /*
     * This is a copy of lookup hardcoded to the assumptions:
     *   1. the lookup is a lookupForAdd
     *   2. the key, whose |keyHash| has been passed is not in the table,
     *   3. no entries have been removed from the table.
     * This specialized search avoids the need for recovering lookup values
     * from entries, which allows more flexible Lookup/Key types.
     */
    Entry &findFreeEntry(HashNumber keyHash)
    {
        JS_ASSERT(!(keyHash & sCollisionBit));
        JS_ASSERT(table);
        METER(stats.searches++);

        /* N.B. the |keyHash| has already been distributed. */

        /* Compute the primary hash address. */
        HashNumber h1 = hash1(keyHash, hashShift);
        Entry *entry = &table[h1];

        /* Miss: return space for a new entry. */
        if (!entry->isLive()) {
            METER(stats.misses++);
            return *entry;
        }

        /* Collision: double hash. */
        DoubleHash dh = hash2(keyHash, hashShift);

        while(true) {
            JS_ASSERT(!entry->isRemoved());
            entry->setCollision();

            METER(stats.steps++);
            h1 = applyDoubleHash(h1, dh);

            entry = &table[h1];
            if (!entry->isLive()) {
                METER(stats.misses++);
                return *entry;
            }
        }
    }

    enum RebuildStatus { NotOverloaded, Rehashed, RehashFailed };

    RebuildStatus changeTableSize(int deltaLog2)
    {
        /* Look, but don't touch, until we succeed in getting new entry store. */
        Entry *oldTable = table;
        uint32_t oldCap = capacity();
        uint32_t newLog2 = sHashBits - hashShift + deltaLog2;
        uint32_t newCapacity = JS_BIT(newLog2);
        if (newCapacity > sMaxCapacity) {
            this->reportAllocOverflow();
            return RehashFailed;
        }

        Entry *newTable = createTable(*this, newCapacity);
        if (!newTable)
            return RehashFailed;

        /* We can't fail from here on, so update table parameters. */
        setTableSizeLog2(newLog2);
        removedCount = 0;
        gen++;
        table = newTable;

        /* Copy only live entries, leaving removed ones behind. */
        for (Entry *src = oldTable, *end = src + oldCap; src < end; ++src) {
            if (src->isLive()) {
                src->unsetCollision();
                findFreeEntry(src->getKeyHash()) = Move(*src);
            }
        }

        destroyTable(*this, oldTable, oldCap);
        return Rehashed;
    }

    RebuildStatus checkOverloaded()
    {
        if (!overloaded())
            return NotOverloaded;

        /* Compress if a quarter or more of all entries are removed. */
        int deltaLog2;
        if (removedCount >= (capacity() >> 2)) {
            METER(stats.compresses++);
            deltaLog2 = 0;
        } else {
            METER(stats.grows++);
            deltaLog2 = 1;
        }

        return changeTableSize(deltaLog2);
    }

    /* Infallibly rehash the table if we are overloaded with removals. */
    void checkOverRemoved()
    {
        if (overloaded()) {
            METER(stats.rehashes++);
            rehashTable();
            JS_ASSERT(!overloaded());
        }
    }

    void remove(Entry &e)
    {
        JS_ASSERT(table);
        METER(stats.removes++);

        if (e.hasCollision()) {
            e.setRemoved();
            removedCount++;
        } else {
            METER(stats.removeFrees++);
            e.setFree();
        }
        entryCount--;
        mutationCount++;
    }

    void checkUnderloaded()
    {
        if (underloaded()) {
            METER(stats.shrinks++);
            (void) changeTableSize(-1);
        }
    }

    /*
     * This is identical to changeTableSize(currentSize), but without requiring
     * a second table.  We do this by recycling the collision bits to tell us if
     * the element is already inserted or still waiting to be inserted.  Since
     * already-inserted elements win any conflicts, we get the same table as we
     * would have gotten through random insertion order.
     */
    void rehashTable()
    {
        removedCount = 0;
        for (size_t i = 0; i < capacity(); ++i)
            table[i].unsetCollision();

        for (size_t i = 0; i < capacity();) {
            Entry *src = &table[i];

            if (!src->isLive() || src->hasCollision()) {
                ++i;
                continue;
            }

            HashNumber keyHash = src->getKeyHash();
            HashNumber h1 = hash1(keyHash, hashShift);
            DoubleHash dh = hash2(keyHash, hashShift);
            Entry *tgt = &table[h1];
            while (true) {
                if (!tgt->hasCollision()) {
                    Swap(*src, *tgt);
                    tgt->setCollision();
                    break;
                }

                h1 = applyDoubleHash(h1, dh);
                tgt = &table[h1];
            }
        }

        /*
         * TODO: this algorithm leaves collision bits on *all* elements, even if
         * they are on no collision path. We have the option of setting the
         * collision bits correctly on a subsequent pass or skipping the rehash
         * unless we are totally filled with tombstones: benchmark to find out
         * which approach is best.
         */
    }

  public:
    void clear()
    {
        if (tl::IsPodType<Entry>::result) {
            memset(table, 0, sizeof(*table) * capacity());
        } else {
            uint32_t tableCapacity = capacity();
            for (Entry *e = table, *end = table + tableCapacity; e < end; ++e)
                *e = Move(Entry());
        }
        removedCount = 0;
        entryCount = 0;
        mutationCount++;
    }

    void finish()
    {
        JS_ASSERT(!entered);

        if (!table)
            return;

        destroyTable(*this, table, capacity());
        table = NULL;
        gen++;
        entryCount = 0;
        removedCount = 0;
        mutationCount++;
    }

    Range all() const {
        JS_ASSERT(table);
        return Range(table, table + capacity());
    }

    bool empty() const {
        JS_ASSERT(table);
        return !entryCount;
    }

    uint32_t count() const {
        JS_ASSERT(table);
        return entryCount;
    }

    uint32_t capacity() const {
        JS_ASSERT(table);
        return JS_BIT(sHashBits - hashShift);
    }

    uint32_t generation() const {
        JS_ASSERT(table);
        return gen;
    }

    size_t sizeOfExcludingThis(JSMallocSizeOfFun mallocSizeOf) const {
        return mallocSizeOf(table);
    }

    size_t sizeOfIncludingThis(JSMallocSizeOfFun mallocSizeOf) const {
        return mallocSizeOf(this) + sizeOfExcludingThis(mallocSizeOf);
    }

    Ptr lookup(const Lookup &l) const {
        ReentrancyGuard g(*this);
        HashNumber keyHash = prepareHash(l);
        return Ptr(lookup(l, keyHash, 0));
    }

    AddPtr lookupForAdd(const Lookup &l) const {
        ReentrancyGuard g(*this);
        HashNumber keyHash = prepareHash(l);
        Entry &entry = lookup(l, keyHash, sCollisionBit);
        AddPtr p(entry, keyHash);
        p.mutationCount = mutationCount;
        return p;
    }

    bool add(AddPtr &p)
    {
        ReentrancyGuard g(*this);
        JS_ASSERT(mutationCount == p.mutationCount);
        JS_ASSERT(table);
        JS_ASSERT(!p.found());
        JS_ASSERT(!(p.keyHash & sCollisionBit));

        /*
         * Changing an entry from removed to live does not affect whether we
         * are overloaded and can be handled separately.
         */
        if (p.entry->isRemoved()) {
            METER(stats.addOverRemoved++);
            removedCount--;
            p.keyHash |= sCollisionBit;
        } else {
            /* Preserve the validity of |p.entry|. */
            RebuildStatus status = checkOverloaded();
            if (status == RehashFailed)
                return false;
            if (status == Rehashed)
                p.entry = &findFreeEntry(p.keyHash);
        }

        p.entry->setLive(p.keyHash);
        entryCount++;
        mutationCount++;
        return true;
    }

    /*
     * There is an important contract between the caller and callee for this
     * function: if add() returns true, the caller must assign the T value
     * which produced p before using the hashtable again.
     */
    bool add(AddPtr &p, T** pentry)
    {
        if (!add(p))
            return false;
        *pentry = &p.entry->t;
        return true;
    }

    bool add(AddPtr &p, const T &t)
    {
        if (!add(p))
            return false;
        p.entry->t = t;
        return true;
    }

    void putNewInfallible(const Lookup &l, const T &t)
    {
        JS_ASSERT(table);

        HashNumber keyHash = prepareHash(l);
        Entry *entry = &findFreeEntry(keyHash);

        if (entry->isRemoved()) {
            METER(stats.addOverRemoved++);
            removedCount--;
            keyHash |= sCollisionBit;
        }

        entry->t = t;
        entry->setLive(keyHash);
        entryCount++;
        mutationCount++;
    }

    bool putNew(const Lookup &l, const T &t)
    {
        if (checkOverloaded() == RehashFailed)
            return false;

        putNewInfallible(l, t);
        return true;
    }

    bool relookupOrAdd(AddPtr& p, const Lookup &l, const T& t)
    {
        p.mutationCount = mutationCount;
        {
            ReentrancyGuard g(*this);
            p.entry = &lookup(l, p.keyHash, sCollisionBit);
        }
        return p.found() || add(p, t);
    }

    void remove(Ptr p)
    {
        JS_ASSERT(table);
        ReentrancyGuard g(*this);
        JS_ASSERT(p.found());
        remove(*p.entry);
        checkUnderloaded();
    }

#undef METER
};

}  /* namespace detail */

/*****************************************************************************/

/*
 * Hash policy
 *
 * A hash policy P for a hash table with key-type Key must provide:
 *  - a type |P::Lookup| to use to lookup table entries;
 *  - a static member function |P::hash| with signature
 *
 *      static js::HashNumber hash(Lookup)
 *
 *    to use to hash the lookup type; and
 *  - a static member function |P::match| with signature
 *
 *      static bool match(Key, Lookup)
 *
 *    to use to test equality of key and lookup values.
 *
 * Normally, Lookup = Key. In general, though, different values and types of
 * values can be used to lookup and store. If a Lookup value |l| is != to the
 * added Key value |k|, the user must ensure that |P::match(k,l)|. E.g.:
 *
 *   js::HashSet<Key, P>::AddPtr p = h.lookup(l);
 *   if (!p) {
 *     assert(P::match(k, l));  // must hold
 *     h.add(p, k);
 *   }
 */

/* Default hashing policies. */
template <class Key>
struct DefaultHasher
{
    typedef Key Lookup;
    static HashNumber hash(const Lookup &l) {
        /* Hash if can implicitly cast to hash number type. */
        return l;
    }
    static bool match(const Key &k, const Lookup &l) {
        /* Use builtin or overloaded operator==. */
        return k == l;
    }
};

/*
 * Pointer hashing policy that strips the lowest zeroBits when calculating the
 * hash to improve key distribution.
 */
template <typename Key, size_t zeroBits>
struct PointerHasher
{
    typedef Key Lookup;
    static HashNumber hash(const Lookup &l) {
        size_t word = reinterpret_cast<size_t>(l) >> zeroBits;
        JS_STATIC_ASSERT(sizeof(HashNumber) == 4);
#if JS_BYTES_PER_WORD == 4
        return HashNumber(word);
#else
        JS_STATIC_ASSERT(sizeof word == 8);
        return HashNumber((word >> 32) ^ word);
#endif
    }
    static bool match(const Key &k, const Lookup &l) {
        return k == l;
    }
};

template <typename Key, size_t zeroBits>
struct TaggedPointerHasher
{
    typedef Key Lookup;

    static HashNumber hash(const Lookup &l) {
        return PointerHasher<Key, zeroBits>::hash(l);
    }

    static const uintptr_t COMPARE_MASK = uintptr_t(-1) - 1;

    static bool match(const Key &k, const Lookup &l) {
        return (uintptr_t(k) & COMPARE_MASK) == uintptr_t(l);
    }
};

/*
 * Specialized hashing policy for pointer types. It assumes that the type is
 * at least word-aligned. For types with smaller size use PointerHasher.
 */
template <class T>
struct DefaultHasher<T *>: PointerHasher<T *, tl::FloorLog2<sizeof(void *)>::result> { };

/* Looking for a hasher for jsid?  Try the DefaultHasher<jsid> in jsatom.h. */

template <class Key, class Value>
class HashMapEntry
{
    template <class, class, class> friend class detail::HashTable;
    template <class> friend class detail::HashTableEntry;
    void operator=(const HashMapEntry &rhs) {
        const_cast<Key &>(key) = rhs.key;
        value = rhs.value;
    }

  public:
    HashMapEntry() : key(), value() {}

    template<typename KeyInput, typename ValueInput>
    HashMapEntry(const KeyInput &k, const ValueInput &v) : key(k), value(v) {}

    HashMapEntry(MoveRef<HashMapEntry> rhs)
      : key(Move(rhs->key)), value(Move(rhs->value)) { }
    void operator=(MoveRef<HashMapEntry> rhs) {
        const_cast<Key &>(key) = Move(rhs->key);
        value = Move(rhs->value);
    }

    const Key key;
    Value value;
};

namespace tl {

template <class T>
struct IsPodType<detail::HashTableEntry<T> > {
    static const bool result = IsPodType<T>::result;
};

template <class K, class V>
struct IsPodType<HashMapEntry<K, V> >
{
    static const bool result = IsPodType<K>::result && IsPodType<V>::result;
};

} /* namespace tl */

/*
 * JS-friendly, STL-like container providing a hash-based map from keys to
 * values. In particular, HashMap calls constructors and destructors of all
 * objects added so non-PODs may be used safely.
 *
 * Key/Value requirements:
 *  - default constructible, copyable, destructible, assignable
 * HashPolicy requirements:
 *  - see "Hash policy" above (default js::DefaultHasher<Key>)
 * AllocPolicy:
 *  - see "Allocation policies" in jsalloc.h
 *
 * N.B: HashMap is not reentrant: Key/Value/HashPolicy/AllocPolicy members
 *      called by HashMap must not call back into the same HashMap object.
 * N.B: Due to the lack of exception handling, the user must call |init()|.
 */
template <class Key,
          class Value,
          class HashPolicy = DefaultHasher<Key>,
          class AllocPolicy = TempAllocPolicy>
class HashMap
{
  public:
    typedef typename HashPolicy::Lookup Lookup;

    typedef HashMapEntry<Key, Value> Entry;

  private:
    /* Implement HashMap using HashTable. Lift |Key| operations to |Entry|. */
    struct MapHashPolicy : HashPolicy
    {
        typedef Key KeyType;
        static const Key &getKey(Entry &e) { return e.key; }
        static void setKey(Entry &e, Key &k) { const_cast<Key &>(e.key) = k; }
    };
    typedef detail::HashTable<Entry, MapHashPolicy, AllocPolicy> Impl;

    friend class Impl::Enum;

    /* Not implicitly copyable (expensive). May add explicit |clone| later. */
    HashMap(const HashMap &);
    HashMap &operator=(const HashMap &);

    Impl impl;

  public:
    const static unsigned sDefaultInitSize = Impl::sDefaultInitSize;

    /*
     * HashMap construction is fallible (due to OOM); thus the user must call
     * init after constructing a HashMap and check the return value.
     */
    HashMap(AllocPolicy a = AllocPolicy()) : impl(a)  {}
    bool init(uint32_t len = sDefaultInitSize)        { return impl.init(len); }
    bool initialized() const                          { return impl.initialized(); }

    /*
     * Return whether the given lookup value is present in the map. E.g.:
     *
     *   typedef HashMap<int,char> HM;
     *   HM h;
     *   if (HM::Ptr p = h.lookup(3)) {
     *     const HM::Entry &e = *p; // p acts like a pointer to Entry
     *     assert(p->key == 3);     // Entry contains the key
     *     char val = p->value;     // and value
     *   }
     *
     * Also see the definition of Ptr in HashTable above (with T = Entry).
     */
    typedef typename Impl::Ptr Ptr;
    Ptr lookup(const Lookup &l) const                 { return impl.lookup(l); }

    /* Assuming |p.found()|, remove |*p|. */
    void remove(Ptr p)                                { impl.remove(p); }

    /*
     * Like |lookup(l)|, but on miss, |p = lookupForAdd(l)| allows efficient
     * insertion of Key |k| (where |HashPolicy::match(k,l) == true|) using
     * |add(p,k,v)|. After |add(p,k,v)|, |p| points to the new Entry. E.g.:
     *
     *   typedef HashMap<int,char> HM;
     *   HM h;
     *   HM::AddPtr p = h.lookupForAdd(3);
     *   if (!p) {
     *     if (!h.add(p, 3, 'a'))
     *       return false;
     *   }
     *   const HM::Entry &e = *p;   // p acts like a pointer to Entry
     *   assert(p->key == 3);       // Entry contains the key
     *   char val = p->value;       // and value
     *
     * Also see the definition of AddPtr in HashTable above (with T = Entry).
     *
     * N.B. The caller must ensure that no mutating hash table operations
     * occur between a pair of |lookupForAdd| and |add| calls. To avoid
     * looking up the key a second time, the caller may use the more efficient
     * relookupOrAdd method. This method reuses part of the hashing computation
     * to more efficiently insert the key if it has not been added. For
     * example, a mutation-handling version of the previous example:
     *
     *    HM::AddPtr p = h.lookupForAdd(3);
     *    if (!p) {
     *      call_that_may_mutate_h();
     *      if (!h.relookupOrAdd(p, 3, 'a'))
     *        return false;
     *    }
     *    const HM::Entry &e = *p;
     *    assert(p->key == 3);
     *    char val = p->value;
     */
    typedef typename Impl::AddPtr AddPtr;
    AddPtr lookupForAdd(const Lookup &l) const {
        return impl.lookupForAdd(l);
    }

    template<typename KeyInput, typename ValueInput>
    bool add(AddPtr &p, const KeyInput &k, const ValueInput &v) {
        Entry *pentry;
        if (!impl.add(p, &pentry))
            return false;
        const_cast<Key &>(pentry->key) = k;
        pentry->value = v;
        return true;
    }

    bool add(AddPtr &p, const Key &k, MoveRef<Value> v) {
        Entry *pentry;
        if (!impl.add(p, &pentry))
            return false;
        const_cast<Key &>(pentry->key) = k;
        pentry->value = v;
        return true;
    }

    bool add(AddPtr &p, const Key &k) {
        Entry *pentry;
        if (!impl.add(p, &pentry))
            return false;
        const_cast<Key &>(pentry->key) = k;
        return true;
    }

    template<typename KeyInput, typename ValueInput>
    bool relookupOrAdd(AddPtr &p, const KeyInput &k, const ValueInput &v) {
        return impl.relookupOrAdd(p, k, Entry(k, v));
    }

    /*
     * |all()| returns a Range containing |count()| elements. E.g.:
     *
     *   typedef HashMap<int,char> HM;
     *   HM h;
     *   for (HM::Range r = h.all(); !r.empty(); r.popFront())
     *     char c = r.front().value;
     *
     * Also see the definition of Range in HashTable above (with T = Entry).
     */
    typedef typename Impl::Range Range;
    Range all() const                                 { return impl.all(); }
    uint32_t count() const                            { return impl.count(); }
    size_t capacity() const                           { return impl.capacity(); }
    size_t sizeOfExcludingThis(JSMallocSizeOfFun mallocSizeOf) const {
        return impl.sizeOfExcludingThis(mallocSizeOf);
    }
    size_t sizeOfIncludingThis(JSMallocSizeOfFun mallocSizeOf) const {
        /*
         * Don't just call |impl.sizeOfExcludingThis()| because there's no
         * guarantee that |impl| is the first field in HashMap.
         */
        return mallocSizeOf(this) + impl.sizeOfExcludingThis(mallocSizeOf);
    }

    /*
     * Typedef for the enumeration class. An Enum may be used to examine and
     * remove table entries:
     *
     *   typedef HashMap<int,char> HM;
     *   HM s;
     *   for (HM::Enum e(s); !e.empty(); e.popFront())
     *     if (e.front().value == 'l')
     *       e.removeFront();
     *
     * Table resize may occur in Enum's destructor. Also see the definition of
     * Enum in HashTable above (with T = Entry).
     */
    typedef typename Impl::Enum Enum;

    /*
     * Remove all entries. This does not shrink the table. For that consider
     * using the finish() method.
     */
    void clear()                                      { impl.clear(); }

    /*
     * Remove all the entries and release all internal buffers. The map must
     * be initialized again before any use.
     */
    void finish()                                     { impl.finish(); }

   /* Does the table contain any entries? */
    bool empty() const                                { return impl.empty(); }

    /*
     * If |generation()| is the same before and after a HashMap operation,
     * pointers into the table remain valid.
     */
    unsigned generation() const                       { return impl.generation(); }

    /* Shorthand operations: */

    bool has(const Lookup &l) const {
        return impl.lookup(l) != NULL;
    }

    /* Overwrite existing value with v. Return false on oom. */
    template<typename KeyInput, typename ValueInput>
    bool put(const KeyInput &k, const ValueInput &v) {
        AddPtr p = lookupForAdd(k);
        if (p) {
            p->value = v;
            return true;
        }
        return add(p, k, v);
    }

    /* Like put, but assert that the given key is not already present. */
    bool putNew(const Key &k, const Value &v) {
        return impl.putNew(k, Entry(k, v));
    }

    /* Add (k,defaultValue) if k no found. Return false-y Ptr on oom. */
    Ptr lookupWithDefault(const Key &k, const Value &defaultValue) {
        AddPtr p = lookupForAdd(k);
        if (p)
            return p;
        (void)add(p, k, defaultValue);  /* p is left false-y on oom. */
        return p;
    }

    /* Remove if present. */
    void remove(const Lookup &l) {
        if (Ptr p = lookup(l))
            remove(p);
    }
};

/*
 * JS-friendly, STL-like container providing a hash-based set of values. In
 * particular, HashSet calls constructors and destructors of all objects added
 * so non-PODs may be used safely.
 *
 * T requirements:
 *  - default constructible, copyable, destructible, assignable
 * HashPolicy requirements:
 *  - see "Hash policy" above (default js::DefaultHasher<Key>)
 * AllocPolicy:
 *  - see "Allocation policies" in jsalloc.h
 *
 * N.B: HashSet is not reentrant: T/HashPolicy/AllocPolicy members called by
 *      HashSet must not call back into the same HashSet object.
 * N.B: Due to the lack of exception handling, the user must call |init()|.
 */
template <class T, class HashPolicy = DefaultHasher<T>, class AllocPolicy = TempAllocPolicy>
class HashSet
{
    typedef typename HashPolicy::Lookup Lookup;

    /* Implement HashSet in terms of HashTable. */
    struct SetOps : HashPolicy {
        typedef T KeyType;
        static const KeyType &getKey(const T &t) { return t; }
        static void setKey(T &t, KeyType &k) { t = k; }
    };
    typedef detail::HashTable<const T, SetOps, AllocPolicy> Impl;

    friend class Impl::Enum;

    /* Not implicitly copyable (expensive). May add explicit |clone| later. */
    HashSet(const HashSet &);
    HashSet &operator=(const HashSet &);

    Impl impl;

  public:
    const static unsigned sDefaultInitSize = Impl::sDefaultInitSize;

    /*
     * HashSet construction is fallible (due to OOM); thus the user must call
     * init after constructing a HashSet and check the return value.
     */
    HashSet(AllocPolicy a = AllocPolicy()) : impl(a)  {}
    bool init(uint32_t len = sDefaultInitSize)        { return impl.init(len); }
    bool initialized() const                          { return impl.initialized(); }

    /*
     * Return whether the given lookup value is present in the map. E.g.:
     *
     *   typedef HashSet<int> HS;
     *   HS h;
     *   if (HS::Ptr p = h.lookup(3)) {
     *     assert(*p == 3);   // p acts like a pointer to int
     *   }
     *
     * Also see the definition of Ptr in HashTable above.
     */
    typedef typename Impl::Ptr Ptr;
    Ptr lookup(const Lookup &l) const                 { return impl.lookup(l); }

    /* Assuming |p.found()|, remove |*p|. */
    void remove(Ptr p)                                { impl.remove(p); }

    /*
     * Like |lookup(l)|, but on miss, |p = lookupForAdd(l)| allows efficient
     * insertion of T value |t| (where |HashPolicy::match(t,l) == true|) using
     * |add(p,t)|. After |add(p,t)|, |p| points to the new element. E.g.:
     *
     *   typedef HashSet<int> HS;
     *   HS h;
     *   HS::AddPtr p = h.lookupForAdd(3);
     *   if (!p) {
     *     if (!h.add(p, 3))
     *       return false;
     *   }
     *   assert(*p == 3);   // p acts like a pointer to int
     *
     * Also see the definition of AddPtr in HashTable above.
     *
     * N.B. The caller must ensure that no mutating hash table operations
     * occur between a pair of |lookupForAdd| and |add| calls. To avoid
     * looking up the key a second time, the caller may use the more efficient
     * relookupOrAdd method. This method reuses part of the hashing computation
     * to more efficiently insert the key if it has not been added. For
     * example, a mutation-handling version of the previous example:
     *
     *    HS::AddPtr p = h.lookupForAdd(3);
     *    if (!p) {
     *      call_that_may_mutate_h();
     *      if (!h.relookupOrAdd(p, 3, 3))
     *        return false;
     *    }
     *    assert(*p == 3);
     *
     * Note that relookupOrAdd(p,l,t) performs Lookup using l and adds the
     * entry t, where the caller ensures match(l,t).
     */
    typedef typename Impl::AddPtr AddPtr;
    AddPtr lookupForAdd(const Lookup &l) const {
        return impl.lookupForAdd(l);
    }

    bool add(AddPtr &p, const T &t) {
        return impl.add(p, t);
    }

    bool relookupOrAdd(AddPtr &p, const Lookup &l, const T &t) {
        return impl.relookupOrAdd(p, l, t);
    }

    /*
     * |all()| returns a Range containing |count()| elements:
     *
     *   typedef HashSet<int> HS;
     *   HS h;
     *   for (HS::Range r = h.all(); !r.empty(); r.popFront())
     *     int i = r.front();
     *
     * Also see the definition of Range in HashTable above.
     */
    typedef typename Impl::Range Range;
    Range all() const                                 { return impl.all(); }
    uint32_t count() const                            { return impl.count(); }
    size_t capacity() const                           { return impl.capacity(); }
    size_t sizeOfExcludingThis(JSMallocSizeOfFun mallocSizeOf) const {
        return impl.sizeOfExcludingThis(mallocSizeOf);
    }
    size_t sizeOfIncludingThis(JSMallocSizeOfFun mallocSizeOf) const {
        /*
         * Don't just call |impl.sizeOfExcludingThis()| because there's no
         * guarantee that |impl| is the first field in HashSet.
         */
        return mallocSizeOf(this) + impl.sizeOfExcludingThis(mallocSizeOf);
    }

    /*
     * Typedef for the enumeration class. An Enum may be used to examine and
     * remove table entries:
     *
     *   typedef HashSet<int> HS;
     *   HS s;
     *   for (HS::Enum e(s); !e.empty(); e.popFront())
     *     if (e.front() == 42)
     *       e.removeFront();
     *
     * Table resize may occur in Enum's destructor. Also see the definition of
     * Enum in HashTable above.
     */
    typedef typename Impl::Enum Enum;

    /*
     * Remove all entries. This does not shrink the table. For that consider
     * using the finish() method.
     */
    void clear()                                      { impl.clear(); }

    /*
     * Remove all the entries and release all internal buffers. The set must
     * be initialized again before any use.
     */
    void finish()                                     { impl.finish(); }

    /* Does the table contain any entries? */
    bool empty() const                                { return impl.empty(); }

    /*
     * If |generation()| is the same before and after a HashSet operation,
     * pointers into the table remain valid.
     */
    unsigned generation() const                       { return impl.generation(); }

    /* Shorthand operations: */

    bool has(const Lookup &l) const {
        return impl.lookup(l) != NULL;
    }

    /* Overwrite existing value with v. Return false on oom. */
    bool put(const T &t) {
        AddPtr p = lookupForAdd(t);
        return p ? true : add(p, t);
    }

    /* Like put, but assert that the given key is not already present. */
    bool putNew(const T &t) {
        return impl.putNew(t, t);
    }

    bool putNew(const Lookup &l, const T &t) {
        return impl.putNew(l, t);
    }

    void remove(const Lookup &l) {
        if (Ptr p = lookup(l))
            remove(p);
    }
};

}  /* namespace js */

#endif
