/* libs/graphics/animator/SkAnimate.h
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

#ifndef SkAnimate_DEFINED
#define SkAnimate_DEFINED

#include "SkAnimateBase.h"
#include "SkDisplayType.h"
#include "SkIntArray.h"
#include "SkUtils.h"

class SkAnimate : public SkAnimateBase {
    DECLARE_MEMBER_INFO(Animate);
    SkAnimate();
    virtual ~SkAnimate();
    virtual int components();
#ifdef SK_DUMP_ENABLED
    virtual void dump(SkAnimateMaker* );
#endif
    virtual void onEndElement(SkAnimateMaker& maker);
protected:
    bool resolveCommon(SkAnimateMaker& );
    int fComponents;
private:
    typedef SkAnimateBase INHERITED;
};

#endif // SkAnimateField_DEFINED

