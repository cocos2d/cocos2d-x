/* libs/graphics/animator/SkDrawable.h
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

#ifndef SkDrawable_DEFINED
#define SkDrawable_DEFINED

#include "SkDisplayable.h"
#include "SkDisplayEvent.h"
#include "SkMath.h"

struct SkEventState;

class SkDrawable :  public SkDisplayable {
public:
    virtual bool doEvent(SkDisplayEvent::Kind , SkEventState* state );
    virtual bool draw(SkAnimateMaker& ) = 0; 
    virtual void initialize();
    virtual bool isDrawable() const;
    virtual void setSteps(int steps);
};

#endif // SkDrawable_DEFINED
