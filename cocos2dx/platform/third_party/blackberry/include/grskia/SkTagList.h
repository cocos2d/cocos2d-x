/* libs/graphics/views/SkTagList.h
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

#ifndef SkTagList_DEFINED
#define SkTagList_DEFINED

#include "SkTypes.h"

enum SkTagListEnum {
    kListeners_SkTagList,
    kViewLayout_SkTagList,
    kViewArtist_SkTagList,

    kSkTagListCount
};

struct SkTagList {
    SkTagList*  fNext;
    uint16_t    fExtra16;
    uint8_t     fExtra8;
    uint8_t     fTag;

    SkTagList(U8CPU tag) : fTag(SkToU8(tag))
    {
        SkASSERT(tag < kSkTagListCount);
        fNext       = NULL;
        fExtra16    = 0;
        fExtra8     = 0;
    }
    virtual ~SkTagList();

    static SkTagList*   Find(SkTagList* head, U8CPU tag);
    static void         DeleteTag(SkTagList** headptr, U8CPU tag);
    static void         DeleteAll(SkTagList* head);
};

#endif
