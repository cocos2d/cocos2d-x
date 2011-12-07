/* libs/graphics/animator/SkDrawLine.h
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

#ifndef SkDrawLine_DEFINED
#define SkDrawLine_DEFINED

#include "SkBoundable.h"
#include "SkMemberInfo.h"

class SkLine : public SkBoundable {
    DECLARE_MEMBER_INFO(Line);
    SkLine();
    virtual bool draw(SkAnimateMaker& );
private:
    SkScalar x1;
    SkScalar x2;
    SkScalar y1;
    SkScalar y2;
    typedef SkBoundable INHERITED;
};

#endif // SkDrawLine_DEFINED

