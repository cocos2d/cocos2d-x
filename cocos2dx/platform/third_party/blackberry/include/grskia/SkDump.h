/* libs/graphics/animator/SkDump.h
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

#ifndef SkDump_DEFINED
#define SkDump_DEFINED

#include "SkDisplayable.h"
#include "SkMemberInfo.h"

class SkAnimateMaker;
class SkString;

class SkDump : public SkDisplayable {
    DECLARE_MEMBER_INFO(Dump);
#ifdef SK_DUMP_ENABLED
    SkDump();
    virtual bool enable(SkAnimateMaker & );
    bool evaluate(SkAnimateMaker &);
    virtual bool hasEnable() const;
    static void GetEnumString(SkDisplayTypes , int index, SkString* result);
    SkBool displayList;
    SkBool eventList;
    SkBool events;
    SkString name;
    SkBool groups;
    SkBool posts;
    SkString script;
#else
    virtual bool enable(SkAnimateMaker & );
    virtual bool hasEnable() const;
    virtual bool setProperty(int index, SkScriptValue& );
#endif
};


#endif // SkDump_DEFINED

