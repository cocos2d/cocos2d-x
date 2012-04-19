/* libs/graphics/animator/SkDisplayTypes.h
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

#ifndef SkDisplayTypes_DEFINED
#define SkDisplayTypes_DEFINED

#include "SkDisplayable.h"
#include "SkMemberInfo.h"
#include "SkTypedArray.h"

class SkOpArray; // compiled script experiment


class SkDisplayDepend : public SkDisplayable {
public:
    virtual bool canContainDependents() const;
    void addDependent(SkDisplayable* displayable) {
        if (fDependents.find(displayable) < 0)
            *fDependents.append() = displayable;
    }
    virtual void dirty();
private:
    SkTDDisplayableArray fDependents;
    typedef SkDisplayable INHERITED;
};

class SkDisplayBoolean : public SkDisplayDepend {
    DECLARE_DISPLAY_MEMBER_INFO(Boolean);
    SkDisplayBoolean();
#ifdef SK_DUMP_ENABLED
    virtual void dump(SkAnimateMaker* );
#endif
    SkBool value;
    friend class SkAnimatorScript;
    friend class SkAnimatorScript_Box;
    friend class SkAnimatorScript_Unbox;
    typedef SkDisplayDepend INHERITED;
};

class SkDisplayInt : public SkDisplayDepend {
    DECLARE_DISPLAY_MEMBER_INFO(Int);
    SkDisplayInt();
#ifdef SK_DUMP_ENABLED
    virtual void dump(SkAnimateMaker* );
#endif
private:
    int32_t value;
    friend class SkAnimatorScript;
    friend class SkAnimatorScript_Box;
    friend class SkAnimatorScript_Unbox;
    typedef SkDisplayDepend INHERITED;
};

class SkDisplayFloat : public SkDisplayDepend {
    DECLARE_DISPLAY_MEMBER_INFO(Float);
    SkDisplayFloat();
#ifdef SK_DUMP_ENABLED
    virtual void dump(SkAnimateMaker* );
#endif
private:
    SkScalar value;
    friend class SkAnimatorScript;
    friend class SkAnimatorScript_Box;
    friend class SkAnimatorScript_Unbox;
    typedef SkDisplayDepend INHERITED;
};

class SkDisplayString : public SkDisplayDepend {
    DECLARE_DISPLAY_MEMBER_INFO(String);
    SkDisplayString();
    SkDisplayString(SkString& );
    virtual void executeFunction(SkDisplayable* , int index, 
        SkTDArray<SkScriptValue>& parameters, SkDisplayTypes type,
        SkScriptValue* );
    virtual const SkFunctionParamType* getFunctionsParameters();
    virtual bool getProperty(int index, SkScriptValue* ) const;
    SkString value;
private:
    static const SkFunctionParamType fFunctionParameters[];
};

class SkDisplayArray : public SkDisplayDepend {
    DECLARE_DISPLAY_MEMBER_INFO(Array);
    SkDisplayArray();
    SkDisplayArray(SkTypedArray& );
    SkDisplayArray(SkOpArray& ); // compiled script experiment
    virtual ~SkDisplayArray();
    virtual bool getProperty(int index, SkScriptValue* ) const;
private:
    SkTypedArray values;
    friend class SkAnimator;
    friend class SkAnimatorScript;
    friend class SkAnimatorScript2;
    friend class SkAnimatorScript_Unbox;
    friend class SkDisplayable;
    friend struct SkMemberInfo;
    friend class SkScriptEngine;
};

#endif // SkDisplayTypes_DEFINED

