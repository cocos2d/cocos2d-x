/* libs/graphics/animator/SkDisplayable.h
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

#ifndef SkDisplayable_DEFINED
#define SkDisplayable_DEFINED

#include "SkOperand.h"
#ifdef SK_DEBUG
#include "SkString.h"
#endif
#include "SkIntArray.h"
#include "SkRect.h"
#include "SkTDArray.h"

class SkAnimateMaker;
class SkApply;
class SkEvents;
struct SkMemberInfo;
struct SkScriptValue;
class SkOpArray; // compiled scripting experiment
union SkOperand2; // compiled scripting experiment

class SkDisplayable {
public:
#ifdef SK_DEBUG
    SkDisplayable();
#endif
    virtual ~SkDisplayable();
    virtual bool add(SkAnimateMaker& , SkDisplayable* child);
    virtual bool canContainDependents() const;
    virtual bool childrenNeedDisposing() const;
    virtual void clearBounder();
    virtual bool contains(SkDisplayable* );
    virtual SkDisplayable* contains(const SkString& );
    virtual SkDisplayable* deepCopy(SkAnimateMaker* );
    virtual void dirty();
#ifdef SK_DUMP_ENABLED
    virtual void dump(SkAnimateMaker* );
    void dumpAttrs(SkAnimateMaker* );
    void dumpBase(SkAnimateMaker* );
    void dumpChildren(SkAnimateMaker* maker, bool closedAngle = false );
    void dumpEnd(SkAnimateMaker* );
    virtual void dumpEvents();
#endif
    virtual bool enable( SkAnimateMaker& );
    virtual void enableBounder();
    virtual void executeFunction(SkDisplayable* , int functionIndex, 
        SkTDArray<SkScriptValue>& , SkDisplayTypes , SkScriptValue* ); 
    void executeFunction(SkDisplayable* , const SkMemberInfo* , 
        SkTypedArray* , SkScriptValue* ); 
    virtual void executeFunction2(SkDisplayable* , int functionIndex, 
        SkOpArray* params , SkDisplayTypes , SkOperand2* ); // compiled scripting experiment
    virtual void getBounds(SkRect* );
    virtual const SkFunctionParamType* getFunctionsParameters();
    virtual const SkMemberInfo* getMember(int index);
    virtual const SkMemberInfo* getMember(const char name[]);
    const SkFunctionParamType* getParameters(const SkMemberInfo* info, 
        int* paramCount);
    virtual SkDisplayable* getParent() const;
    virtual bool getProperty(int index, SkScriptValue* value) const;
    virtual bool getProperty2(int index, SkOperand2* value) const;    // compiled scripting experiment
    virtual SkDisplayTypes getType() const;
    virtual bool hasEnable() const;
    bool isAnimate() const { 
        SkDisplayTypes type = getType(); 
        return type == SkType_Animate || type == SkType_Set; }
    bool isApply() const { return getType() == SkType_Apply; }
    bool isColor() const { return getType() == SkType_Color; }
    virtual bool isDrawable() const;
    bool isGroup() const { return getType() == SkType_Group || 
        getType() == SkType_Save || getType() == SkType_DrawTo ||
        getType() == SkType_SaveLayer; }
    bool isMatrix() const { return getType() == SkType_Matrix; }
    virtual bool isPaint() const { return getType() == SkType_Paint; }
    virtual bool isPath() const { return false; }
    bool isPost() const { return getType() == SkType_Post; }
    virtual void onEndElement(SkAnimateMaker& );
    virtual const SkMemberInfo* preferredChild(SkDisplayTypes type);
    virtual bool resolveIDs(SkAnimateMaker& maker, SkDisplayable* original, SkApply* );
    virtual void setChildHasID();
    virtual bool setParent(SkDisplayable* );
    virtual bool setProperty(int index, SkScriptValue& );
    void setReference(const SkMemberInfo* info, SkDisplayable* ref);
#ifdef SK_DEBUG
    bool isDataInput() const { return getType() == SkType_DataInput; };
    bool isEvent() const { return getType() == SkType_Event; }
    virtual bool isMatrixPart() const { return false; }
    bool isPatch() const { return getType() == SkType_3D_Patch; }
    virtual bool isPaintPart() const { return false; }
    virtual bool isPathPart() const { return false; }
    virtual void validate();
    SkString _id;
    const char* id;
//  static int fAllocationCount;
    static SkTDDisplayableArray fAllocations;
#else
    void validate() {}
#endif
#ifdef SK_DUMP_ENABLED
private:
    void dumpValues(const SkMemberInfo* info, SkDisplayTypes type, SkOperand op, SkOperand blankOp,
        SkOperand op2, SkOperand blankOp2);
#endif
};

#endif // SkDisplayable_DEFINED
