/* libs/graphics/animator/SkDrawPoint.h
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

#ifndef SkDrawPoint_DEFINED
#define SkDrawPoint_DEFINED

#include "SkBoundable.h"
#include "SkMemberInfo.h"
#include "SkPoint.h"

struct Sk_Point {
    DECLARE_NO_VIRTUALS_MEMBER_INFO(_Point);
    Sk_Point();
private:
    SkPoint fPoint;
};

class SkDrawPoint : public SkDisplayable {
    DECLARE_MEMBER_INFO(DrawPoint);
    SkDrawPoint();
    virtual void getBounds(SkRect*  );
private:
    SkPoint fPoint;
    typedef SkDisplayable INHERITED;
};

#endif // SkDrawPoint_DEFINED
