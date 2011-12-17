/*
 * Copyright (C) 2006 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SkInterpolator_DEFINED
#define SkInterpolator_DEFINED

#include "SkScalar.h"

class SkInterpolatorBase : SkNoncopyable {
public:
    enum Result {
        kNormal_Result,
        kFreezeStart_Result,
        kFreezeEnd_Result
    };
protected:
    SkInterpolatorBase();
    ~SkInterpolatorBase();
public:
    void    reset(int elemCount, int frameCount);

    /** Return the start and end time for this interpolator.
        If there are no key frames, return false.
        @param startTime If not null, returns the time (in milliseconds) of the
                         first keyframe. If there are no keyframes, this param
                         is ignored (left unchanged).
        @param endTime If not null, returns the time (in milliseconds) of the
                       last keyframe. If there are no keyframes, this parameter
                       is ignored (left unchanged).
        @return True if there are key frames, or false if there are none.
    */
    bool    getDuration(SkMSec* startTime, SkMSec* endTime) const;


    /** Set the whether the repeat is mirrored.
        @param mirror If true, the odd repeats interpolate from the last key
                      frame and the first.
    */
    void setMirror(bool mirror) {
        fFlags = SkToU8((fFlags & ~kMirror) | (int)mirror);
    }

    /** Set the repeat count. The repeat count may be fractional.
        @param repeatCount Multiplies the total time by this scalar.
    */
    void    setRepeatCount(SkScalar repeatCount) { fRepeat = repeatCount; }

    /** Set the whether the repeat is mirrored.
        @param reset If true, the odd repeats interpolate from the last key
                     frame and the first.
    */
    void setReset(bool reset) {
        fFlags = SkToU8((fFlags & ~kReset) | (int)reset);
    }

    Result  timeToT(SkMSec time, SkScalar* T, int* index, SkBool* exact) const;

protected:
    enum Flags {
        kMirror = 1,
        kReset = 2,
        kHasBlend = 4
    };
    static SkScalar ComputeRelativeT(SkMSec time, SkMSec prevTime,
                             SkMSec nextTime, const SkScalar blend[4] = NULL);
    int16_t fFrameCount;
    uint8_t fElemCount;
    uint8_t fFlags;
    SkScalar fRepeat;
    struct SkTimeCode {
        SkMSec  fTime;
        SkScalar fBlend[4];
    };
    SkTimeCode* fTimes;     // pointer into fStorage
    void* fStorage;
#ifdef SK_DEBUG
    SkTimeCode(* fTimesArray)[10];
#endif
};

class SkInterpolator : public SkInterpolatorBase {
public:
    SkInterpolator();
    SkInterpolator(int elemCount, int frameCount);
    void    reset(int elemCount, int frameCount);

    /** Add or replace a key frame, copying the values[] data into the
        interpolator.
        @param index    The index of this frame (frames must be ordered by time)
        @param time The millisecond time for this frame
        @param values   The array of values [elemCount] for this frame. The data
                        is copied into the interpolator.
        @param blend    A positive scalar specifying how to blend between this
                        and the next key frame. [0...1) is a cubic lag/log/lag
                        blend (slow to change at the beginning and end)
                        1 is a linear blend (default)
    */
    bool setKeyFrame(int index, SkMSec time, const SkScalar values[],
                     const SkScalar blend[4] = NULL);

    /** Return the computed values given the specified time. Return whether
        those values are the result of pinning to either the first
        (kFreezeStart) or last (kFreezeEnd), or from interpolated the two
        nearest key values (kNormal).
        @param time The time to sample (in milliseconds)
        @param (may be null) where to write the computed values.
    */
    Result timeToValues(SkMSec time, SkScalar values[] = NULL) const;

    SkDEBUGCODE(static void UnitTest();)
private:
    SkScalar* fValues;  // pointer into fStorage
#ifdef SK_DEBUG
    SkScalar(* fScalarsArray)[10];
#endif
    typedef SkInterpolatorBase INHERITED;
};

/** Given all the parameters are [0...1], apply the cubic specified by (0,0)
    (bx,by) (cx,cy) (1,1) to value, returning the answer, also [0...1].
*/
SkScalar SkUnitCubicInterp(SkScalar value, SkScalar bx, SkScalar by,
                           SkScalar cx, SkScalar cy);

#endif

