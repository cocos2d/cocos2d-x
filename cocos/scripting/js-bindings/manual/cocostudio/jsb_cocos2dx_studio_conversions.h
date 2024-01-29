/*
 * Created by Huabin LING on 21/1/15.
 * Copyright (c) 2015-2016 Chukong Technologies Inc.
 * Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
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

#ifndef __cocos2d_js_bindings__jsb_cocos2dx_studio_conversions__
#define __cocos2d_js_bindings__jsb_cocos2dx_studio_conversions__

#include "jsapi.h"

namespace cocostudio
{
    namespace timeline
    {
        struct AnimationInfo;
    }
}

extern jsval animationInfo_to_jsval(JSContext* cx, const cocostudio::timeline::AnimationInfo& v);
extern bool jsval_to_animationInfo(JSContext* cx, JS::HandleValue vp, cocostudio::timeline::AnimationInfo* ret);

#endif /* defined(__cocos2d_js_bindings__jsb_cocos2dx_studio_conversions__) */
