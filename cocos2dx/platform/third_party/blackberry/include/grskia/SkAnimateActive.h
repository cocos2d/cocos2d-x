/* libs/graphics/animator/SkAnimateActive.h
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

#ifndef SkAnimateActive_DEFINED
#define SkAnimateActive_DEFINED

#include "SkDisplayApply.h"
#include "SkOperandInterpolator.h"
#include "SkIntArray.h"

class SkAnimateMaker;

class SkActive {
public:
    SkActive(SkApply& , SkAnimateMaker& );
    ~SkActive();
    void advance();
    void append(SkApply* );
    void calcDurations(int index);
    void create(SkDrawable* scope, SkMSec time);
    bool draw() { return immediate(false); }
    bool enable() { return immediate(true); }
    void init( );
    SkMSec getTime(SkMSec inTime, int animatorIndex);
    void pickUp(SkActive* existing);
    void reset() { fDrawIndex = 0; }
    void setInterpolator(int index, SkOperand* from);
    void start();
#ifdef SK_DEBUG
    void validate();
#endif
private:
    void appendSave(int oldCount);
    void fixInterpolator(SkBool save);
    bool immediate(bool enable);
    bool initializeSave();
    void initState(SkApply* , int offset);
    void resetInterpolators();
    void resetState();
    void restoreInterpolatorValues(int index);
    void saveInterpolatorValues(int index);
    void setSteps(int steps);
    struct SkState {
//      void bumpSave();
        SkMSec getRelativeTime(SkMSec time);
        SkApply::Mode fMode;
        SkApply::Transition fTransition;
        SkBool8 fPickup;
        SkBool8 fRestore;
        SkBool8 fStarted;
        SkBool8 fUnpostedEndEvent;
        int32_t fSteps;
        SkMSec fBegin;
        SkMSec fStartTime;
        SkMSec fDuration;
        SkMSec fSave;
        SkMSec fTicks;
    };
    SkActive& operator= (const SkActive& );
    SkTDArray<SkOperandInterpolator*> fInterpolators;
    SkApply& fApply;
    SkTDArray<SkState> fState;  // one per animator
    SkTDOperandPtrArray fSaveRestore;   // if apply has restore="true"
    SkTDOperandPtrArray fSaveInterpolators;
    SkTDAnimateArray fAnimators;
    SkMSec fMaxTime;    // greatest of all animation durations; only used by immediate mode
    SkAnimateMaker& fMaker;
    int fDrawIndex;
    int fDrawMax;
    friend class SkApply;
};

#endif // SkAnimateActive_DEFINED
