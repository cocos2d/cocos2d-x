/*
 * Created by ucchen on 2/12/14.
 * Copyright (c) 2014 Chukong Technologies Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef __jsb_cocos2dx_spine_manual__
#define __jsb_cocos2dx_spine_manual__

#include "jsapi.h"
#include "spine/spine-cocos2dx.h"

void register_all_cocos2dx_spine_manual(JSContext* cx, JS::HandleObject global);

extern jsval speventdata_to_jsval(JSContext* cx, spEventData& v);
extern jsval spevent_to_jsval(JSContext* cx, spEvent& v);
extern jsval spbonedata_to_jsval(JSContext* cx, const spBoneData* v);
extern jsval spbone_to_jsval(JSContext* cx, spBone& v);
extern jsval spskeleton_to_jsval(JSContext* cx, spSkeleton& v);
extern jsval spattachment_to_jsval(JSContext* cx, spAttachment& v);
extern jsval spslotdata_to_jsval(JSContext* cx, spSlotData& v);
extern jsval spslot_to_jsval(JSContext* cx, spSlot& v);
extern jsval sptimeline_to_jsval(JSContext* cx, spTimeline& v);
extern jsval spanimationstate_to_jsval(JSContext* cx, spAnimationState& v);
extern jsval spanimation_to_jsval(JSContext* cx, spAnimation& v);
extern jsval sptrackentry_to_jsval(JSContext* cx, spTrackEntry& v);

#endif /* defined(__jsb_cocos2dx_spine_manual__) */
