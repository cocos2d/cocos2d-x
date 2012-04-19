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


#ifndef GrInstanceCounter_DEFINED
#define GrInstanceCounter_DEFINED

#include "GrTypes.h"

template <typename T> class GrInstanceCounter {
public:
    GrInstanceCounter() {
        ++gCounter;
        GrPrintf("+ %s %d\n", T::InstanceCounterClassName(), gCounter);
    }

    ~GrInstanceCounter() {
        --gCounter;
        GrPrintf("- %s %d\n", T::InstanceCounterClassName(), gCounter);
    }

private:
    static int gCounter;
};

template <typename T> int GrInstanceCounter<T>::gCounter;

#define DECLARE_INSTANCE_COUNTER(T)                                 \
    static const char* InstanceCounterClassName() { return #T; }    \
    friend class GrInstanceCounter<T>;                              \
    GrInstanceCounter<T> fInstanceCounter

#endif

