/*
    Copyright 2011 Google Inc.

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

#ifndef GrBinHashKey_DEFINED
#define GrBinHashKey_DEFINED

#include "GrTypes.h"

/**
 * Abstract base class that presents the building interface of GrBinHashKey.
 * This base class allows builder methods to not know the exact template
 * parameters of GrBinHashKey
 */
class GrBinHashKeyBuilder {
public:
    GrBinHashKeyBuilder() {}
    virtual ~GrBinHashKeyBuilder() {}
    virtual void keyData(const uint32_t *dataToAdd, size_t len) = 0;
};

/**
 *  Hash function class than can take a data stream of indeterminate length.
 *  It also has the ability to recieve data in several chunks (steamed). The
 *  hash function used is the One-at-a-Time Hash
 *  (http://burtleburtle.net/bob/hash/doobs.html).
 *
 *  Keys are built in two passes the first pass builds the key until the
 *  allocated storage for the key runs out, raw data accumulation stops, but
 *  the calculation of the 32-bit hash value and total key length continue.
 *  The second pass is only necessary if storage ran-out during the first pass.
 *  If that is the case, the heap storage portion of the key will be
 *  re-allocated so that the entire key can be stored in the second pass.
 *
 *  Code for building a key:
 *
 *      GrBinHashKey<MyEntryStruct, MyStackSize> MyKey;
 *      while( MyKey->doPass() )
 *      {
 *          MyObject->buildKey(&MyKey); //invoke a builder method
 *      }
 *
 *  All the builder method needs to do is make calls to the keyData method to
 *  append binary data to the key.
 */
template<typename Entry, size_t StackSize>
class GrBinHashKey : public GrBinHashKeyBuilder {
public:
    GrBinHashKey()
        : fA(0)
        , fLength(0)
        , fHeapData(NULL)
        , fPhysicalSize(StackSize)
        , fUseHeap(false)
        , fPass(0)
#if GR_DEBUG
        , fIsValid(true)
#endif
    {}

private:
    // Illegal: must choose explicitly between copyAndTakeOwnership
    // and deepCopyFrom.
    // Not inheriting GrNoncopyable, because it causes very obscure compiler
    // errors with template classes, which are hard to trace back to the use
    // of assignment.
    GrBinHashKey(const GrBinHashKey<Entry, StackSize>&) {}
    GrBinHashKey<Entry, StackSize>& operator=(const GrBinHashKey<Entry,
        StackSize>&) {
        return this;
    }

public:
    void copyAndTakeOwnership(GrBinHashKey<Entry, StackSize>& key) {
        GrAssert(key.fIsValid);
        copyFields(key);
        if (fUseHeap) {
            key.fHeapData = NULL;  // ownership transfer
        }
        // Consistency Checking
        // To avoid the overhead of copying or ref-counting the dynamically
        // allocated portion of the key, we use ownership transfer
        // Key usability is only tracked in debug builds.
        GR_DEBUGCODE(key.fIsValid = false;)
    }

    void deepCopyFrom(const GrBinHashKey<Entry, StackSize>& key) {
        GrAssert(key.fIsValid);
        copyFields(key);
        if (fUseHeap) {
            fHeapData = reinterpret_cast<uint8_t*>(
                GrMalloc(sizeof(uint8_t) * fPhysicalSize));
            memcpy(fHeapData, key.fHeapData, fLength);
        }
    }

    virtual ~GrBinHashKey() {
        if (fUseHeap) {
            GrFree(fHeapData);
        }
    }

    bool doPass() {
        GrAssert(fIsValid);
        if (0 == fPass) {
            fPass++;
            return true;
        }
        if (1 == fPass) {
            bool passNeeded = false;
            if (fLength > fPhysicalSize) {
                // If the first pass ran out of space the we need to
                // re-allocate and perform a second pass
                GrFree(fHeapData);
                fHeapData = reinterpret_cast<uint8_t*>(
                    GrMalloc(sizeof(uint8_t) * fLength));
                fPhysicalSize = fLength;
                fUseHeap = true;
                passNeeded = true;
                fLength = 0;
            }
            fPass++;
            return passNeeded;
        }
        return false;
    }

    void keyData(const uint32_t *dataToAdd, size_t len) {
        GrAssert(fIsValid);
        GrAssert(fPass);
        GrAssert(GrIsALIGN4(len));
        if (fUseHeap) {
            GrAssert(fHeapData);
            GrAssert(fLength + len <= fPhysicalSize);
            memcpy(&fHeapData[fLength], dataToAdd, len );
        } else {
            if (fLength + len <= StackSize) {
                memcpy(&fStackData[fLength], dataToAdd, len);
            } else {
                GrAssert(1 == fPass);
            }
        }

        fLength += len;

        if (1 == fPass) {
            uint32_t a = fA;
            while (len >= 4) {
                a += *dataToAdd++;
                a += (a << 10);
                a ^= (a >> 6);
                len -= 4;
            }
            a += (a << 3);
            a ^= (a >> 11);
            a += (a << 15);

            fA = a;
        }
    }

    int compare(const GrBinHashKey<Entry, StackSize>& key) const {
        GrAssert(fIsValid);
        if (fLength == key.fLength) {
            GrAssert(fUseHeap == key.fUseHeap);
            if(fUseHeap) {
                return memcmp(fHeapData, key.fHeapData, fLength);
            } else {
                return memcmp(fStackData, key.fStackData, fLength);
            }
        }

        return (fLength - key.fLength);
    }

    static bool
    EQ(const Entry& entry, const GrBinHashKey<Entry, StackSize>& key) {
        GrAssert(key.fIsValid);
        return 0 == entry.compare(key);
    }

    static bool
    LT(const Entry& entry, const GrBinHashKey<Entry, StackSize>& key) {
        GrAssert(key.fIsValid);
        return entry.compare(key) < 0;
    }

    uint32_t getHash() const {
        GrAssert(fIsValid);
        return fA;
    }

private:
    void copyFields(const GrBinHashKey<Entry, StackSize>& src) {
        if (fUseHeap) {
            GrFree(fHeapData);
        }
        // We do a field-by-field copy because this is a non-POD
        // class, and therefore memcpy would be bad
        fA = src.fA;
        fLength = src.fLength;
        memcpy(fStackData, src.fStackData, StackSize);
        fHeapData = src.fHeapData;
        fPhysicalSize = src.fPhysicalSize;
        fUseHeap = src.fUseHeap;
        fPass = src.fPass;
    }

    uint32_t                fA;

    // For accumulating the variable length binary key
    size_t              fLength;                // length of data accumulated so far
    uint8_t             fStackData[StackSize];  //Buffer for key storage
    uint8_t*            fHeapData;              //Dynamically allocated extended key storage
    size_t              fPhysicalSize;          //Total size available for key storage
    bool                fUseHeap;               //Using a dynamically allocated key storage
    int                 fPass;                  //Key generation pass counter

#if GR_DEBUG
public:
    bool                fIsValid;
#endif
};

#endif
