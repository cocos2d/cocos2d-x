/* libs/graphics/animator/SkOperandInterpolator.h
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

#ifndef SkOperandInterpolator_DEFINED
#define SkOperandInterpolator_DEFINED

#include "SkDisplayType.h"
#include "SkInterpolator.h"
#include "SkOperand.h"

class SkOperandInterpolator : public SkInterpolatorBase {
public:
    SkOperandInterpolator();
    SkOperandInterpolator(int elemCount, int frameCount, SkDisplayTypes type);
    SkOperand* getValues() { return fValues; }
    int getValuesCount() { return fFrameCount * fElemCount; }
    void    reset(int elemCount, int frameCount, SkDisplayTypes type);

    /** Add or replace a key frame, copying the values[] data into the interpolator.
        @param index    The index of this frame (frames must be ordered by time)
        @param time The millisecond time for this frame
        @param values   The array of values [elemCount] for this frame. The data is copied
                        into the interpolator.
        @param blend    A positive scalar specifying how to blend between this and the next key frame.
                        [0...1) is a cubic lag/log/lag blend (slow to change at the beginning and end)
                        1 is a linear blend (default)
                        (1...inf) is a cubic log/lag/log blend (fast to change at the beginning and end)
    */
    bool    setKeyFrame(int index, SkMSec time, const SkOperand values[], SkScalar blend = SK_Scalar1);
    Result timeToValues(SkMSec time, SkOperand values[]) const;
    SkDEBUGCODE(static void UnitTest();)
private:
    SkDisplayTypes fType;
    SkOperand* fValues;     // pointer into fStorage
#ifdef SK_DEBUG
    SkOperand(* fValuesArray)[10];
#endif
    typedef SkInterpolatorBase INHERITED;
};

#endif // SkOperandInterpolator_DEFINED

