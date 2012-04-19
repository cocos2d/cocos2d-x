/* libs/graphics/animator/SkDisplayEvent.h
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

#ifndef SkDisplayEvent_DEFINED
#define SkDisplayEvent_DEFINED

#include "SkDisplayable.h"
#include "SkMemberInfo.h"
#include "SkIntArray.h"
#include "SkKey.h"

class SkEvent;

class SkDisplayEvent : public SkDisplayable {
    DECLARE_DISPLAY_MEMBER_INFO(Event);
    enum Kind {
        kNo_kind,
        kKeyChar,
        kKeyPress,
        kKeyPressUp,    //i assume the order here is intended to match with skanimatorscript.cpp
        kMouseDown,
        kMouseDrag,
        kMouseMove,
        kMouseUp,
        kOnEnd,
        kOnload,
        kUser
    };
    SkDisplayEvent();
    virtual ~SkDisplayEvent();
    virtual bool add(SkAnimateMaker& , SkDisplayable* child);
    virtual bool contains(SkDisplayable*);
    virtual SkDisplayable* contains(const SkString& );
#ifdef SK_DEBUG
    void dumpEvent(SkAnimateMaker* );
#endif
    bool enableEvent(SkAnimateMaker& );
    virtual bool getProperty(int index, SkScriptValue* ) const;
    virtual void onEndElement(SkAnimateMaker& maker);
    void populateInput(SkAnimateMaker& , const SkEvent& fEvent);
    virtual bool setProperty(int index, SkScriptValue& );
protected:
    SkKey code;
    SkBool disable;
    Kind kind;
    SkString target;
    SkScalar x;
    SkScalar y;
    SkTDDisplayableArray fChildren;
    mutable SkString fKeyString;
    SkKey fLastCode; // last key to trigger this event
    SkKey fMax; // if the code expresses a range
    SkDisplayable* fTarget; // used by onEnd
private:
    void deleteMembers();
    friend class SkEvents;
    typedef SkDisplayable INHERITED;
};

#endif // SkDisplayEvent_DEFINED

