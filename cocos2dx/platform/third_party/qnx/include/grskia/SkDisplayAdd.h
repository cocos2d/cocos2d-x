/* libs/graphics/animator/SkDisplayAdd.h
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

#ifndef SkDisplayAdd_DEFINED
#define SkDisplayAdd_DEFINED

#include "SkDrawable.h"
#include "SkMemberInfo.h"

class SkAdd : public SkDrawable {
    DECLARE_MEMBER_INFO(Add);
    SkAdd();
    
    enum Mode {
        kMode_indirect,
        kMode_immediate
    };
    
    virtual SkDisplayable* deepCopy(SkAnimateMaker* );
    virtual bool draw(SkAnimateMaker& );
#ifdef SK_DUMP_ENABLED
    virtual void dump(SkAnimateMaker* );
#endif
    virtual bool enable(SkAnimateMaker& );
    virtual bool hasEnable() const;
    virtual void initialize();
    virtual bool isDrawable() const;
protected:
//  struct _A {
        Mode mode;
        int32_t offset;
        SkDrawable* use;
        SkDrawable* where;  // if NULL, offset becomes index
//  } A;
private:
    typedef SkDrawable INHERITED;
};

class SkClear : public SkDisplayable {
    virtual bool enable(SkAnimateMaker& );
};

class SkMove : public SkAdd {
    DECLARE_MEMBER_INFO(Move);
private:
    typedef SkAdd INHERITED;
};

class SkRemove : public SkAdd {
    DECLARE_MEMBER_INFO(Remove);
    SkRemove();
protected:
    SkBool fDelete;
private:
    friend class SkAdd;
    typedef SkAdd INHERITED;
};

class SkReplace : public SkAdd {
    DECLARE_MEMBER_INFO(Replace);
private:
    typedef SkAdd INHERITED;
};

#endif // SkDisplayAdd_DEFINED


