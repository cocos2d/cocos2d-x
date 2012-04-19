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


#ifndef GrTLList_DEFINED
#define GrTLList_DEFINED

#include "GrNoncopyable.h"

template <typename T> class GrTLList : GrNoncopyable {
public:
    class Entry {
        Entry*  fPrev;
        Entry*  fNext;
    };

    GrTLList() : fHead(NULL), fTail(NULL) {}
#if GR_DEBUG
    ~GrTLList() {
        GrAssert(NULL == fHead);
        GrAssert(NULL == ftail);
    }
#endif

    T*  head() const { return fHead; }
    T*  tail() const { return fTail; }
    
    void addToHead(T*);
    void addToTail(T*);
    void removeFromList(T*);

private:
    Entry*  fHead;
    Entry*  fTail;

    friend class Entry;
};


class Parent {
    GrTDLList<Child>    fList;
};

class Child : public GrTLList::Entry<Child> {
};

#endif

