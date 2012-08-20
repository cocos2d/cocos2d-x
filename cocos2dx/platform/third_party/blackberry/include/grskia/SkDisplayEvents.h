/* libs/graphics/animator/SkDisplayEvents.h
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

#ifndef SkDisplayEvents_DEFINED
#define SkDisplayEvents_DEFINED

#include "SkEvent.h"
#include "SkDisplayEvent.h"

struct SkEventState {
    SkEventState();
    int fCode;
    SkBool fDisable;
    SkDisplayable* fDisplayable;
    SkScalar fX;
    SkScalar fY;
};

class SkEvents {
public:
    SkEvents();
    ~SkEvents();
    void addEvent(SkDisplayEvent* evt) { *fEvents.append() = evt; }
    bool doEvent(SkAnimateMaker& , SkDisplayEvent::Kind , SkEventState* );
#ifdef SK_DUMP_ENABLED
    void dump(SkAnimateMaker& );
#endif
    void reset() { fEvents.reset(); }
    void removeEvent(SkDisplayEvent::Kind kind, SkEventState* );
private:
    SkTDDisplayEventArray fEvents;
    SkBool fError;
    friend class SkDisplayXMLParser;
};

#endif // SkDisplayEvents_DEFINED

