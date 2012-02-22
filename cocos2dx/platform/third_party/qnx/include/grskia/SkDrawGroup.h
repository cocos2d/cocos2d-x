/* libs/graphics/animator/SkDrawGroup.h
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

#ifndef SkDrawGroup_DEFINED
#define SkDrawGroup_DEFINED

#include "SkDrawable.h"
#include "SkIntArray.h"
#include "SkMemberInfo.h"

class SkGroup : public SkDrawable { //interface for schema element <g>
public:
    DECLARE_MEMBER_INFO(Group);
    SkGroup();
    virtual ~SkGroup();
    virtual bool add(SkAnimateMaker& , SkDisplayable* child);
    virtual bool contains(SkDisplayable* );
    SkGroup* copy();
    SkBool copySet(int index);
    virtual SkDisplayable* deepCopy(SkAnimateMaker* );
    virtual bool doEvent(SkDisplayEvent::Kind , SkEventState* state );
    virtual bool draw(SkAnimateMaker& );
#ifdef SK_DUMP_ENABLED
    virtual void dump(SkAnimateMaker* );
    virtual void dumpDrawables(SkAnimateMaker* );
    virtual void dumpEvents();
#endif
    int findGroup(SkDrawable* drawable,  SkTDDrawableArray** list,
        SkGroup** parent, SkGroup** found, SkTDDrawableArray** grandList);
    virtual bool enable(SkAnimateMaker& );
    SkTDDrawableArray* getChildren() { return &fChildren; }
    SkGroup* getOriginal() { return fOriginal; }
    virtual bool hasEnable() const;
    virtual void initialize();
    SkBool isACopy() { return fOriginal != NULL; }
    void markCopyClear(int index);
    void markCopySet(int index);
    void markCopySize(int index);
    bool markedForDelete(int index) const { return (fCopies[index >> 5] & 1 << (index & 0x1f)) == 0; }
    void reset();
    bool resolveIDs(SkAnimateMaker& maker, SkDisplayable* original, SkApply* );
    virtual void setSteps(int steps);
#ifdef SK_DEBUG
    virtual void validate();
#endif
protected:
    bool ifCondition(SkAnimateMaker& maker, SkDrawable* drawable,
        SkString& conditionString);
    SkString condition;
    SkString enableCondition;
    SkTDDrawableArray fChildren;
    SkTDDrawableArray* fParentList;
    SkTDIntArray fCopies;
    SkGroup* fOriginal;
private:
    typedef SkDrawable INHERITED;
};

class SkSave: public SkGroup {
    DECLARE_MEMBER_INFO(Save);
    virtual bool draw(SkAnimateMaker& );
private:
    typedef SkGroup INHERITED;
};

#endif // SkDrawGroup_DEFINED
