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

#ifndef SkRefDict_DEFINED
#define SkRefDict_DEFINED

#include "SkRefCnt.h"

/**
 *  A dictionary of string,refcnt pairs. The dictionary is also an owner of the
 *  refcnt objects while they are contained.
 */
class SK_API SkRefDict : SkNoncopyable {
public:
    SkRefDict();
    ~SkRefDict();

    /**
     *  Return the data associated with name[], or NULL if no matching entry
     *  is found. The reference-count of the entry is not affected.
     */
    SkRefCnt* find(const char name[]) const;
    
    /**
     *  If data is NULL, remove (if present) the entry matching name and call
     *  prev_data->unref() on the data for the matching entry.
     *  If data is not-NULL, replace the existing entry matching name and
     *  call (prev_data->unref()), or add a new one. In either case,
     *  data->ref() is called.
     */
    void set(const char name[], SkRefCnt* data);

    /**
     *  Remove the matching entry (if found) and unref its data.
     */
    void remove(const char name[]) { this->set(name, NULL); }

    /**
     *  Remove all entries, and unref() their associated data.
     */
    void removeAll();

private:
    struct Impl;
    Impl* fImpl;
};

#endif
