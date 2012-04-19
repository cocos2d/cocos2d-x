/* libs/graphics/animator/SkSnapshot.h
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

#ifndef SkSnapShot_DEFINED
#define SkSnapShot_DEFINED

#include "SkDrawable.h"
#include "SkImageDecoder.h"
#include "SkMemberInfo.h"
#include "SkString.h"

class SkSnapshot: public SkDrawable {
    DECLARE_MEMBER_INFO(Snapshot);
    SkSnapshot();
    virtual bool draw(SkAnimateMaker& );
    private:
    SkString filename;
    SkScalar quality;
    SkBool sequence;
    int /*SkImageEncoder::Type*/    type;
    int fSeqVal;
};

#endif // SkSnapShot_DEFINED

