/* libs/graphics/animator/SkDisplayList.h
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

#ifndef SkDisplayList_DEFINED
#define SkDisplayList_DEFINED

#include "SkOperand.h"
#include "SkIntArray.h"
#include "SkBounder.h"
#include "SkRect.h"

class SkAnimateMaker;
class SkActive;
class SkApply;
class SkDrawable;
class SkGroup;

class SkDisplayList : public SkBounder {
public:
    SkDisplayList();
    virtual ~SkDisplayList();
    void append(SkActive* );
    void clear() { fDrawList.reset(); }
    int count() { return fDrawList.count(); }
    bool draw(SkAnimateMaker& , SkMSec time);
#ifdef SK_DUMP_ENABLED
    void dump(SkAnimateMaker* maker);
    void dumpInner(SkAnimateMaker* maker);
    static int fIndent;
    static int fDumpIndex;
#endif
    int findGroup(SkDrawable* match, SkTDDrawableArray** list, 
        SkGroup** parent, SkGroup** found, SkTDDrawableArray** grandList); 
    SkDrawable* get(int index) { return fDrawList[index]; }
    SkMSec getTime() { return fInTime; }
    SkTDDrawableArray* getDrawList() { return &fDrawList; }
    void hardReset();
    virtual bool onIRect(const SkIRect& r);
    void reset();
    void remove(SkActive* );
#ifdef SK_DEBUG
    void validate();
#else
    void validate() {}
#endif
    static int SearchForMatch(SkDrawable* match, SkTDDrawableArray** list,
        SkGroup** parent, SkGroup** found, SkTDDrawableArray**grandList);
    static bool SearchGroupForMatch(SkDrawable* draw, SkDrawable* match, 
        SkTDDrawableArray** list, SkGroup** parent, SkGroup** found, SkTDDrawableArray** grandList, 
        int &index);
public:
    SkIRect fBounds;
    SkIRect fInvalBounds;
    bool fDrawBounds;
    bool fHasUnion;
    bool fUnionBounds;
private:
    SkTDDrawableArray fDrawList;
    SkTDActiveArray fActiveList;
    SkMSec fInTime;
    friend class SkEvents;
};

#endif // SkDisplayList_DEFINED

