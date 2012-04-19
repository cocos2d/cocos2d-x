/* libs/graphics/animator/SkDrawText.h
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

#ifndef SkDrawText_DEFINED
#define SkDrawText_DEFINED

#include "SkBoundable.h"
#include "SkMemberInfo.h"

class SkText : public SkBoundable {
    DECLARE_MEMBER_INFO(Text);
    SkText();
    virtual ~SkText();
    virtual bool draw(SkAnimateMaker& );
#ifdef SK_DUMP_ENABLED
    virtual void dump(SkAnimateMaker* );
#endif
    virtual bool getProperty(int index, SkScriptValue* value) const ; 
    const char* getText() { return text.c_str(); }
    size_t getSize() { return text.size(); }
protected:
    SkString text;
    SkScalar x;
    SkScalar y;
private:
    friend class SkTextToPath;
    typedef SkBoundable INHERITED;
};

#endif // SkDrawText_DEFINED
