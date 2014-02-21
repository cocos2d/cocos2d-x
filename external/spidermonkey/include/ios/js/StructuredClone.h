/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sts=4 et sw=4 tw=99:
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef js_StructuredClone_h
#define js_StructuredClone_h

#include "mozilla/NullPtr.h"

#include <stdint.h>

#include "jstypes.h"

#include "js/RootingAPI.h"
#include "js/TypeDecls.h"
#include "js/Value.h"

struct JSRuntime;
struct JSStructuredCloneReader;
struct JSStructuredCloneWriter;

// API for the HTML5 internal structured cloning algorithm.

// Read structured data from the reader r. This hook is used to read a value
// previously serialized by a call to the WriteStructuredCloneOp hook.
//
// tag and data are the pair of uint32_t values from the header. The callback
// may use the JS_Read* APIs to read any other relevant parts of the object
// from the reader r. closure is any value passed to the JS_ReadStructuredClone
// function. Return the new object on success, nullptr on error/exception.
typedef JSObject *(*ReadStructuredCloneOp)(JSContext *cx, JSStructuredCloneReader *r,
                                           uint32_t tag, uint32_t data, void *closure);

// Structured data serialization hook. The engine can write primitive values,
// Objects, Arrays, Dates, RegExps, TypedArrays, and ArrayBuffers. Any other
// type of object requires application support. This callback must first use
// the JS_WriteUint32Pair API to write an object header, passing a value
// greater than JS_SCTAG_USER to the tag parameter. Then it can use the
// JS_Write* APIs to write any other relevant parts of the value v to the
// writer w. closure is any value passed to the JS_WriteStructuredCLone function.
//
// Return true on success, false on error/exception.
typedef bool (*WriteStructuredCloneOp)(JSContext *cx, JSStructuredCloneWriter *w,
                                         JS::Handle<JSObject*> obj, void *closure);

// This is called when JS_WriteStructuredClone is given an invalid transferable.
// To follow HTML5, the application must throw a DATA_CLONE_ERR DOMException
// with error set to one of the JS_SCERR_* values.
typedef void (*StructuredCloneErrorOp)(JSContext *cx, uint32_t errorid);

// The maximum supported structured-clone serialization format version. Note
// that this does not need to be bumped for Transferable-only changes, since
// they are never saved to persistent storage.
#define JS_STRUCTURED_CLONE_VERSION 2

struct JSStructuredCloneCallbacks {
    ReadStructuredCloneOp read;
    WriteStructuredCloneOp write;
    StructuredCloneErrorOp reportError;
};

// Note: if the *data contains transferable objects, it can be read only once.
JS_PUBLIC_API(bool)
JS_ReadStructuredClone(JSContext *cx, uint64_t *data, size_t nbytes, uint32_t version,
                       JS::MutableHandleValue vp,
                       const JSStructuredCloneCallbacks *optionalCallbacks, void *closure);

// Note: On success, the caller is responsible for calling
// JS_ClearStructuredClone(*datap, nbytesp).
JS_PUBLIC_API(bool)
JS_WriteStructuredClone(JSContext *cx, JS::HandleValue v, uint64_t **datap, size_t *nbytesp,
                        const JSStructuredCloneCallbacks *optionalCallbacks,
                        void *closure, JS::HandleValue transferable);

JS_PUBLIC_API(bool)
JS_ClearStructuredClone(const uint64_t *data, size_t nbytes);

JS_PUBLIC_API(bool)
JS_StructuredCloneHasTransferables(const uint64_t *data, size_t nbytes, bool *hasTransferable);

JS_PUBLIC_API(bool)
JS_StructuredClone(JSContext *cx, JS::HandleValue v, JS::MutableHandleValue vp,
                   const JSStructuredCloneCallbacks *optionalCallbacks, void *closure);

// RAII sugar for JS_WriteStructuredClone.
class JS_PUBLIC_API(JSAutoStructuredCloneBuffer) {
    uint64_t *data_;
    size_t nbytes_;
    uint32_t version_;

  public:
    JSAutoStructuredCloneBuffer()
        : data_(nullptr), nbytes_(0), version_(JS_STRUCTURED_CLONE_VERSION) {}

    ~JSAutoStructuredCloneBuffer() { clear(); }

    uint64_t *data() const { return data_; }
    size_t nbytes() const { return nbytes_; }

    void clear();

    // Copy some memory. It will be automatically freed by the destructor.
    bool copy(const uint64_t *data, size_t nbytes, uint32_t version=JS_STRUCTURED_CLONE_VERSION);

    // Adopt some memory. It will be automatically freed by the destructor.
    // data must have been allocated by the JS engine (e.g., extracted via
    // JSAutoStructuredCloneBuffer::steal).
    void adopt(uint64_t *data, size_t nbytes, uint32_t version=JS_STRUCTURED_CLONE_VERSION);

    // Remove the buffer so that it will not be automatically freed.
    // After this, the caller is responsible for feeding the memory back to
    // JSAutoStructuredCloneBuffer::adopt.
    void steal(uint64_t **datap, size_t *nbytesp, uint32_t *versionp=nullptr);

    bool read(JSContext *cx, JS::MutableHandleValue vp,
              const JSStructuredCloneCallbacks *optionalCallbacks=nullptr, void *closure=nullptr);

    bool write(JSContext *cx, JS::HandleValue v,
               const JSStructuredCloneCallbacks *optionalCallbacks=nullptr, void *closure=nullptr);

    bool write(JSContext *cx, JS::HandleValue v, JS::HandleValue transferable,
               const JSStructuredCloneCallbacks *optionalCallbacks=nullptr, void *closure=nullptr);

    // Swap ownership with another JSAutoStructuredCloneBuffer.
    void swap(JSAutoStructuredCloneBuffer &other);

  private:
    // Copy and assignment are not supported.
    JSAutoStructuredCloneBuffer(const JSAutoStructuredCloneBuffer &other);
    JSAutoStructuredCloneBuffer &operator=(const JSAutoStructuredCloneBuffer &other);
};

// The range of tag values the application may use for its own custom object types.
#define JS_SCTAG_USER_MIN  ((uint32_t) 0xFFFF8000)
#define JS_SCTAG_USER_MAX  ((uint32_t) 0xFFFFFFFF)

#define JS_SCERR_RECURSION 0
#define JS_SCERR_TRANSFERABLE 1

JS_PUBLIC_API(void)
JS_SetStructuredCloneCallbacks(JSRuntime *rt, const JSStructuredCloneCallbacks *callbacks);

JS_PUBLIC_API(bool)
JS_ReadUint32Pair(JSStructuredCloneReader *r, uint32_t *p1, uint32_t *p2);

JS_PUBLIC_API(bool)
JS_ReadBytes(JSStructuredCloneReader *r, void *p, size_t len);

JS_PUBLIC_API(bool)
JS_ReadTypedArray(JSStructuredCloneReader *r, JS::Value *vp);

JS_PUBLIC_API(bool)
JS_WriteUint32Pair(JSStructuredCloneWriter *w, uint32_t tag, uint32_t data);

JS_PUBLIC_API(bool)
JS_WriteBytes(JSStructuredCloneWriter *w, const void *p, size_t len);

JS_PUBLIC_API(bool)
JS_WriteTypedArray(JSStructuredCloneWriter *w, JS::Value v);

#endif  /* js_StructuredClone_h */
