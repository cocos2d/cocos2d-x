/*
 * Created by Huabin LING on 17/6/15.
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

#include "base/ccConfig.h"
#if CC_USE_NAVMESH
#ifndef __cocos2d_js_bindings__jsb_cocos2dx_navmesh_conversions__
#define __cocos2d_js_bindings__jsb_cocos2dx_navmesh_conversions__

#include "jsapi.h"
#include "navmesh/CCNavMeshAgent.h"

namespace cocos2d
{
    struct NavMeshAgentParam;
}

bool jsval_to_NavMeshAgentParam(JSContext *cx, JS::HandleValue v, cocos2d::NavMeshAgentParam* ret);
jsval offMeshLinkData_to_jsval(JSContext* cx, const cocos2d::OffMeshLinkData& v);

#endif /* defined(__cocos2d_js_bindings__jsb_cocos2dx_navmesh_conversions__) */
#endif //#if CC_USE_NAVMESH
