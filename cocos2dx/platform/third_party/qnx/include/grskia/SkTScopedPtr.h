/*
 * Copyright (C) 2011 Google Inc.
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

#ifndef SkTScopedPtr_DEFINED
#define SkTScopedPtr_DEFINED

#include "SkTypes.h"

/** \class SkTScopedPtr
  A SkTScopedPtr<T> is like a T*, except that the destructor of SkTScopedPtr<T>
  automatically deletes the pointer it holds (if any).  That is, SkTScopedPtr<T>
  owns the T object that it points to.  Like a T*, a SkTScopedPtr<T> may hold
  either NULL or a pointer to a T object.  Also like T*, SkTScopedPtr<T> is
  thread-compatible, and once you dereference it, you get the threadsafety
  guarantees of T.

  The size of a SkTScopedPtr is small: sizeof(SkTScopedPtr<T>) == sizeof(T*)
*/
template <typename T> class SkTScopedPtr : SkNoncopyable {
public:
    explicit SkTScopedPtr(T* o = NULL) : fObj(o) {}
    ~SkTScopedPtr() {
        enum { kTypeMustBeComplete = sizeof(T) };
        delete fObj;
    }

    /** Delete the current object, if any.  Then take ownership of the
        passed object.
     */
    void reset(T* o = NULL) {
        if (o != fObj) {
            enum { kTypeMustBeComplete = sizeof(T) };
            delete fObj;
            fObj = o;
        }
    }

    /** Without deleting the current object, return it and forget about it.
        Similar to calling get() and reset(), but the object is not deleted.
     */
    T* release() {
        T* retVal = fObj;
        fObj = NULL;
        return retVal;
    }

    T& operator*() const {
        SkASSERT(fObj != NULL);
        return *fObj;
    }
    T* operator->() const  {
        SkASSERT(fObj != NULL);
        return fObj;
    }
    T* get() const { return fObj; }

    bool operator==(T* o) const { return fObj == o; }
    bool operator!=(T* o) const { return fObj != o; }

private:
    T* fObj;

    // Forbid comparison of SkTScopedPtr types.  If T2 != T, it doesn't make
    // sense, and if T2 == T, it still doesn't make sense because the same
    // object can't be owned by two different scoped_ptrs.
    template <class T2> bool operator==(SkTScopedPtr<T2> const& o2) const;
    template <class T2> bool operator!=(SkTScopedPtr<T2> const& o2) const;
};

#endif
