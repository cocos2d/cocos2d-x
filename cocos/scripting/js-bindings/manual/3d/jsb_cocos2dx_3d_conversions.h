/*
 * Created by Huabin LING on 17/6/15.
 * Copyright (c) 2015 Chukong Technologies Inc.
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
#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
#ifndef __cocos2d_js_bindings__jsb_cocos2dx_3d_conversions__
#define __cocos2d_js_bindings__jsb_cocos2dx_3d_conversions__

#include "jsapi.h"
#include "CCPhysics3DObject.h"

bool jsval_to_Physics3DRigidBodyDes(JSContext *cx, JS::HandleValue v, cocos2d::Physics3DRigidBodyDes** bodyDes);

#endif /* defined(__cocos2d_js_bindings__jsb_cocos2dx_3d_conversions__) */
#endif //#if CC_USE_3d
