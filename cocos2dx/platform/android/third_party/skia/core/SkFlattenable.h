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

#ifndef SkFlattenable_DEFINED
#define SkFlattenable_DEFINED

#include "SkRefCnt.h"
#include "SkBitmap.h"
#include "SkReader32.h"
#include "SkTDArray.h"
#include "SkWriter32.h"

class SkFlattenableReadBuffer;
class SkFlattenableWriteBuffer;
class SkString;

/** \class SkFlattenable
 
 SkFlattenable is the base class for objects that need to be flattened
 into a data stream for either transport or as part of the key to the
 font cache.
 */
class SkFlattenable : public SkRefCnt {
public:
    typedef SkFlattenable* (*Factory)(SkFlattenableReadBuffer&);
    
    SkFlattenable() {}
    
    /** Implement this to return a factory function pointer that can be called
     to recreate your class given a buffer (previously written to by your
     override of flatten().
     */
    virtual Factory getFactory() = 0;
    /** Override this to write data specific to your subclass into the buffer,
     being sure to call your super-class' version first. This data will later
     be passed to your Factory function, returned by getFactory().
     */
    virtual void flatten(SkFlattenableWriteBuffer&);
    
    /** Set the string to describe the sublass and return true. If this is not
        overridden, ignore the string param and return false.
     */
    virtual bool toDumpString(SkString*) const;

    static Factory NameToFactory(const char name[]);
    static const char* FactoryToName(Factory);
    static void Register(const char name[], Factory);
    
    class Registrar {
    public:
        Registrar(const char name[], Factory factory) {
            SkFlattenable::Register(name, factory);
        }
    };
    
protected:
    SkFlattenable(SkFlattenableReadBuffer&) {}
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class SkTypeface;

class SkFlattenableReadBuffer : public SkReader32 {
public:
    SkFlattenableReadBuffer();
    explicit SkFlattenableReadBuffer(const void* data);
    SkFlattenableReadBuffer(const void* data, size_t size);
    
    void setRefCntArray(SkRefCnt* array[], int count) {
        fRCArray = array;
        fRCCount = count;
    }
    
    void setTypefaceArray(SkTypeface* array[], int count) {
        fTFArray = array;
        fTFCount = count;
    }
    
    void setFactoryPlayback(SkFlattenable::Factory array[], int count) {
        fFactoryArray = array;
        fFactoryCount = count;
    }
    
    SkTypeface* readTypeface();
    SkRefCnt* readRefCnt();
    void* readFunctionPtr();
    SkFlattenable* readFlattenable();
    
private:
    SkRefCnt** fRCArray;
    int        fRCCount;
    
    SkTypeface** fTFArray;
    int        fTFCount;
    
    SkFlattenable::Factory* fFactoryArray;
    int                     fFactoryCount;
    
    typedef SkReader32 INHERITED;
};

///////////////////////////////////////////////////////////////////////////////

#include "SkPtrRecorder.h"

class SkRefCntRecorder : public SkPtrRecorder {
public:
    virtual ~SkRefCntRecorder();
    
    /** Add a refcnt object to the set and ref it if not already present,
        or if it is already present, do nothing. Either way, returns 0 if obj
        is null, or a base-1 index if obj is not null.
    */
    uint32_t record(SkRefCnt* ref) {
        return this->recordPtr(ref);
    }

    // This does not change the owner counts on the objects
    void get(SkRefCnt* array[]) const {
        this->getPtrs((void**)array);
    }

protected:
    // overrides
    virtual void incPtr(void*);
    virtual void decPtr(void*);

private:
    typedef SkPtrRecorder INHERITED;
};

class SkFactoryRecorder : public SkPtrRecorder {
public:
    /** Add a factory to the set. If it is null return 0, otherwise return a
        base-1 index for the factory.
    */
    uint32_t record(SkFlattenable::Factory fact) {
        return this->recordPtr((void*)fact);
    }
    
    void get(SkFlattenable::Factory array[]) const {
        this->getPtrs((void**)array);
    }
    
private:
    typedef SkPtrRecorder INHERITED;
};

class SkFlattenableWriteBuffer : public SkWriter32 {
public:
    SkFlattenableWriteBuffer(size_t minSize);
    virtual ~SkFlattenableWriteBuffer();

    void writeTypeface(SkTypeface*);
    void writeRefCnt(SkRefCnt*);
    void writeFunctionPtr(void*);
    void writeFlattenable(SkFlattenable* flattenable);
    
    SkRefCntRecorder* getTypefaceRecorder() const { return fTFRecorder; }
    SkRefCntRecorder* setTypefaceRecorder(SkRefCntRecorder*);
    
    SkRefCntRecorder* getRefCntRecorder() const { return fRCRecorder; }
    SkRefCntRecorder* setRefCntRecorder(SkRefCntRecorder*);
    
    SkFactoryRecorder* getFactoryRecorder() const { return fFactoryRecorder; }
    SkFactoryRecorder* setFactoryRecorder(SkFactoryRecorder*);

    enum Flags {
        kCrossProcess_Flag      = 0x01
    };
    Flags getFlags() const { return fFlags; }
    void setFlags(Flags flags) { fFlags = flags; }
    
    bool isCrossProcess() const { return (fFlags & kCrossProcess_Flag) != 0; }

    bool persistBitmapPixels() const {
        return (fFlags & kCrossProcess_Flag) != 0;
    }
    
    bool persistTypeface() const { return (fFlags & kCrossProcess_Flag) != 0; }

private:
    Flags               fFlags;
    SkRefCntRecorder*   fTFRecorder;
    SkRefCntRecorder*   fRCRecorder;
    SkFactoryRecorder*  fFactoryRecorder;
    
    typedef SkWriter32 INHERITED;
};

#endif

