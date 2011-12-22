/* libs/graphics/sgl/SkTemplatesPriv.h
**
** Copyright 2006, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License"); 
** you may not use this file except in compliance with the License. 
** You may obtain a copy of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** Unless required by applicable law or agreed to in writing, software 
** distributed under the License is distributed on an "AS IS" BASIS, 
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
** See the License for the specific language governing permissions and 
** limitations under the License.
*/

#ifndef SkTemplatesPriv_DEFINED
#define SkTemplatesPriv_DEFINED

#include "SkTemplates.h"

////////////////////////////////////////////////////////////////////////////////

#ifdef SK_BUILD_FOR_WIN32
    #define SK_PLACEMENT_NEW(result, classname, storage, storageSize)   \
        result = SkNEW(classname)

    #define SK_PLACEMENT_NEW_ARGS(result, classname, storage, storageSize, args)    \
        result = SkNEW_ARGS(classname, args)
#else
    #include <new>
    #define SK_PLACEMENT_NEW(result, classname, storage, storagesize)       \
    do {                                                                    \
        if (storagesize)                                                    \
        {                                                                   \
            SkASSERT(storageSize >= sizeof(classname));                     \
            result = new(storage) classname;                                \
        }                                                                   \
        else                                                                \
            result = SkNEW(classname);                                      \
    } while (0)

    #define SK_PLACEMENT_NEW_ARGS(result, classname, storage, storagesize, args)        \
    do {                                                                                \
        if (storagesize)                                                                \
        {                                                                               \
            SkASSERT(storageSize >= sizeof(classname));                                 \
            result = new(storage) classname args;                                       \
        }                                                                               \
        else                                                                            \
            result = SkNEW_ARGS(classname, args);                                       \
    } while (0)
#endif

////////////////////////////////////////////////////////////////////////////////

template <class T> class SkAutoTPlacementDelete {
public:
    SkAutoTPlacementDelete(T* obj, void* storage) : fObj(obj), fStorage(storage)
    {
    }
    ~SkAutoTPlacementDelete()
    {
        if (fObj)
        {
            if (fObj == fStorage)
                fObj->~T();
            else
                delete fObj;
        }
    }
    T* detach()
    {
        T*  obj = fObj;
        fObj = NULL;
        return obj;
    }
private:
    T*      fObj;
    void*   fStorage;
};

#endif
