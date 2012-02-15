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

#ifndef SkStream_DEFINED
#define SkStream_DEFINED

#include "SkRefCnt.h"
#include "SkScalar.h"

class SkData;

class SK_API SkStream : public SkRefCnt {
public:
    virtual ~SkStream();
    /** Called to rewind to the beginning of the stream. If this cannot be
        done, return false.
    */
    virtual bool rewind() = 0;
    /** If this stream represents a file, this method returns the file's name.
        If it does not, it returns NULL (the default behavior).
    */
    virtual const char* getFileName();
    /** Called to read or skip size number of bytes.
        If buffer is NULL and size > 0, skip that many bytes, returning how many were skipped.
        If buffer is NULL and size == 0, return the total length of the stream.
        If buffer != NULL, copy the requested number of bytes into buffer, returning how many were copied.
        @param buffer   If buffer is NULL, ignore and just skip size bytes, otherwise copy size bytes into buffer
        @param size The number of bytes to skip or copy
        @return bytes read on success
    */
    virtual size_t read(void* buffer, size_t size) = 0;

    /** Return the total length of the stream.
    */
    size_t getLength() { return this->read(NULL, 0); }
    
    /** Skip the specified number of bytes, returning the actual number
        of bytes that could be skipped.
    */
    size_t skip(size_t bytes);

    /** If the stream is backed by RAM, this method returns the starting
        address for the data. If not (i.e. it is backed by a file or other
        structure), this method returns NULL.
        The default implementation returns NULL.
    */
    virtual const void* getMemoryBase();

    int8_t   readS8();
    int16_t  readS16();
    int32_t  readS32();

    uint8_t  readU8() { return (uint8_t)this->readS8(); }
    uint16_t readU16() { return (uint16_t)this->readS16(); }
    uint32_t readU32() { return (uint32_t)this->readS32(); }

    bool     readBool() { return this->readU8() != 0; }
    SkScalar readScalar();
    size_t   readPackedUInt();
};

class SK_API SkWStream : SkNoncopyable {
public:
    virtual ~SkWStream();

    /** Called to write bytes to a SkWStream. Returns true on success
        @param buffer the address of at least size bytes to be written to the stream
        @param size The number of bytes in buffer to write to the stream
        @return true on success
    */
    virtual bool write(const void* buffer, size_t size) = 0;
    virtual void newline();
    virtual void flush();

    // helpers
    
    bool    write8(U8CPU);
    bool    write16(U16CPU);
    bool    write32(uint32_t);

    bool    writeText(const char text[]);
    bool    writeDecAsText(int32_t);
    bool    writeBigDecAsText(int64_t, int minDigits = 0);
    bool    writeHexAsText(uint32_t, int minDigits = 0);
    bool    writeScalarAsText(SkScalar);
    
    bool    writeBool(bool v) { return this->write8(v); }
    bool    writeScalar(SkScalar);
    bool    writePackedUInt(size_t);
    
    bool writeStream(SkStream* input, size_t length);

    bool writeData(const SkData*);
};

////////////////////////////////////////////////////////////////////////////////////////

#include "SkString.h"

struct SkFILE;

/** A stream that reads from a FILE*, which is opened in the constructor and
    closed in the destructor
 */
class SK_API SkFILEStream : public SkStream {
public:
    /** Initialize the stream by calling fopen on the specified path. Will be
        closed in the destructor.
     */
    explicit SkFILEStream(const char path[] = NULL);
    virtual ~SkFILEStream();

    /** Returns true if the current path could be opened.
    */
    bool isValid() const { return fFILE != NULL; }
    /** Close the current file, and open a new file with the specified
        path. If path is NULL, just close the current file.
    */
    void setPath(const char path[]);

    virtual bool rewind();
    virtual size_t read(void* buffer, size_t size);
    virtual const char* getFileName();

private:
    SkFILE*     fFILE;
    SkString    fName;
};

/** A stream that reads from a file descriptor
 */
class SkFDStream : public SkStream {
public:
    /** Initialize the stream with a dup() of the specified file descriptor.
        If closeWhenDone is true, then the descriptor will be closed in the
        destructor.
     */
    SkFDStream(int fileDesc, bool closeWhenDone);
    virtual ~SkFDStream();
    
    /** Returns true if the current path could be opened.
     */
    bool isValid() const { return fFD >= 0; }
    
    virtual bool rewind();
    virtual size_t read(void* buffer, size_t size);
    virtual const char* getFileName() { return NULL; }
    
private:
    int     fFD;
    bool    fCloseWhenDone;
};

class SkMemoryStream : public SkStream {
public:
    SkMemoryStream();
    /** We allocate (and free) the memory. Write to it via getMemoryBase()
    */
    SkMemoryStream(size_t length);
    /** if copyData is true, the stream makes a private copy of the data
    */
    SkMemoryStream(const void* data, size_t length, bool copyData = false);
    virtual ~SkMemoryStream();

    /** Resets the stream to the specified data and length,
        just like the constructor.
        if copyData is true, the stream makes a private copy of the data
    */
    virtual void setMemory(const void* data, size_t length,
                           bool copyData = false);
    /** Replace any memory buffer with the specified buffer. The caller
        must have allocated data with sk_malloc or sk_realloc, since it
        will be freed with sk_free.
    */
    void setMemoryOwned(const void* data, size_t length);

    /**
     *  Return the stream's data in a SkData. The caller must call unref() when
     *  it is finished using the data.
     */
    SkData* copyToData() const;

    /**
     *  Use the specified data as the memory for this stream. The stream will
     *  call ref() on the data (assuming it is not null). The function returns
     *  the data parameter as a convenience.
     */
    SkData* setData(SkData*);

    void skipToAlign4();
    virtual bool rewind();
    virtual size_t read(void* buffer, size_t size);
    virtual const void* getMemoryBase();
    const void* getAtPos();
    size_t seek(size_t offset);
    size_t peek() const { return fOffset; }
    
private:
    SkData* fData;
    size_t  fOffset;
};

/** \class SkBufferStream
    This is a wrapper class that adds buffering to another stream.
    The caller can provide the buffer, or ask SkBufferStream to allocated/free
    it automatically.
*/
class SkBufferStream : public SkStream {
public:
    /** Provide the stream to be buffered (proxy), and the size of the buffer that
        should be used. This will be allocated and freed automatically. If bufferSize is 0,
        a default buffer size will be used.
        The proxy stream is referenced, and will be unreferenced in when the
        bufferstream is destroyed.
    */
    SkBufferStream(SkStream* proxy, size_t bufferSize = 0);
    /** Provide the stream to be buffered (proxy), and a buffer and size to be used.
        This buffer is owned by the caller, and must be at least bufferSize bytes big.
        Passing NULL for buffer will cause the buffer to be allocated/freed automatically.
        If buffer is not NULL, it is an error for bufferSize to be 0.
     The proxy stream is referenced, and will be unreferenced in when the
     bufferstream is destroyed.
    */
    SkBufferStream(SkStream* proxy, void* buffer, size_t bufferSize);
    virtual ~SkBufferStream();

    virtual bool        rewind();
    virtual const char* getFileName();
    virtual size_t      read(void* buffer, size_t size);
    virtual const void* getMemoryBase();

private:
    enum {
        kDefaultBufferSize  = 128
    };
    // illegal
    SkBufferStream(const SkBufferStream&);
    SkBufferStream& operator=(const SkBufferStream&);

    SkStream*   fProxy;
    char*       fBuffer;
    size_t      fOrigBufferSize, fBufferSize, fBufferOffset;
    bool        fWeOwnTheBuffer;

    void    init(void*, size_t);
};

/////////////////////////////////////////////////////////////////////////////////////////////

class SK_API SkFILEWStream : public SkWStream {
public:
            SkFILEWStream(const char path[]);
    virtual ~SkFILEWStream();

    /** Returns true if the current path could be opened.
    */
    bool isValid() const { return fFILE != NULL; }

    virtual bool write(const void* buffer, size_t size);
    virtual void flush();
private:
    SkFILE* fFILE;
};

class SkMemoryWStream : public SkWStream {
public:
    SkMemoryWStream(void* buffer, size_t size);
    virtual bool write(const void* buffer, size_t size);
    
private:
    char*   fBuffer;
    size_t  fMaxLength;
    size_t  fBytesWritten;
};

class SK_API SkDynamicMemoryWStream : public SkWStream {
public:
    SkDynamicMemoryWStream();
    virtual ~SkDynamicMemoryWStream();

    virtual bool write(const void* buffer, size_t size);
    // random access write
    // modifies stream and returns true if offset + size is less than or equal to getOffset()
    bool write(const void* buffer, size_t offset, size_t size);
    bool read(void* buffer, size_t offset, size_t size);
    size_t getOffset() const { return fBytesWritten; }
    size_t bytesWritten() const { return fBytesWritten; }

    // copy what has been written to the stream into dst
    void copyTo(void* dst) const;

    /**
     *  Return a copy of the data written so far. This call is responsible for
     *  calling unref() when they are finished with the data.
     */
    SkData* copyToData() const;

    // reset the stream to its original state
    void reset();
    void padToAlign4();
private:
    struct Block;
    Block*  fHead;
    Block*  fTail;
    size_t  fBytesWritten;
    mutable SkData* fCopy;  // is invalidated if we write after it is created

    void invalidateCopy();
};


class SkDebugWStream : public SkWStream {
public:
    // overrides
    virtual bool write(const void* buffer, size_t size);
    virtual void newline();
};

// for now
typedef SkFILEStream SkURLStream;

#endif
