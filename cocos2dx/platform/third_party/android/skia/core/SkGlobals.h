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

#ifndef SkGlobals_DEFINED
#define SkGlobals_DEFINED

#include "SkThread.h"

class SkGlobals {
public:
    class Rec {
    public:
        virtual ~Rec();
    private:
        Rec*        fNext;
        uint32_t    fTag;

        friend class SkGlobals;
    };

    /** Look for a matching Rec for the specified tag. If one is found, return it.
        If one is not found, if create_proc is null, return null, else
        call the proc, and if it returns a Rec, add it to the global list
        and return it.

        create_proc can NOT call back into SkGlobals::Find (it would deadlock)
    */
    static Rec* Find(uint32_t tag, Rec* (*create_proc)());
    /** Helper for Find, when you want to assert that the Rec is already in the list
    */
    static Rec* Get(uint32_t tag)
    {
        Rec* rec = SkGlobals::Find(tag, NULL);
        SkASSERT(rec);
        return rec;
    }

    // used by porting layer
    struct BootStrap {
        SkMutex fMutex;
        Rec*    fHead;
    };

private:
    static void Init();
    static void Term();
    friend class SkGraphics;

    //  This last function is implemented in the porting layer
    static BootStrap& GetBootStrap();
};

#endif

