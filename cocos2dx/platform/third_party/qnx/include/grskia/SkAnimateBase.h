/* libs/graphics/animator/SkAnimateBase.h
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

#ifndef SkAnimateBase_DEFINED
#define SkAnimateBase_DEFINED

#include "SkDisplayable.h"
#include "SkMath.h"
#include "SkMemberInfo.h"
#include "SkTypedArray.h"

class SkApply;
class SkDrawable;

class SkAnimateBase : public SkDisplayable {
public:
    DECLARE_MEMBER_INFO(AnimateBase);
    SkAnimateBase();
    virtual ~SkAnimateBase();
    virtual int components();
    virtual SkDisplayable* deepCopy(SkAnimateMaker* );
    virtual void dirty();
#ifdef SK_DUMP_ENABLED
    virtual void dump(SkAnimateMaker* );
#endif
    int entries() { return fValues.count() / components(); }
    virtual bool hasExecute() const;
    bool isDynamic() const { return SkToBool(fDynamic); }
    virtual SkDisplayable* getParent() const;
    virtual bool getProperty(int index, SkScriptValue* value) const;
    SkMSec getStart() const { return fStart; }
    SkOperand* getValues() { return fValues.begin(); }
    SkDisplayTypes getValuesType() { return fValues.getType(); }
    virtual void onEndElement(SkAnimateMaker& );
    void packARGB(SkScalar [], int count, SkTDOperandArray* );
    virtual void refresh(SkAnimateMaker& );
    void setChanged(bool changed) { fChanged = changed; }
    void setHasEndEvent() { fHasEndEvent = true; }
    virtual bool setParent(SkDisplayable* );
    virtual bool setProperty(int index, SkScriptValue& value);
    void setTarget(SkAnimateMaker& );
    virtual bool targetNeedsInitialization() const;
protected:
    SkMSec begin;
    SkTDScalarArray blend;
    SkMSec dur;
    // !!! make field part of a union with fFieldInfo, or fValues, something known later?
    SkString field; // temporary; once target is known, this is reset
    SkString formula;
    SkString from;
    SkString lval;
    SkScalar repeat;
    SkString target;    // temporary; once target is known, this is reset
    SkString to;
    SkApply* fApply;
    const SkMemberInfo* fFieldInfo;
    int fFieldOffset;
    SkMSec fStart;  // corrected time when this apply was enabled
    SkDrawable* fTarget;
    SkTypedArray fValues;
    unsigned fChanged : 1; // true when value referenced by script has changed
    unsigned fDelayed : 1;  // enabled, but undrawn pending delay
    unsigned fDynamic : 1;
    unsigned fHasEndEvent : 1;
    unsigned fHasValues : 1;        // set if 'values' passed instead of 'to'
    unsigned fMirror : 1;
    unsigned fReset : 1;
    unsigned fResetPending : 1;
    unsigned fTargetIsScope : 1;
private:
    typedef SkDisplayable INHERITED;
    friend class SkActive;
    friend class SkApply;
    friend class SkDisplayList;
};

#endif // SkAnimateBase_DEFINED
