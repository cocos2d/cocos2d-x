/* libs/graphics/animator/SkDrawTo.h
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

#ifndef SkDrawTo_DEFINED
#define SkDrawTo_DEFINED

#include "SkDrawGroup.h"
#include "SkMemberInfo.h"

class SkDrawBitmap;

class SkDrawTo : public SkGroup {
    DECLARE_MEMBER_INFO(DrawTo);
    SkDrawTo();
//  virtual ~SkDrawTo();
    virtual bool draw(SkAnimateMaker& );
#ifdef SK_DUMP_ENABLED
    virtual void dump(SkAnimateMaker* );
#endif
protected:
    SkBool drawOnce;
    SkDrawBitmap* use;
private:
    typedef SkGroup INHERITED;
    SkBool fDrawnOnce;
};

#endif // SkDrawTo_DEFINED
